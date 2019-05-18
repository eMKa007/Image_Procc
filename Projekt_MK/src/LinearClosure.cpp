
#include "../include/LinearClosure.h"

LinearClosure::LinearClosure(Bitmap ^ InputImage)
{
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	

}

LinearClosure::~LinearClosure()
{
	delete OutputImage;
	delete StructuralElement;
}

Bitmap^ LinearClosure::Compute()
{
	

	return OutputImage;
}
