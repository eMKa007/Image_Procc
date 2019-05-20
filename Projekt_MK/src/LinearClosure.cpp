
#include "../include/LinearClosure.h"

LinearClosure::LinearClosure(Bitmap ^ InputImage)
{
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	Img = InputImage;
	OutputImage = gcnew Bitmap( Img->Width, Img->Height, Imaging::PixelFormat::Format24bppRgb);

	CreateStructuralElement( GetLength(), GetDegree() );
	
}

LinearClosure::~LinearClosure()
{
	delete OutputImage;
	delete StructuralElement;
}

/*	----------------------------------------------------------
*	Function name:	Compute()
*	Parameters:		None.
*	Used to:		Start processing.
*	Return:			Bitmap^ Image* - output computed image
*/
Bitmap^ LinearClosure::Compute()
{
	return Erosion(Dilatation( Img ));
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	CreateStructuralElement()
*	Parameters:		int length - length of linear element
					int degree - degree of element to OX axis.
*	Used to:		Create Morphological structural element used in Erosion/Dilatation
*	Return:			None. Structural element vector is filled.
*/
void LinearClosure::CreateStructuralElement( int length, int degree)
{
	/* Create container for structural element */
	StructuralElement = new vector<int>;

	/* Calculate size of structural element matrix */
	structural_element_height = Math::Abs(Math::Ceiling(Math::Sin( Math::PI * degree / 180.0 ) * length));
	structural_element_width = Math::Abs( Math::Ceiling(Math::Cos( Math::PI * degree / 180.0 ) * length));

	/* Resize container to calculated size, and fill with zeros */
	StructuralElement->resize( structural_element_width * structural_element_height );
	std::fill(StructuralElement->begin(), StructuralElement->end(), 0);

	/* Compute centre of structural element */
	structural_element_anchor_x = + Math::Floor( structural_element_width /2.f );
	structural_element_anchor_y = Math::Floor( structural_element_height/2.f );

	/* Line equation -> y = ax + b; */
	/* Calculate line factors */
	double Coef_a = Math::Round(Math::Tan(Math::PI * degree / 180.0) * 10) / 10;
	double Coef_b = Coef_a < 0 ? 0 : -(structural_element_height - 1);

	/* Put 1 into structural element matrix where line is inside pixel */
	for (double idx = 0; idx < structural_element_width; idx += 0.1)
	{
		idx = Math::Round(idx * 10) / 10;
		float x = Math::Floor(idx);

		if (Coef_a * idx + Coef_b > 0)
			break;

		double y = Math::Ceiling( Math::Abs( Coef_a * idx + Coef_b ));

		/* Calculate offset in 1d vector */
		int offset = (y * structural_element_width + x);

		StructuralElement->at( offset ) = 1;
	}

	/* Print to console computed structural element */
	for (int i = 0; i < StructuralElement->size(); i++)
	{
		printf("  %d  ", StructuralElement->at(i));
		if (i % structural_element_width == structural_element_width - 1)
			printf("\n");
	}

	printf(" \n Anchor at: %d  %d", structural_element_anchor_x, structural_element_anchor_y);
}

/*	----------------------------------------------------------
*	Function name:	GetLength()
*	Parameters:		None
*	Used to:		Interact with user to choose desired element length.
*	Return:			Element length.
*/
int LinearClosure::GetLength() 
{
	int			Choice = 0;
	bool		Picked = false;

	while (!Picked)
	{
		///TODO: What if number is soooo big?
		printf("\nEnter valid desired line element length [in pixels]: ");

		cin >> Choice;		

		if (Choice >= 0 && Choice <= (Img->Height < Img->Width ? Img->Height : Img->Width) )
		{
			Picked = true;
			break;
		}

		printf("\nPlease enter valid number.\nLength in pixels. Not bigger than image size.");
	}

	return Choice;
}

/*	----------------------------------------------------------
*	Function name:	GetDegree()
*	Parameters:		None
*	Used to:		Interact with user to choose desired element rotation.
*	Return:			Rotation degree to OX axis.
*/
int LinearClosure::GetDegree()
{
	int			Choice = 0;
	bool		Picked = false;

	while (!Picked)
	{
		///TODO: What if number is soooo big?
		printf("\nEnter valid desired line element rotation degree [in degrees] <0-180>: ");

		cin >> Choice;

		if (Choice >= 0 && Choice <= 180 )
		{
			Picked = true;
			break;
		}

		printf("\nPlease enter valid number.\nRotation in degree. Range: 0 - 180.");
	}

	return Choice;
}

/*	----------------------------------------------------------
*	Function name:	Dilatation()
*	Parameters:		Bitmap^ SourceImage - desired image to apply dilatation to.
*	Used to:		Apply Dilatation with linear element to input image.
*	Return:			None. Output Image is updated.
*/
Bitmap^ LinearClosure::Dilatation( Bitmap^ SourceImage )
{
	for( int x = 0; x < Img->Width-1; x++)
		for( int y = 0; y < Img->Height-1; y++)
		{
			int actual_min_value = 255;

			/* For every pixel inside structural element compute value */
			for( int idx = 0; idx < StructuralElement->size(); idx++)
			{
				/* Ignore pixels with values 0. They are not used. */
				if( !StructuralElement->at( idx ) )
					continue;

				/* Actual structural idx element coordinates */
				int se_x = Math::Floor(idx / structural_element_width);
				int se_y = idx - se_x;

				/* Compute pixel coordinates on input image */
				int image_x =  x + se_x - structural_element_anchor_x;
				int image_y = y + se_y - structural_element_anchor_y;

				/* Prevent of accessing pixel out of input image */
				if( image_x < 0 || image_y < 0 || image_x >= Img->Width || image_y >= Img->Height )
					continue;

				/* Update minimum value */
				actual_min_value = actual_min_value > Img->GetPixel(image_x, image_y).R ? Img->GetPixel(image_x, image_y).R : actual_min_value;
			}

			OutputImage->SetPixel(x, y, Color::FromArgb(actual_min_value, actual_min_value , actual_min_value) );
		}


	return OutputImage;
}

/*	----------------------------------------------------------
*	Function name:	Erosion()
*	Parameters:		Bitmap^ SourceImage - desired image to apply erosion to.
*	Used to:		Apply Erosion with linear element to input image.
*	Return:			None. Output Image is updated.
*/
Bitmap^ LinearClosure::Erosion( Bitmap^ SourceImage )
{
	for( int x = 0; x < Img->Width-1; x++)
		for( int y = 0; y < Img->Height-1; y++)
		{
			int actual_max_value = 0;

			/* For every pixel inside structural element compute value */
			for( int idx = 0; idx < StructuralElement->size(); idx++)
			{
				/* Ignore pixels with values 0. They are not used. */
				if( !StructuralElement->at( idx ) )
					continue;

				/* Actual structural idx element coordinates */
				int se_x = Math::Floor(idx / structural_element_width);
				int se_y = idx - se_x;

				/* Compute pixel coordinates on input image */
				int image_x =  x + se_x - structural_element_anchor_x;
				int image_y = y + se_y - structural_element_anchor_y;

				/* Prevent of accessing pixel out of input image */
				if( image_x < 0 || image_y < 0 || image_x >= Img->Width || image_y >= Img->Height )
					continue;

				/* Update minimum value */
				actual_max_value = actual_max_value < Img->GetPixel(image_x, image_y).R ? Img->GetPixel(image_x, image_y).R : actual_max_value;
			}

			OutputImage->SetPixel(x, y, Color::FromArgb(actual_max_value, actual_max_value , actual_max_value) );
		}


	return OutputImage;
}