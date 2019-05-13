#include "../include/KirschFilt.h"

KirschFilt::KirschFilt(Bitmap ^ Image): Img(Image) 
{
	KirshMasks = new array< array< int, 9>*, 8>;
	KirshMasks->fill(0);

	for (int i = 0; i < 8; i++)
	{
		(*KirshMasks)[i] = new array< int, 9>;
		(*KirshMasks)[i]->fill(0);
	}

	FillKirschMasks();
}

KirschFilt::~KirschFilt() { }

/*	----------------------------------------------------------
*	Function name:	Compute()
*	Parameters:		None.
*	Used to:		Start image processing. Prepare, and compute.
*	Return:			Computed new Bitmap.
*/
Bitmap ^ KirschFilt::Compute()
{
	




	return Img;
}




/* -------------------  Auxiliary Functions -------------------  */

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
			KirshMasks->at(y)->at(x) = Mask->at(x);
		}
		RotateMask45(Mask);
	}
}


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