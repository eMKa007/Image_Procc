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

String^ ReadArgument(int argc, char* InputArgument);

int PickProcess();

Bitmap^ ReadImage(String^ FilePath);

void Start(Bitmap^ Image, int Pick);

void PrintUsage();


/* -------------------  Auxiliary Functions -------------------  */

void PrintChoiceInfo();