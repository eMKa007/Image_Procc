
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

Bitmap ^ AutoTresholding::Compute()
{
	switch (Img->PixelFormat)
	{
		case Imaging::PixelFormat::Format24bppRgb:
		{
			Rgb2Gray();
			ComputeHistogram();
		}break;

		case Imaging::PixelFormat::Format8bppIndexed:
		{
			ComputeHistogram();
		} break;
	}


	throw "End of Implementation.";
	// TODO: insert return statement here
}

void AutoTresholding::ComputeHistogram()
{
	for (int kx = 0; kx < Img->Width; kx++)
	{
		for (int ky = 0; ky < Img->Height; ky++)
		{
			(*Histogram)[Img->GetPixel(kx, ky).R]++;
		}
	}
}

void AutoTresholding::Rgb2Gray()
{
	for (int kx = 0; kx < Img->Width; kx++)
	{
		for (int ky = 0; ky < Img->Height; ky++)
		{
			Color OldColor = Img->GetPixel(kx, ky);

			int grayScale = (int)round((OldColor.R * 0.3) + (OldColor.G * 0.59) + (OldColor.B * 0.11));			

			// Grayscale image stored in 24bits bitmap. Memory overhead. 
			
			Img->SetPixel(kx, ky, Color::FromArgb(grayScale, grayScale, grayScale)); 

			/// TODO: Create Clone of input Bitmap stored only 8bit values. 
			//Bitmap^ NewOne = gcnew Bitmap(Img->Width, Img->Height, Imaging::PixelFormat::Format8bppIndexed);
		}
	}

	/*for (int i = 0; i < c.Width; i++)
	{
		for (int x = 0; x < c.Height; x++)
		{
			Color oc = c.GetPixel(i, x);
			int grayScale = (int)((oc.R * 0.3) + (oc.G * 0.59) + (oc.B * 0.11));
			Color nc = Color.FromArgb(oc.A, grayScale, grayScale, grayScale);
			d.SetPixel(i, x, nc);
		}
	}*/
}
