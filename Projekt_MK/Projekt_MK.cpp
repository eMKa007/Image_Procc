// Projekt_MK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "include/Application.h"



int main( int argc, char* argv[])
{
	Fl_Window win( 300,200,"Testing" );
    win.begin();
    Fl_Button but( 10, 150, 150, 30, "Open Image File" );
    win.end();
    but.callback( OpenFile_cb );
    win.show();
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


