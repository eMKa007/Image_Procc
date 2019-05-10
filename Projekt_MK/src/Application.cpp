
#include "../include/Application.h"

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

int PickProcess()
{
	PrintChoiceInfo();

	int			Choice	= 5;
	bool		Picked	= false;

	while (!Picked)
	{
		printf("\nEnter valid desired proccess number: ");
		
		cin >> Choice;		///TODO: Prompt user if input is not a number (eg. letter)
				
		if (Choice >= 0 && Choice <= 4)
		{
			Picked = true;
			break;
		}

		printf("\nPlease enter valid number. <0-4>");
	}

	return Choice;
}

Bitmap^ ReadImage(String ^ FilePath)
{
	Bitmap^ bmp;
	bmp = gcnew Bitmap(FilePath, true);

	if (!bmp || bmp->Height == 0 || bmp->Width == 0)
		throw "Invalid input image. Select valid one please.";

	return bmp;
}

void Start(Bitmap^ Image, int Pick)
{
	EProcess Process = static_cast<EProcess>(Pick);
	switch (Process)
	{
		case EProcess::EAutoTreshold:
		{

		} break;

		case EProcess::EKirshFiltration:
		{

		} break;

		case EProcess::ELinearClosure:
		{

		} break;

		case EProcess::EConvexSurr:
		{

		} break;

		default:
		{

		} break;
	}
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


/* -------------------  Auxiliary Functions -------------------  */

void PrintChoiceInfo()
{
	printf("Choose desired process: <0-4>\n");
	printf("\t1. Automatic tresholding with max entrophy method (RGB or Mono image).\n");
	printf("\t2. Kirsch filtering. Symmetric reflection (RGB or Mono image).\n");
	printf("\t3. Image closure with linear element (Mono or Binary image).\n");
	printf("\t4. Convex surrounding. (Binary Image)\n");
	printf("\n\t0. Do nothing, exit program.\n");
}