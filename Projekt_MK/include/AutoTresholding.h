#pragma once

#include "Headers.h"

/*
 * AutoTresholding class is used to binary image
 * RGB, or gray-scale one. Binarization is process
 * with maximum entropy method. 
 * RGB image is transferred to gray-scale first, 
 * after that histogram, and binarization take place.
 */
public ref class AutoTresholding
{
	public:
		AutoTresholding(Drawing::Bitmap^ Image );
		~AutoTresholding();

		Drawing::Bitmap^ Compute();

	private:
		Drawing::Bitmap^ Img;
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

