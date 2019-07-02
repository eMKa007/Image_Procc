#include  "../include/Application_GUI.h"

void OpenFile_cb( Fl_Widget* o, void*  ) 
{
	Fl_Native_File_Chooser fnfc;
	fnfc.title("Pick valid image file. :)");
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.filter("Image File\t *.{png,\n");
	fnfc.directory("/var/tmp");

	switch ( fnfc.show() )
	{
		case -1:	printf("Error: %s\n", fnfc.errmsg());
					//throw fnfc.errmsg();
					break;

		case 1:		printf("Canceled");
					break;

		default:	printf("Picked: %s\n", fnfc.filename());
					break;
	}
}