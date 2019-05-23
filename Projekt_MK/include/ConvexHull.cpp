#include "../include/ConvexHull.h"

ConvexHull::ConvexHull(Bitmap ^ InputImage)
{
	if (InputImage->PixelFormat != Imaging::PixelFormat::Format24bppRgb)
	{
		Rectangle BBox = Rectangle(0, 0, InputImage->Width, InputImage->Height);
		Bitmap^ clonedOne = InputImage->Clone(BBox, Imaging::PixelFormat::Format24bppRgb);
		InputImage = clonedOne;
	}

	SourceImage = InputImage;

	/* Create array for 8 masks, and fill them with starting values */
	convex_masks = new array< array< int, 9>*, 8>;
	convex_masks->fill(nullptr);

	for (int i = 0; i < 8; i++)
	{
		(*convex_masks)[i] = new array< int, 9>;
		(*convex_masks)[i]->fill(0);
	}
}

ConvexHull::~ConvexHull()
{
	delete SourceImage;

	for (int i = 0; i < 8; i++)
	{
		delete( (*convex_masks)[i] );
	}

	delete convex_masks;
}

/*	----------------------------------------------------------
*	Function name:	Compute()
*	Parameters:		None.
*	Used to:		Main function. Used to fill masks, and start computing.
*	Return:			None. Convex Hull of image is created.
*/
Bitmap^ ConvexHull::Compute()
{
	/* Create masks and process image. */
	fill_masks();
	return compute_hull();	
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	fill_masks()
*	Parameters:		None.
*	Used to:		Fill created array of Masks with values used in convex hull.
*	Return:			None. Convex hull masks are updates.
*/
void ConvexHull::fill_masks()
{
	/* Initial values for first mask. Ether will be rotated */
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

	/* Fill other masks. */
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			convex_masks->at(y)->at(x) = Mask->at(x);
		}

		rotate_mask45(Mask);
	}
}

/*	----------------------------------------------------------
*	Function name:	rotate_mask45()
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
Bitmap^ ConvexHull::compute_hull()
{
	/* Init number of pixels changed to some big value */
	array<Color*, 9>* Pixels = new array<Color*, 9>;

	/* Initialise pixels array */
	for( int i = 0; i< 9; i++)
	{
		Pixels->at(i) = nullptr;
	}

	/* Init pixel_changed value to true, just to get inside while loop */
	int pixel_changed = 1;

	/* Make computations while any pixel changed. */
	while( pixel_changed )
	{
		pixel_changed = 0;

		/* Go through all image pixels */
		for( int x = 1; x < SourceImage->Width-1; x++ )
		{
			for( int y = 1; y < SourceImage->Height-1; y++)
			{
				/* Go to next if central pixel is == 0*/
				if( SourceImage->GetPixel(x,y).R == 255 )
					continue;

				/* Get access to every pixel we have to deal with in this iteration */
				Pixels->at(0) = &SourceImage->GetPixel(x - 1, y - 1);
				Pixels->at(1) = &SourceImage->GetPixel(x,	 y - 1);
				Pixels->at(2) = &SourceImage->GetPixel(x + 1, y - 1);
				Pixels->at(3) = &SourceImage->GetPixel(x - 1, y);
				Pixels->at(4) = &SourceImage->GetPixel(x,	 y);
				Pixels->at(5) = &SourceImage->GetPixel(x + 1, y);
				Pixels->at(6) = &SourceImage->GetPixel(x - 1, y + 1);
				Pixels->at(7) = &SourceImage->GetPixel(x,	 y + 1);
				Pixels->at(8) = &SourceImage->GetPixel(x + 1, y + 1);

				/* For that pixel compute mask. */
				for (int i = 0; i < convex_masks->size(); i++)
				{
					/* Number of pixels matched with this mask */
					int match_pixels = 0;
					
					for( int j = 0; j< 9; j++ )
					{
						if( convex_masks->at(i)->at(j) == 1 && Pixels->at(j)->R == 255 && Pixels->at(j)->G == 255 && Pixels->at(j)->B == 255)
							match_pixels++;
						else if (convex_masks->at(i)->at(j) == 0 && Pixels->at(j)->R == 0 && Pixels->at(j)->G == 0 && Pixels->at(j)->B == 0)
							match_pixels++;
					}

					/* If any mask match, fill pixel at coordinates x,y and go to nex one. */
					if( match_pixels >= 6)
					{
						SourceImage->SetPixel(x, y, Color::FromArgb(255, 255, 255) );
						pixel_changed++;
						break;
					}
				}
			}
		}
	}

	return SourceImage;
}


