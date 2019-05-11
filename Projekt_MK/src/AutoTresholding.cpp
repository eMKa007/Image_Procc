
#include "../include/AutoTresholding.h"

AutoTresholding::AutoTresholding( Bitmap^ Image ): Img(Image) 
{
	Histogram = new array<int, 256>;
	Histogram->fill(0);
}

AutoTresholding::~AutoTresholding() 
{
	delete Histogram;
}

/*	----------------------------------------------------------
*	Function name:	Compute()
*	Parameters:		None.
*	Used to:		Start image processing. Prepare, and compute.
*	Return:			Computed new Bitmap.
*/
Bitmap ^ AutoTresholding::Compute()
{
	switch (Img->PixelFormat)
	{
		case Imaging::PixelFormat::Format24bppRgb:
		{
			Rgb2Gray();
			
			ComputeHistogram();

			double ImgEntropy	= ComputeHistogramEntropy( 0, Histogram->size() );
			int TresholdVal		= ComputeMaxEntropy();
		
		} break;

		case Imaging::PixelFormat::Format8bppIndexed:
		{
			ComputeHistogram();
		} break;
	}


	throw "End of Implementation.";
	// TODO: insert return statement here
}

/*	----------------------------------------------------------
*	Function name:	ComputeHistogram()
*	Parameters:		None.
*	Used to:		Compute Histogram of grayscale image, where pixel value is stored in Red value.
*	Return:			None. Histogram array is filled.
*/
void AutoTresholding::ComputeHistogram()
{
	for (int kx = 0; kx < Img->Width; kx++)
	{
		for (int ky = 0; ky < Img->Height; ky++)
		{
			/// TODO: What if image is 8bit grayscale? Is there R channel?
			(*Histogram)[Img->GetPixel(kx, ky).R]++;
		}
	}
}

/*	----------------------------------------------------------
*	Function name:	Rgb2Gray()
*	Parameters:		None.
*	Used to:		Compute each pixel grayscale value based on its RGB value, and save it as new pixel value.
*	Return:			None. Bitmap is updated to Grayscale image.
*/
void AutoTresholding::Rgb2Gray()
{
	for (int kx = 0; kx < Img->Width; kx++)
	{
		for (int ky = 0; ky < Img->Height; ky++)
		{
			Color OldColor	= Img->GetPixel(kx, ky);
			int grayScale	= (int)round((OldColor.R * 0.3) + (OldColor.G * 0.59) + (OldColor.B * 0.11));			

			// Grayscale image stored in 24bits bitmap instead of 8bit. Memory overhead. 
			Img->SetPixel(kx, ky, Color::FromArgb(grayScale, grayScale, grayScale)); 

			/// TODO: Create Clone of input Bitmap stored only 8bit values. 
			//Bitmap^ NewOne = gcnew Bitmap(Img->Width, Img->Height, Imaging::PixelFormat::Format8bppIndexed);
		}
	}
}

/*	----------------------------------------------------------
*	Function name:	ComputeImageEntropy()
*	Parameters:		int StartIdx, int EndIdx
*					StartIdx- Starting Histogram bin. EndIdx - last Histogram Bin
*	Used to:		Compute Entropy for AutoTreshold Histogram based on given Start and End index. 
*	Return:			Computed Histogram Entropy.
*/
double AutoTresholding::ComputeHistogramEntropy(int StartIdx, int EndIdx)
{
	double ImgEntropy = 0.f;
	//for (int kx = 0; kx < Img->Width; kx++)
	//{
	//	for (int ky = 0; ky < Img->Height; ky++)
	//	{
	//		int PixelVal = Img->GetPixel(kx, ky).R;
	//		ImgEntropy += (PixelVal * Math::Log(PixelVal, Math::E));
	//	}
	//}

	int TotalPx = Img->Width * Img->Height;
	for (int i = StartIdx; i < EndIdx; i++)
	{
		double HistogramTempVal = (*Histogram)[i];
		ImgEntropy += (HistogramTempVal / TotalPx) * Math::Log((HistogramTempVal / TotalPx), 2.0);
	}

	ImgEntropy = -ImgEntropy;

	return ImgEntropy;
}

/*	----------------------------------------------------------
*	Function name:	ComputeMaxEntropy()
*	Parameters:		None.
*	Used to:		Compute Entropy every Histogram treshold. 
*	Return:			Return k'value which is treshold for maximum Entropy.
*/
int AutoTresholding::ComputeMaxEntropy()
{
	int HistogramSize = Histogram->size();
	vector<double>* kValues = new vector<double>(HistogramSize, 0);
	
	TresholdEntropyValues(kValues);

	return MaxValue(kValues);;
}

/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	TresholdEntropyValues()
*	Parameters:		vector<double>* kValues - vector to store calculated entropy for every treshold.
*	Used to:		Calculate entropy for every treshold in histogram.
*	Return:			None. Updated vector values.
*/
void AutoTresholding::TresholdEntropyValues(vector<double>* kValues)
{
	int ImageSize = Img->Width * Img->Height;
	int HistogramSize = Histogram->size();
	int	BackgroundPx = 0;
	int ForegroundPx = 0;

	for (unsigned int i = 1; i < (Histogram->size() - 1); i++)
	{
		//Compute number of pixels of background.
		for (unsigned int k = 0; k < i; k++)
			BackgroundPx += (*Histogram)[i];
		
		ForegroundPx = ImageSize - BackgroundPx;

		// ---------------------------------------------------------------------------------

		double EntropyBg = ComputeHistogramEntropy(0, i);
		double EntropyFg= ComputeHistogramEntropy(i + 1, HistogramSize);					/// TODO: Write proper formula for calculation!!!!

		(*kValues)[i] = (1.f / BackgroundPx) * EntropyBg + (1.f / ForegroundPx) * EntropyFg;

		// ---------------------------------------------------------------------------------
	}
}

/*	----------------------------------------------------------
*	Function name:	MaxValue()
*	Parameters:		vector<double>* kValues - vector storing calculated values.
*	Used to:		Return index of max  input vector value.
*	Return:			int ResultVal - index of maximum value.
*/
int AutoTresholding::MaxValue(vector<double>* kValues)
{
	double MaxEntropy = 0;
	int ResultVal = 0;
	for (unsigned int i = 0; i < kValues->size(); i++)
	{
		if ((*kValues)[i] > MaxEntropy)
		{
			MaxEntropy = (*kValues)[i];
			ResultVal = i;
		}
	}

	return ResultVal;
}
