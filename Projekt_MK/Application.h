#pragma once

#include "Headers.h"

enum class EProcess
{
	EHistogramEqualization,
	EOrdfilt2,
	ELinearClosure,
	EGeodeticDistanceMap
};

/*	----------------------------------------------------------
*	Function name:	ReadArgument
*	Parameters:		int argc, char* InputArgument
*	Used to:		Check if input argument have *.bmp extension. Parse argument to String class.
*	Return:			Parsed Input Argument as String instance.
*/
String^ ReadArgument(int argc, char* InputArgument);



/*	----------------------------------------------------------
*	Function name:	PrintUsage
*	Parameters:		None.
*	Used to:		Print to console information about program.
*	Return:			None. 
*/
void PrintUsage();