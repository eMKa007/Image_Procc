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
		KirschFilt(Bitmap^ Image);
		~KirschFilt();

		Bitmap^ Compute();

	private:
		Bitmap^ Img;
		Bitmap^ OutputImage;
		array< array<int, 9>*, 8>* KirschMasks;

		/* -------------------  Auxiliary Functions -------------------  */
		void FillKirschMasks();

		void RotateMask45(array<int, 9>* Mask);

		void ReplicateBorderValues(System::Drawing::Bitmap ^ TempImage, System::Drawing::Bitmap ^ Image);

		void FiltChannelsRGB();
};