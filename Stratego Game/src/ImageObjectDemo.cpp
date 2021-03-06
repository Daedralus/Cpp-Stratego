#include "header.h"

// This is a basic implementation, without fancy stuff

#include "BaseEngine.h"
#include "ImageManager.h"
#include "TileManager.h"
#include "DisplayableObject.h"
#include "BouncingImageObject.h"

#include "ImageObjectDemo.h"



/*
Do any setup of back buffer prior to locking the screen buffer
Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
*/
void ImageObjectDemo::virtSetupBackgroundBuffer()
{
	fillBackground(0x000000);

	for (int iX = 0; iX < getWindowWidth(); iX++)
		for (int iY = 0; iY < this->getWindowHeight(); iY++)
			switch (rand() % 100)
			{
			case 0: setBackgroundPixel(iX, iY, 0xFF0000); break;
			case 1: setBackgroundPixel(iX, iY, 0x00FF00); break;
			case 2: setBackgroundPixel(iX, iY, 0x0000FF); break;
			case 3: setBackgroundPixel(iX, iY, 0xFFFF00); break;
			case 4: setBackgroundPixel(iX, iY, 0x00FFFF); break;
			case 5: setBackgroundPixel(iX, iY, 0xFF00FF); break;
			}

	SimpleImage image(loadImage("images/cards.png", false/*don't keep it loaded*/));
	// image.renderImage(getBackgroundSurface(), 0, 0, 0, 0, image.getHeight(), image.getWidth());
	image.renderImageWithMask(getBackgroundSurface(), 0, 0, 0, 0, image.getHeight(), image.getWidth());
}


/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int ImageObjectDemo::virtInitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();

	// Destroy any existing objects
	destroyOldObjects(true);

	createObjectArray(1);
	storeObjectInArray(0, new BouncingImageObject(this,"demo.png"));

	return 0;
}









/* Draw the string that moving objects should be drawn on top of */
void ImageObjectDemo::virtDrawStringsUnderneath()
{
	// Build the string to print
	char buf[128];
	sprintf(buf, "Changing random %6d", rand());
	drawForegroundString(50, 10, buf, 0x00ffff, NULL);
	drawForegroundString(450, 10, "Underneath the objects", 0xff0000, NULL);

	if (isPaused())
		drawForegroundString(150, 300, "*** PAUSED ***", 0xff0000, NULL);
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void ImageObjectDemo::virtDrawStringsOnTop()
{
	
	// Build the string to print
	char buf[128];
	sprintf(buf, "Count %6d", rand());
	drawForegroundString(150, 40, buf, 0xff00ff, NULL);
	drawForegroundString(450, 40, "On top of the objects", 0x00ff00, NULL);
}




// Override to handle a mouse press
void ImageObjectDemo::virtMouseDown(int iButton, int iX, int iY)
{
	// Redraw the background
	lockAndSetupBackground();
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is currently pressed
*/
void ImageObjectDemo::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		setExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		if (isPaused())
			unpause();
		else
			pause();
		break;
	}
}
