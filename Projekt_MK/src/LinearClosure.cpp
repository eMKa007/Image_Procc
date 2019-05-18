
#include "../include/LinearClosure.h"

LinearClosure::LinearClosure(Bitmap ^ InputImage)
{
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	CreateStructuralElement( GetLength(), GetDegree() );
	
}

LinearClosure::~LinearClosure()
{
	delete OutputImage;
	delete StructuralElement;
}

Bitmap^ LinearClosure::Compute()
{
	//Apply Dylatancja();
	//Apply Erosion();


	return OutputImage;
}

/* -------------------  Auxiliary Functions -------------------  */

void LinearClosure::CreateStructuralElement( int length, int degree)
{
	StructuralElement = new vector<int>;
	StructuralElement->resize(length * length);
	fill(StructuralElement->begin(), StructuralElement->end(), 0);



}

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

int LinearClosure::GetDegree()
{
	int			Choice = 0;
	bool		Picked = false;

	while (!Picked)
	{
		///TODO: What if number is soooo big?
		printf("\nEnter valid desired line element rotation degree [in degrees] <0-90>: ");

		cin >> Choice;

		if (Choice >= 0 && Choice <= 90 )
		{
			Picked = true;
			break;
		}

		printf("\nPlease enter valid number.\nRotation in degree. Range: 0 - 90.");
	}

	return Choice;
}

void LinearClosure::Dilatation()
{

}

void LinearClosure::Erosion()
{

}