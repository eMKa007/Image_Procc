#pragma once

#include "Headers.h"

public ref class AutoTresholding
{
	public:
		AutoTresholding( Bitmap^ Image );
		~AutoTresholding();

		Bitmap^ Compute();

	private:
		Bitmap^ Img;
		array<int, 256>* Histogram;

		void ComputeHistogram();

		void Rgb2Gray();
};

