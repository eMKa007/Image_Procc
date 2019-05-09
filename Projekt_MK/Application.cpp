
#include "Application.h"

String^ ReadArgument(int argc, char* InputArgument)
{
	if (argc != 2)
	{
		PrintUsage();
		throw "Invalid Number of arguments";
	}

	String^ Temp = gcnew String(InputArgument);

	if (!Temp->EndsWith(gcnew String(".bmp")))
	{
		PrintUsage();
		throw "Invalid file extension. Need to be *.bmp";
	}

	return Temp;
}

EProcess PickProcess()
{
	printf("Choose desired process: <0-4>\n");
	printf("\t11. Histogram Equalization to Gauss decomposition with specifed standard deviation.\n");
	printf("\t12. Ordfilt2 with specified mask and starting number.\n");
	printf("\t13. Image closure with linear element (specified lenght and pitch.\n");
	printf("\t14. Geodethic distance map from specified point.\n");
	printf("\t\n10. Do nothing, exit program.\n");

	EProcess Choice = EProcess::None;
	bool Picked = false;

	while (!Picked)
	{
		printf("\nEnter desired proccess number: ");
		
		/// TODO : Fix input !!!
		cin >> Choice;

		switch (Choice)
		{
		case EProcess::None:;

		case EProcess::EHistogramEqualization:;

		case EProcess::EOrdfilt2:;

		case EProcess::ELinearClosure:;

		case EProcess::EGeodeticDistanceMap:;

		default: //Pick valid value
			break;
		}

	}
	return EProcess();
}














void PrintUsage()
{
	printf("\nImage Processing console application.");
	printf("\n\n\tUsage: Projekt_MK.exe <path>");
	printf("\n\n\t\t<path>   -   Name or path to *.bmp file.");
	printf("\n\nApplication accepts any *.bmp file (RGB or Mono).\n");
	printf("It is used to process image in specific, user defined way.\n");
	printf("For more information visit: https://github.com/eMKa007/Image_Procc\n");
}
