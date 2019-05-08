// Projekt_MK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace System;
using namespace System::Drawing;
using namespace std;

String^ ReadArgument(int argc, char* InputArgument);
void PrintUsage();

int main( int argc, char* argv[])
{
	try
	{
		String^ FilePath = gcnew String( ReadArgument(argc, argv[1]) );
	}
	catch ( const char* Ex )
	{
		printf("\n\n|===========================================|\n");
		printf("\nException catched: %s\n\n", Ex);
		printf("|===========================================|\n\n");
	}





    return 0;
}

String^ ReadArgument( int argc, char* InputArgument )
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

void PrintUsage()
{
	printf("\nImage Processing console application.");
	printf("\n\n\tUsage: Projekt_MK.exe <path>");
	printf("\n\n\t\t<path>   -   Name or path to *.bmp file.");
	printf("\n\nApplication accepts any *.bmp file (RGB or Mono).\n");
	printf("It is used to process image in specific, user defined way.\n");
	printf("For more information visit: https://github.com/eMKa007/Image_Procc\n");
}
