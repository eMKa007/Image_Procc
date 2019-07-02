#pragma once

#include "Headers.h"

/*
 * KirschFilt class is used to apply edge detection
 * processing to input image. Masks are created 
 * during program runtime. Border values are replicated.
 * RGB images are filtered every channel separately.
 */
public ref class KirschFilt
{
	public:
		KirschFilt(Drawing::Bitmap^ Image);
		~KirschFilt();

		Drawing::Bitmap^ Compute();

	private:
		Drawing::Bitmap^ Img;
		Drawing::Bitmap^ OutputImage;
		array< array<int, 9>*, 8>* KirschMasks;

		/* -------------------  Auxiliary Functions -------------------  */
		void FillKirschMasks();

		void RotateMask45(array<int, 9>* Mask);

		void ReplicateBorderValues(Drawing::Bitmap ^ TempImage, Drawing::Bitmap ^ Image);

		void FiltChannelsRGB();
};