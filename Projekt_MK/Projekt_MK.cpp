// Projekt_MK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "include/Application.h"


int main( int argc, char* argv[])
{
	Fl_Window window(200, 200, "Window title");
    Fl_Box box(0, 0, 200, 200, "Hey, I mean, Hello, World!");
    window.show();
    Fl::run();

	try
	{
		String^ FilePath = gcnew String( ReadArgument(argc, argv[1]) );
		Drawing::Bitmap^ InputImage = ReadImage( FilePath );

		int Pick = PickProcess();
		if (Pick != 0)
		{
			Start( InputImage, FilePath, Pick );
		}

	}
	catch ( const char* Ex )
	{
		printf("\n\n|===========================================|\n");
		printf("\nException catched: %s\n\n", Ex);
		printf("|===========================================|\n\n");
	}

    return 0;
}
