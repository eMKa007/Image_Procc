
#include "../include/Application.h"

/*	----------------------------------------------------------
*	Function name:	ReadArgument()
*	Parameters:		int argc, char* InputArgument
*					argc- parameters quantity; InputArgument - passed argument.
*	Used to:		Check if input argument have *.bmp extension. Parse argument to String class.
*	Return:			Parsed Input Argument as String instance.
*/
String^ ReadArgument(int argc, char* InputArgument)
{
	if (argc != 2)
	{
		PrintUsage();
		throw "Invalid Number of arguments";
	}

	String^ Temp = gcnew String(InputArgument);

	return Temp;
}

/*	----------------------------------------------------------
*	Function name:	PickProcess()
*	Parameters:		None
*	Used to:		Interact with user to choose desired image process.
*	Return:			Process id.
*/
int PickProcess()
{
	PrintChoiceInfo();

	int			Choice	= 5;
	bool		Picked	= false;

	while (!Picked)
	{
		printf("\nEnter valid desired process number: ");
		
		cin >> Choice;		/// TODO: Prompt user if input is not a number (eg. letter)
				
		if (Choice >= 0 && Choice <= 4)
		{
			Picked = true;
			break;
		}

		printf("\nPlease enter valid number. <0-4>");
	}

	return Choice;
}

/*	----------------------------------------------------------
*	Function name:	ReadImage()
*	Parameters:		String^ FilePath
*	Used to:		Construct Bitmap class, and check for if is valid.
*	Return:			Constructed Bitmap class.
*/
Drawing::Bitmap^ ReadImage(String ^ FilePath)
{
	Drawing::Bitmap^ bmp = gcnew Drawing::Bitmap(FilePath, true);

	if (!bmp || bmp->Height == 0 || bmp->Width == 0)
		throw "Invalid input image. Select valid one please.";

	return bmp;
}

/*	----------------------------------------------------------
*	Function name:	Start()
*	Parameters:		Bitmap^ Image, int Pick
*					Image - input image; Pick - number of picked process
*	Used to:		Start processing.
*	Return:			None.
*/
void Start(Drawing::Bitmap^ Img, String^ FilePath, int Pick)
{
	Drawing::Bitmap^ ResultBitmap = nullptr;

	EProcess Process = static_cast<EProcess>(Pick);
	switch (Process)
	{
		case EProcess::EAutoTreshold:
		{
			AutoTresholding^ TresholdingProcess = gcnew AutoTresholding( Img );
			ResultBitmap = TresholdingProcess->Compute();
			ResultBitmap->Save( ChangeFileName(FilePath, "_AutoTreshold.bmp") );
		} break;

		case EProcess::EKirshFiltration:
		{
			KirschFilt^ KirshFiltration = gcnew KirschFilt( Img );
			ResultBitmap = KirshFiltration->Compute();
			ResultBitmap->Save(ChangeFileName(FilePath, "_KirschFiltration.bmp"));
		} break;

		case EProcess::ECloseOpenLinear:
		{
			CloseOpenLinear^ LinearClose = gcnew CloseOpenLinear(Img);
			ResultBitmap = LinearClose->imclose();
			ResultBitmap->Save(ChangeFileName(FilePath, "_Closure.bmp"));
		} break;

		case EProcess::EConvexSurrounding:
		{
			ConvexHull^ Convex = gcnew ConvexHull(Img);
			ResultBitmap = Convex->Compute();
			ResultBitmap->Save(ChangeFileName(FilePath, "_Convex.bmp"));
		} break;

		default:
		{
			throw "Invalid picked enum value. RIP [*]";
		} break;
	}
}

/*	----------------------------------------------------------
*	Function name:	PrintUsage()
*	Parameters:		None.
*	Used to:		Print to console information about program.
*	Return:			None.
*/
void PrintUsage()
{
	printf("\nImage Processing console application.");
	printf("\n\n\tUsage: Projekt_MK.exe <path>");
	printf("\n\n\t\t<path>   -   Name or path to image file.");
	printf("\n\nApplication accepts image files (RGB or Mono).\n");
	printf("Tested extensions: *.jpg   *.bmp   *.png .\n");
	printf("It is used to process image in specific, user defined way.\n");
	printf("For more information visit: https://github.com/eMKa007/Image_Procc\n");
}


/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	ChangeFileName()
*	Parameters:		String^ FileName - input filename, with file extension.
					String^ ExtensionReplacement - string to replace old extension.
*	Used to:		Replace file extension with given string.
*	Return:			FileName updated.
*/
String^ ChangeFileName(String^ FileName, String^ ExtensionReplacement)
{
	int Length = FileName->ToCharArray()->Length;
	FileName = FileName->Remove(Length - 4);

	return FileName->Insert(Length - 4, ExtensionReplacement);
}

/*	----------------------------------------------------------
*	Function name:	PrintChoiceInfo()
*	Parameters:		None.
*	Used to:		Print to console information Choice() function.
*	Return:			None.
*/
void PrintChoiceInfo()
{
	printf("Choose desired process: <0-4>\n");
	printf("\t1. Automatic tresholding with max entrophy method (RGB or Mono image).\n");
	printf("\t2. Kirsch filtering. Symmetric reflection (RGB or Mono image).\n");
	printf("\t3. Image closure with linear element (Mono or Binary image).\n");
	printf("\t4. Convex Hull. (Binary Image)\n");
	printf("\n\t0. Do nothing, exit program.\n");
}