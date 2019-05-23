
#include "../include/CloseOpenLinear.h"

CloseOpenLinear::CloseOpenLinear(Bitmap ^ InputImage)
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

CloseOpenLinear::~CloseOpenLinear()
{
	delete OutputImage;
	delete StructuralElement;
}

/*	----------------------------------------------------------
*	Function name:	imclose()
*	Parameters:		None.
*	Used to:		Start image close processing.
*	Return:			Bitmap^ Image* - output computed image
*/
Bitmap^ CloseOpenLinear::imclose()
{
	return Erode(Dilate( Img ));
}

/*	----------------------------------------------------------
*	Function name:	imopen()
*	Parameters:		None.
*	Used to:		Start image open processing.
*	Return:			Bitmap^ Image* - output computed image
*/
Bitmap^ CloseOpenLinear::imopen()
{
	return Dilate( Erode( Img ) );
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	CreateStructuralElement()
*	Parameters:		int length - length of linear element
					int degree - degree of element to OX axis.
*	Used to:		Create Morphological structural element used in Erosion/Dilatation
*	Return:			None. Structural element vector is filled.
*/
void CloseOpenLinear::CreateStructuralElement( int length, int degree)
{
	/* Create container for structural element */
	StructuralElement = new vector<int>;
	
	if ( degree == 0 )	
	{
		/* Calculate size of structural element matrix */
		structural_element_height = 1;
		structural_element_width = length;
		structural_element_anchor_x = length/2;
		structural_element_anchor_y = 0;

		StructuralElement->resize( length );
		std::fill(StructuralElement->begin(), StructuralElement->end(), 1);

		print_structural_el();

		return;
	}
	else if( degree == 90 )
	{
		/* Calculate size of structural element matrix */
		structural_element_height = length;
		structural_element_width = 1;
		structural_element_anchor_x = 0;
		structural_element_anchor_y = length/2;

		StructuralElement->resize( length );
		std::fill(StructuralElement->begin(), StructuralElement->end(), 1);

		print_structural_el();

		return;
	}

	bool revert = false;
	if( degree > 90 )
	{
		degree = 180 - degree;
		revert = true;
	}
	/* Calculate size of structural element matrix */
	structural_element_height = Math::Abs(Math::Ceiling(Math::Sin( Math::PI * degree / 180.0 ) * length));
	structural_element_width = Math::Abs( Math::Ceiling(Math::Cos( Math::PI * degree / 180.0 ) * length));

	/* Resize container to calculated size, and fill with zeros */
	StructuralElement->resize( structural_element_width * structural_element_height );
	std::fill(StructuralElement->begin(), StructuralElement->end(), 0);

	/* Compute centre of structural element */
	structural_element_anchor_x = Math::Floor( structural_element_width /2.f );
	structural_element_anchor_y = Math::Floor( structural_element_height/2.f );

	/* Line equation -> y = ax + b; */
	/* Calculate line factors */
	double Coef_a = Math::Round(Math::Tan(Math::PI * degree / 180.0) * 10) / 10;
	double Coef_b = -(structural_element_height - 1);

	/* Put 1 into structural element matrix where line is inside pixel */
	for (double idx = 0; idx < structural_element_width; idx += 0.1)
	{
		idx = Math::Round(idx * 10) / 10;
		float x = Math::Floor(idx);

		if (Coef_a * idx + Coef_b > 0)
		{
			StructuralElement->at( structural_element_width - 1 ) = 1;
			break;
		}
			
		double y = Math::Ceiling( Math::Abs( Coef_a * idx + Coef_b ));

		/* Calculate offset in 1d vector */
		int offset = (y * structural_element_width + x);

		StructuralElement->at( offset ) = 1;
	}

	/* Because calculated one is upside down. */
	if( revert )
	{
		int y = structural_element_height;
		int x = structural_element_width;

		for( int i = 0; i < y/2; i++)
		{
			for( int j = 0; j < x; j++)
			{
				int temp0 = StructuralElement->at( i * structural_element_width + j );
				StructuralElement->at( i * structural_element_width + j ) = StructuralElement->at( (structural_element_height - i-1) * structural_element_width + j );
				StructuralElement->at( (structural_element_height - i-1) * structural_element_width + j ) = temp0;
			}
		}
	}
	
	print_structural_el();
	
	printf(" \n Anchor at: %d  %d \n", structural_element_anchor_x, structural_element_anchor_y);

}

/*	----------------------------------------------------------
*	Function name:	GetLength()
*	Parameters:		None
*	Used to:		Interact with user to choose desired element length.
*	Return:			Element length.
*/
int CloseOpenLinear::GetLength() 
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
int CloseOpenLinear::GetDegree()
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
*	Function name:	Dilate()
*	Parameters:		Bitmap^ SourceImage - desired image to apply dilatation to.
*	Used to:		Apply Dilatation with linear element to input image.
*	Return:			None. Output Image is updated.
*/
Bitmap^ CloseOpenLinear::Dilate( Bitmap^ SourceImage )
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
				int se_y = Math::Floor(idx / structural_element_width);
				int se_x = idx % structural_element_width;

				/* Compute pixel coordinates on input image */
				int delta_x_mask = se_x - structural_element_anchor_x;
				int delta_y_mask = se_y - structural_element_anchor_y;

				int image_x =  x + delta_x_mask;
				int image_y = y + delta_y_mask;

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
*	Function name:	Erode()
*	Parameters:		Bitmap^ SourceImage - desired image to apply erosion to.
*	Used to:		Apply Erosion with linear element to input image.
*	Return:			None. Output Image is updated.
*/
Bitmap^ CloseOpenLinear::Erode( Bitmap^ SourceImage )
{
	for( int x = 0; x < Img->Width-1; x++)
		for( int y = 0; y < Img->Height-1; y++)
		{
			int actual_max_value = 0;

			/* For every pixel inside structural element compute value */
			for( int idx = 0; idx < (StructuralElement->size() ); idx++)
			{
				/* Ignore pixels with values 0. They are not used. */
				if( !StructuralElement->at( idx ) )
					continue;

				/* Actual structural idx element coordinates */
				int se_y = Math::Floor(idx / structural_element_width);
				int se_x = idx % structural_element_width;

				/* Compute pixel coordinates on input image */
				int delta_x_mask = se_x - structural_element_anchor_x;
				int delta_y_mask = se_y - structural_element_anchor_y;

				int image_x =  x + delta_x_mask;
				int image_y = y + delta_y_mask;

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

/*	----------------------------------------------------------
*	Function name:	print_structural_el()
*	Parameters:		None.
*	Used to:		Print to console structural element.
*	Return:			None. 
*/
void CloseOpenLinear::print_structural_el()
{
	/* Print to console computed structural element */
	for (int i = 0; i < StructuralElement->size(); i++)
	{
		printf("  %d  ", StructuralElement->at(i));
		if (i % structural_element_width == structural_element_width - 1)
			printf("\n");
	}
}