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
		array< array<int, 9>*, 8>* KirshMasks;


		/* -------------------  Auxiliary Functions -------------------  */
		void FillKirschMasks();

		void RotateMask45(array<int, 9>* Mask);
};