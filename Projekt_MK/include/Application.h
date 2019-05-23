#pragma once

#include "Headers.h"
#include "AutoTresholding.h"
#include "KirschFilt.h"
#include "CloseOpenLinear.h"
#include "ConvexHull.h"

enum class EProcess
{
	ENone,
	EAutoTreshold,
	EKirshFiltration,
	ECloseOpenLinear,
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