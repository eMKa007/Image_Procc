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

		void Rgb2Gray();

		void ComputeHistogram();
		
		double ComputeHistogramEntropy(int StartIdx, int EndIdx);
		
		int ComputeMaxEntropy();

		void Image2Binary(int TresholdValue);


		/* -------------------  Auxiliary Functions -------------------  */

		void TresholdEntropyValues(vector<double>* kValues);

		int MaxValue(vector<double>* kValues);
		
};

