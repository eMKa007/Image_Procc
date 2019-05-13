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
