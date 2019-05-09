// Projekt_MK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application.h"

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
