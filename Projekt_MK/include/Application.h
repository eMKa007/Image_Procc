#pragma once

#include "Headers.h"
#include "AutoTresholding.h"

enum class EProcess
{
	None,
	EAutoTreshold,
	EKirshFiltration,
	ELinearClosure,
	EConvexSurr
};

/*	----------------------------------------------------------
*	Function name:	ReadArgument()
*	Parameters:		int argc, char* InputArgument
*					argc- parameters quantity; InputArgument - passed argument.
*	Used to:		Check if input argument have *.bmp extension. Parse argument to String class.
*	Return:			Parsed Input Argument as String instance.
*/
String^ ReadArgument(int argc, char* InputArgument);


/*	----------------------------------------------------------
*	Function name:	PickProcess()
*	Parameters:		None
*	Used to:		Interact with user to choose desired image proccess.
*	Return:			Process id.
*/
int PickProcess();

/*	----------------------------------------------------------
*	Function name:	ReadImage()
*	Parameters:		String^ FilePath
*	Used to:		Construct Bitmap class, and check for if is valid.
*	Return:			Constructed Bitmap class.
*/
Bitmap^ ReadImage(String^ FilePath);

/*	----------------------------------------------------------
*	Function name:	Start()
*	Parameters:		Bitmap^ Image, int Pick
*					Image - input image; Pick - number of picked process
*	Used to:		Start processing.
*	Return:			None.
*/
void Start(Bitmap^ Image, int Pick);

/*	----------------------------------------------------------
*	Function name:	PrintUsage()
*	Parameters:		None.
*	Used to:		Print to console information about program.
*	Return:			None. 
*/
void PrintUsage();




/* -------------------  Auxiliary Functions -------------------  */

/*	----------------------------------------------------------
*	Function name:	PrintChoiceInfo()
*	Parameters:		None.
*	Used to:		Print to console information Choice() function.
*	Return:			None.
*/
void PrintChoiceInfo();