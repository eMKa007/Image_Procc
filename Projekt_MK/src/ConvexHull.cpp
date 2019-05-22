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
	OutputImage = InputImage->Clone( Rectangle(0,0, InputImage->Width, InputImage->Height), Imaging::PixelFormat::Format24bppRgb);

	convex_masks = new array< array< int, 9>*, 8>;
	convex_masks->fill(0);

	for (int i = 0; i < 8; i++)
	{
		(*convex_masks)[i] = new array< int, 9>;
		(*convex_masks)[i]->fill(0);
	}
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
	fill_masks();
	compute_hull();	

	return OutputImage;
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

		rotate_mask45(Mask);
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
	array<Color*, 9>* Pixels = new array<Color*, 9>;

	/* Initialise pixels array */
	for( int i = 0; i< 9; i++)
	{
		Pixels->at(i) = nullptr;
	}

	/* Compute convex while there are pixels changed. */
	while( pixel_changed )
	{
		pixel_changed = 0;

		for (int i = 0; i < convex_masks->size(); i++)
		{
			for( int x = 0; x < Img->Width; x++ )
			{
				for( int y = 0; y < Img->Height; y++)
				{
					/* Number of pixels matched with mask */
					int match_pixels = 0;

					Color* Temp = &Color::FromArgb(100,100,100);
					fill(Pixels->begin(), Pixels->end(), Temp);
/*
					Pixels->at(0) = Color::FromArgb(100, 100, 100);
					Pixels->at(1) = Color::FromArgb(100, 100, 100);
					Pixels->at(2) = Color::FromArgb(100, 100, 100);
					Pixels->at(3) = Color::FromArgb(100, 100, 100);
					Pixels->at(4) = Color::FromArgb(100, 100, 100);
					Pixels->at(5) = Color::FromArgb(100, 100, 100);
					Pixels->at(6) = Color::FromArgb(100, 100, 100);
					Pixels->at(7) = Color::FromArgb(100, 100, 100);
					Pixels->at(8) = Color::FromArgb(100, 100, 100);
*/
					/* Be sure, that pixels are inside image. */
					if( (x -1) > 0 && (y-1) > 0)
					{
						Pixels->at(0) = &Img->GetPixel(x - 1, y - 1);
						
					}

					if( (y - 1) > 0 )
					{
						Pixels->at(1) = &Img->GetPixel(x,	 y - 1);
					}

					if( ( x + 1) < Img->Width && (y-1)>0)
					{
						Pixels->at(2) = &Img->GetPixel(x + 1, y - 1);
					}

					if( (x-1) > 0 )
					{
						Pixels->at(3) = &Img->GetPixel(x - 1, y);
					}

					Pixels->at(4) = &Img->GetPixel(x,	 y);

					if( (x+1) < Img->Width)
					{
						Pixels->at(5) = &Img->GetPixel(x + 1, y);
					}

					if( (x -1) > 0 && (y+1) < Img->Height)
					{
						Pixels->at(6) = &Img->GetPixel(x - 1, y + 1);
					}

					if( (y+1) < Img->Height)
					{
						Pixels->at(7) = &Img->GetPixel(x,	 y + 1);
					}

					if( (x+1) < Img->Width && (y+1) < Img->Height )
					{
						Pixels->at(8) = &Img->GetPixel(x + 1, y + 1);
					}

					for( int j = 0; j< 9; j++ )
					{
						if( convex_masks->at(i)->at(j) == 1 && Pixels->at(j)->R == 255 && Pixels->at(j)->G == 255 && Pixels->at(j)->B == 255)
							match_pixels++;
						else if (convex_masks->at(i)->at(j) == 0 && Pixels->at(j)->R == 0 && Pixels->at(j)->G == 0 && Pixels->at(j)->B == 0)
							match_pixels++;
					}

					if( match_pixels >= 6 )
					{
						OutputImage->SetPixel(x, y, Color::FromArgb(255, 255, 255) );
						pixel_changed++;
					}
				}
			}
		}
				

	}


}


