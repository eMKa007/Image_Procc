#include "../include/KirschFilt.h"

KirschFilt::KirschFilt(Bitmap^ InputImage)
{
	KirschMasks = new array< array< int, 9>*, 8>;
	KirschMasks->fill(0);

	for (int i = 0; i < 8; i++)
	{
		(*KirschMasks)[i] = new array< int, 9>;
		(*KirschMasks)[i]->fill(0);
	}

	FillKirschMasks();

	// If Input image is different from 24bits depth- clone it to 24bits depth.
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	// Create new bitmap, Replicate border, and fill like input image.
	Img = gcnew Bitmap(InputImage->Width + 2, InputImage->Height + 2, InputImage->PixelFormat);
	ReplicateBorderValues(Img, InputImage);

	//Create new Bitmap for output image.
	OutputImage = gcnew Bitmap(InputImage->Width, InputImage->Height, InputImage->PixelFormat);
}

KirschFilt::~KirschFilt() 
{ 
	for (int i = 0; i < 8; i++)
	{
		delete( (*KirschMasks)[i] );
	}

	delete KirschMasks;
}

/*	----------------------------------------------------------
*	Function name:	Compute()
*	Parameters:		None.
*	Used to:		Start image processing. Prepare, and compute.
*	Return:			Computed new Bitmap.
*/
Bitmap^ KirschFilt::Compute()
{
	switch (Img->PixelFormat)
	{
		case Imaging::PixelFormat::Format24bppRgb:
		{
			FiltChannelsRGB();
		} break;

		case Imaging::PixelFormat::Format8bppIndexed:
		{
			
		} break;
	}

	return OutputImage;
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	FillKirschMasks()
*	Parameters:		None.
*	Used to:		Fill created array of Masks with values used by Kirsch Filter.
*	Return:			None. KirschMasks are updates.
*/
void KirschFilt::FillKirschMasks()
{
	array<int, 9>* Mask = new array<int, 9>;
	Mask->at(0) = 5;
	Mask->at(1) = 5;
	Mask->at(2) = 5;
	Mask->at(3) = -3;
	Mask->at(4) = 0;
	Mask->at(5) = -3;
	Mask->at(6) = -3;
	Mask->at(7) = -3;
	Mask->at(8) = -3;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			KirschMasks->at(y)->at(x) = Mask->at(x);
		}

		RotateMask45(Mask);
	}
}

/*	----------------------------------------------------------
*	Function name:	RotateMask45()
*	Parameters:		array<int, 9>* Mask - One of eight Kirsch mask. 
*	Used to:		Rotate Kirsch mask by 45deg.
*	Return:			None. Input Mask is updated.
*/
void KirschFilt::RotateMask45(array<int, 9>* Mask)
{
	int temp = Mask->at(1);
	Mask->at(1) = Mask->at(0);

	int temp2 = Mask->at(2);
	Mask->at(2) = temp;

	temp = Mask->at(5);
	Mask->at(5) = temp2;

	temp2 = Mask->at(8);
	Mask->at(8) = temp;

	temp = Mask->at(7);
	Mask->at(7) = temp2;

	temp2 = Mask->at(6);
	Mask->at(6) = temp;

	temp = Mask->at(3);
	Mask->at(3) = temp2;

	Mask->at(0) = temp;
}

/*	----------------------------------------------------------
*	Function name:	ReplicateBorderValues()
*	Parameters:		System::Drawing::Bitmap^ TempImage - New image to replicate border.
*					System::Drawing::Bitmap^ Image - Original image from border taken.
*	Used to:		Replicate border from Image to TempImage
*	Return:			None. TempImage is filled.
*/
void KirschFilt::ReplicateBorderValues(System::Drawing::Bitmap ^ TempImage, System::Drawing::Bitmap ^ Image)
{
	//Copy Left-Top corner.
	TempImage->SetPixel(0, 0, Image->GetPixel(0, 0));

	//Copy First line.
	for (int i = 0; i < Image->Width; i++)
		TempImage->SetPixel(i + 1, 0, Image->GetPixel(i, 0));

	//Copy Upper Right Corner
	TempImage->SetPixel(TempImage->Width - 1, 0, Image->GetPixel(Image->Width - 1, 0));

	//Copy Both sides.
	for (int i = 0; i < Image->Height; i++)
	{
		TempImage->SetPixel(0, i, Image->GetPixel(0, i));
		TempImage->SetPixel(TempImage->Width - 1, i, Image->GetPixel(Image->Width - 1, i));
	}

	//Copy Bottom-left corner.
	TempImage->SetPixel(0, TempImage->Height - 1, Image->GetPixel(0, Image->Height - 1));

	//Copy last line.
	for (int i = 0; i < Image->Width; i++)
		TempImage->SetPixel(i + 1, TempImage->Height - 1, Image->GetPixel(i, Image->Height - 1));

	//Copy Bottom-right corner.
	TempImage->SetPixel(TempImage->Width - 1, TempImage->Height - 1, Image->GetPixel(Image->Width - 1, Image->Height - 1));

	//Copy Rest of Image (inner part)
	for (int x = 0; x < Image->Width; x++)
		for (int y = 0; y < Image->Height; y++)
			TempImage->SetPixel(x + 1, y + 1, Image->GetPixel(x, y));
}

/*	----------------------------------------------------------
*	Function name:	FiltChannelsRGB()
*	Parameters:		None.
*	Used to:		Apply Kirsch filter to image channels.
*	Return:			None. Output Image is updated. 
*/
void KirschFilt::FiltChannelsRGB()
{
	int MaxRValue;
	int MaxGValue;
	int MaxBValue;

	for( int y = 1; y < Img->Height-2; y++)
		for (int x = 1; x < Img->Width- 2; x++)
		{
			MaxRValue = 0;
			MaxGValue = 0;
			MaxBValue = 0;

			Color Px1 = Img->GetPixel(x - 1, y - 1);
			Color Px2 = Img->GetPixel(x,	 y - 1);
			Color Px3 = Img->GetPixel(x + 1, y - 1);
			Color Px4 = Img->GetPixel(x - 1, y);
			Color Px5 = Img->GetPixel(x,	 y);
			Color Px6 = Img->GetPixel(x + 1, y);
			Color Px7 = Img->GetPixel(x - 1, y + 1);
			Color Px8 = Img->GetPixel(x,	 y + 1);
			Color Px9 = Img->GetPixel(x + 1, y + 1);


			//Compute Values for Central pixel with 8 Kirsch Masks.
			for (int i = 0; i < KirschMasks->size(); i++)
			{
				int PixValueR = 0;
				int PixValueG = 0;
				int PixValueB = 0;

				PixValueR += KirschMasks->at(i)->at(0) * Px1.R;
				PixValueR += KirschMasks->at(i)->at(1) * Px2.R;
				PixValueR += KirschMasks->at(i)->at(2) * Px3.R;
				PixValueR += KirschMasks->at(i)->at(3) * Px4.R;
				PixValueR += KirschMasks->at(i)->at(4) * Px5.R;
				PixValueR += KirschMasks->at(i)->at(5) * Px6.R;
				PixValueR += KirschMasks->at(i)->at(6) * Px7.R;
				PixValueR += KirschMasks->at(i)->at(7) * Px8.R;
				PixValueR += KirschMasks->at(i)->at(8) * Px9.R;

				PixValueG += KirschMasks->at(i)->at(0) * Px1.G;
				PixValueG += KirschMasks->at(i)->at(1) * Px2.G;
				PixValueG += KirschMasks->at(i)->at(2) * Px3.G;
				PixValueG += KirschMasks->at(i)->at(3) * Px4.G;
				PixValueG += KirschMasks->at(i)->at(4) * Px5.G;
				PixValueG += KirschMasks->at(i)->at(5) * Px6.G;
				PixValueG += KirschMasks->at(i)->at(6) * Px7.G;
				PixValueG += KirschMasks->at(i)->at(7) * Px8.G;
				PixValueG += KirschMasks->at(i)->at(8) * Px9.G;

				PixValueB += KirschMasks->at(i)->at(0) * Px1.B;
				PixValueB += KirschMasks->at(i)->at(1) * Px2.B;
				PixValueB += KirschMasks->at(i)->at(2) * Px3.B;
				PixValueB += KirschMasks->at(i)->at(3) * Px4.B;
				PixValueB += KirschMasks->at(i)->at(4) * Px5.B;
				PixValueB += KirschMasks->at(i)->at(5) * Px6.B;
				PixValueB += KirschMasks->at(i)->at(6) * Px7.B;
				PixValueB += KirschMasks->at(i)->at(7) * Px8.B;
				PixValueB += KirschMasks->at(i)->at(8) * Px9.B;

				MaxRValue = PixValueR > MaxRValue ? PixValueR : MaxRValue;
				MaxGValue = PixValueG > MaxGValue ? PixValueG : MaxGValue;
				MaxBValue = PixValueB > MaxBValue ? PixValueB : MaxBValue;
			}
			
			// Pick Maximum One from each one channel.
			OutputImage->SetPixel(x-1, y-1, Color::FromArgb( 
				MaxRValue > 255 ? 255 : MaxRValue,
				MaxGValue > 255 ? 255 : MaxGValue,
				MaxBValue > 255 ? 255 : MaxBValue) );
		}
}