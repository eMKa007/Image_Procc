#pragma once

#include "Headers.h"
#include "AutoTresholding.h"
#include "KirschFilt.h"

enum class EProcess
{
	None,
	EAutoTreshold,
	EKirshFiltration,
	ELinearClosure,
	EConvexSurr
};

String^ ReadArgument(int argc, char* InputArgument);

Bitmap^ ReadImage(String^ FilePath);

int PickProcess();

void Start(Bitmap^ Image, String^ FilePath, int Pick);

void PrintUsage();


/* -------------------  Auxiliary Functions -------------------  */

String^ ChangeFileName(String^ FileName, String^ ExtensionReplacement);

void PrintChoiceInfo();