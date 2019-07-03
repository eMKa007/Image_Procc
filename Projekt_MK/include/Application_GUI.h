#pragma once

#include "Headers.h"

extern Fl_Window* MainWindow;
extern Fl_Image* InputImage;
extern Fl_Box* MainPicetureBox;
extern Fl_Menu_Bar* MenuBar;
extern Fl_Box* InfoBox;

extern char ImageSource[160];
extern char InfoBox_label[1024];

void OpenFile_cb( Fl_Widget* o, void* );
void KirschFilt_cb( Fl_Widget* o, void* );
void Exit_cb( Fl_Widget* o, void* );
