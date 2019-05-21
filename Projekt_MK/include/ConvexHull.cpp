#include "ConvexHull.h"

ConvexHull::ConvexHull(Bitmap ^ InputImage)
{
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	Img = InputImage;
	OutputImage = gcnew Bitmap( Img->Width, Img->Height, Imaging::PixelFormat::Format24bppRgb);
}

ConvexHull::~ConvexHull()
{
	delete OutputImage;

	for (int i = 0; i < 8; i++)
	{
		delete( (*convex_masks)[i] );
	}

	delete convex_masks;
}

Bitmap^ ConvexHull::Compute()
{
	create_masks();

	

	return OutputImage;
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	create_masks()
*	Parameters:		None.
*	Used to:		Fill created array of Masks with values used in convex hull.
*	Return:			None. Convex hull masks are updates.
*/
void ConvexHull::create_masks()
{
	array<int, 9>* Mask = new array<int, 9>;
	Mask->at(0) =	1;
	Mask->at(1) =	1;
	Mask->at(2) =	-1;
	Mask->at(3) =	1;
	Mask->at(4) =	0;
	Mask->at(5) =	-1;
	Mask->at(6) =	1;
	Mask->at(7) =	-1;
	Mask->at(8) =	0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			convex_masks->at(y)->at(x) = Mask->at(x);
		}

		RotateMask45(Mask);
	}
}

/*	----------------------------------------------------------
*	Function name:	RotateMask45()
*	Parameters:		array<int, 9>* Mask - One of eight convex hull masks. 
*	Used to:		Rotate given mask by 45deg.
*	Return:			None. Input Mask is updated.
*/
void ConvexHull::rotate_mask45(array<int, 9>* Mask)
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
*	Function name:	compute_hull()
*	Parameters:		None. 
*	Used to:		Compute convex hull of input binary image.
*	Return:			None. Output image is updated.
*/
void ConvexHull::compute_hull()
{
	/* Init number of pixels changed to some big value */
	int pixel_changed = Img->Width * Img->Height;

	/* Compute convex while there are pixels changed. */
	while( pixel_changed )
	{
		
		for( int x = 0; x < Img->Width; x++ )
		{
			for( int y = 0; y < Img->Height; y++)
			{
				
			}
		}

	}


}


