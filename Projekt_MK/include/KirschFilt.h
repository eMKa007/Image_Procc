#pragma once

#include "Headers.h"

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