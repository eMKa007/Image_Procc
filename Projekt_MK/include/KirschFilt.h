#pragma once

#include "Headers.h"

enum class ColorChannel
{
	R,
	G,
	B,
	GrayScale
};

public ref class KirschFilt
{
	public:
		KirschFilt(Bitmap^ Image);
		~KirschFilt();

		Bitmap^ Compute();

	private:
		Bitmap^ Img;
		array< array<int, 9>*, 8>* KirschMasks;


		void ProcessChannel(ColorChannel Channel);

		/* -------------------  Auxiliary Functions -------------------  */
		void FillKirschMasks();

		void RotateMask45(array<int, 9>* Mask);
};