// Projekt_MK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "include/Application.h"

Fl_Window* MainWindow;
Fl_Image* InputImage;
Fl_Box* MainPicetureBox;
Fl_Menu_Bar* MenuBar;
Fl_Box* InfoBox;

char ImageSource[160] = {0};
char InfoBox_label[1024] = {0};

int main( int argc, char* argv[])
{
	/* Create Main Application Window */
	MainWindow = new Fl_Window( 900,620, "Image Processing. by eMKa007" );
    MainWindow->begin();

	/* Main Window without border */
	MainWindow->border(0);
	MainWindow->position(100, 100);

	/* Add All necessary widgets */
    MenuBar = new Fl_Menu_Bar(0, 0, MainWindow->w(), 30 );
	MenuBar->add("File/&Open File",		0,	(Fl_Callback*)OpenFile_cb);
	MenuBar->add("File/&Exit",			0,	(Fl_Callback*)Exit_cb);
	MenuBar->add("Entropy Treshold.",	0,	(Fl_Callback*)Exit_cb);
	MenuBar->add("Open|Close Image",	0,	(Fl_Callback*)Exit_cb);
	MenuBar->add("Convex Hull",			0,	(Fl_Callback*)Exit_cb);
	MenuBar->add("Kirsch Filtration",	0,	(Fl_Callback*)KirschFilt_cb );

	MainPicetureBox = new Fl_Box(FL_THIN_DOWN_BOX, 10, 40, 600, 450, "");
	InfoBox = new Fl_Box( FL_DOWN_BOX, 10, 500, 450, 100, "InfoBox" );

	InfoBox->label("\nAfter you load an image, this box will fill with basic image info.");
	InfoBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP );

	MainWindow->end();

    MainWindow->show();
    
	Fl::run();

	/*
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
	*/

    return 0;
}


