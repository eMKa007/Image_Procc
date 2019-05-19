
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
	//Apply Dylatancja(Img);
	//Apply Erosion(OutputImage);


	return OutputImage;
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
	StructuralElement = new vector<int>;

	int Height = Math::Abs(Math::Ceiling(Math::Sin( Math::PI * degree / 180.0 ) * length));
	int Width = Math::Abs( Math::Ceiling(Math::Cos( Math::PI * degree / 180.0 ) * length));

	StructuralElement->resize( Width * Height );
	std::fill(StructuralElement->begin(), StructuralElement->end(), 0);

	// Line equation -> y = ax + b; 
	double Coef_a = Math::Round(Math::Tan(Math::PI * degree / 180.0) * 10) / 10;
	double Coef_b = Coef_a < 0 ? 0 : -(Height - 1);

	// Fill Structural Element Matrix with 0.05 step. 
	for (double idx = 0; idx < Width; idx += 0.1)
	{
		idx = Math::Round(idx * 10) / 10;
		float x = Math::Floor(idx);

		if (Coef_a * idx + Coef_b > 0)
			break;

		double y = Math::Ceiling( Math::Abs( Coef_a * idx + Coef_b ));

		int offset = (y * Width + x);

		StructuralElement->at( offset ) = 1;
	}

	for (int i = 0; i < StructuralElement->size(); i++)
	{
		printf("  %d  ", StructuralElement->at(i));
		if ( i % Width == Width-1)
			printf("\n");
	}


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

		if (Choice >= 0 && Choice <= Img->Height && Choice <= Img->Width)
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
void LinearClosure::Dilatation( Bitmap^ SourceImage )
{

}

/*	----------------------------------------------------------
*	Function name:	Erosion()
*	Parameters:		Bitmap^ SourceImage - desired image to apply erosion to.
*	Used to:		Apply Erosion with linear element to input image.
*	Return:			None. Output Image is updated.
*/
void LinearClosure::Erosion( Bitmap^ SourceImage )
{

}