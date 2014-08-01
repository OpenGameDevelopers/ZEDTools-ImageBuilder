#include <iostream>
#include <X11Window.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	ImageBuilder::X11Window TestWindow;
	ImageBuilder::WINDOW_RECT WindowRect;

	WindowRect.X = 0;
	WindowRect.Y = 0;
	WindowRect.Width = 1024;
	WindowRect.Height = 768;
	
	TestWindow.Initialise( WindowRect );

	return 0;
}

