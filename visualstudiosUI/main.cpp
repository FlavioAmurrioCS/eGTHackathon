

#include <QApplication>			// These headers are needed for our Qt application
#include <QDesktopWidget>

#include "window.h"				// Declares a window class for the Qt window and interaction with it. 

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);	// High level control for our Qt application. Includes start of an infinite loop
    Window window;					// Create a Qt window. Defined in window.h

	// Set the window size and area. Don't worry about these right now. 
	window.resize(window.sizeHint());	
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

	window.setWindowTitle("GMU MINERS CRAWLER PROGRAM!");		// Give the window an appropriate title. 

	//allows seeable window
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();

	//int texter = window.readTextFile();

	return app.exec(); // Starts the infinite loop necessary for event based programming. 
}
