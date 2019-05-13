#include "../include/KirschFilt.h"

KirschFilt::KirschFilt(Bitmap ^ Image): Img(Image) 
{
	KirschMasks = new array< array< int, 9>*, 8>;
	KirschMasks->fill(0);

	for (int i = 0; i < 8; i++)
	{
		(*KirschMasks)[i] = new array< int, 9>;
		(*KirschMasks)[i]->fill(0);
	}

	FillKirschMasks();
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
Bitmap ^ KirschFilt::Compute()
{
	switch (Img->PixelFormat)
	{
		case Imaging::PixelFormat::Format24bppRgb:
		{
			ProcessChannel( ColorChannel::R );
			ProcessChannel( ColorChannel::G );
			ProcessChannel( ColorChannel::B );
		} break;

		case Imaging::PixelFormat::Format8bppIndexed:
		{
			ProcessChannel( ColorChannel::GrayScale );
		} break;
	}




	return Img;
}

void KirschFilt::ProcessChannel(ColorChannel Channel)
{
	switch (Channel)
	{
		case ColorChannel::R:
		{

		} break;
	
		case ColorChannel::G:
		{

		}break;

		case ColorChannel::B:
		{
	
		} break;

		case ColorChannel::GrayScale:
		{

		} break;

		default:
		{
	
		} break;
	}

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