#pragma once

#include "Headers.h"
#include "AutoTresholding.h"
#include "KirschFilt.h"
#include "LinearClosure.h"

enum class EProcess
{
	ENone,
	EAutoTreshold,
	EKirshFiltration,
	ELinearClosure,
	EConvexSurrounding
};

String^ ReadArgument(int argc, char* InputArgument);

Bitmap^ ReadImage(String^ FilePath);

int PickProcess();

void Start(Bitmap^ Image, String^ FilePath, int Pick);

void PrintUsage();


/* -------------------  Auxiliary Functions -------------------  */

String^ ChangeFileName(String^ FileName, String^ ExtensionReplacement);

void PrintChoiceInfo();