/*
 * Program/Code for System Design (Electronic Level)
 *
 * This project contains the necessary files to interface with the 
 * accelerometer and LCD and the header file to work with Note.cpp.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "system.h"
#include "derivative.h"
#include "hardware.h"
#include "delay.h"
#include "lcd.h"
#include "i2c.h"
#include "mma845x.h"
#include "spi.h"
#include "Note.h"

using namespace USBDM;

/// LCD derived dimensions
#define LCD_WIDTH  	(LCD_X_MAX-LCD_X_MIN)
#define LCD_HEIGHT 	(LCD_Y_MAX-LCD_Y_MIN)
#define CENTRE_X   	((LCD_X_MAX-LCD_X_MIN)/2)
#define CENTRE_Y   	((LCD_Y_MAX-LCD_Y_MIN)/2)
#define ORIGIN 	   	(0)

//Total range of the Accelerometer
#define ACCEL_RANGE (8000)

// Colour for LCD background
#define BACKGROUND_COLOUR (RED)

// Colour for LCD foreground
#define FOREGROUND_COLOUR (WHITE)

// Radius used for the moving circle
#define CIRCLE_RADIUS 	  (20)


/*
 * Draws a cursor(Cross-hair) on the lcd screen.
 * Draws the reference Cross-hair on the lcd screen.
 *
 * @param lcd     The LCD to draw on
 * @param x       x position
 * @param y       y position
 * @param colour  Colour of cursor
 *
 * @note Done this way so a more sophisticated cursor can be added
 */
void drawCursor(Lcd *lcd, int x, int y, int colour) {
   lcd->drawCircle(x, y, CIRCLE_RADIUS, colour);
   lcd->drawLine(LCD_WIDTH, LCD_HEIGHT/2, ORIGIN, LCD_HEIGHT/2, FOREGROUND_COLOUR);
   lcd->drawLine(LCD_WIDTH/2, LCD_HEIGHT, LCD_WIDTH/2, ORIGIN, FOREGROUND_COLOUR);
   lcd->drawLine(x-CIRCLE_RADIUS, y, x+CIRCLE_RADIUS, y, colour);
   lcd->drawLine(x, y-CIRCLE_RADIUS, x, y+CIRCLE_RADIUS, colour);
}

/**
 * Main Procedure.
 *
 * Instantiate the LCD and Accelerometer.
 *
 * Initialise the Speaker (InitialiseNotes).
 *
 * Draw the Circle and move correctly depending
 * on the movement of the accelerometer and keep it on the LCD.
 *
 * Play the Notes on the Speaker correctly depending
 * on the movement of the accelerometer.
 */
int main() {
	// Instantiate SPI interface class
	Spi *spi = new Spi0();
	// Instantiate LCD interface class
	Lcd *lcd = new Lcd(spi);

	lcd->clear(BACKGROUND_COLOUR);

	// Instantiate interface
	I2c *i2c = new I2c0();
	MMA845x *accelerometer = new MMA845x(i2c, MMA845x::ACCEL_2Gmode);

	initialiseNotes();

	// Create variables for accelerometer values and load them with readAccelerometerXYZ
	int accelStatus;
	int16_t accelX,accelY,accelZ;

	accelerometer->readAccelerometerXYZ(&accelStatus, &accelX, &accelY, &accelZ);

	// Cursor position on screen
	int x=0, y=0;
	int xOld=50, yOld=50;

	//Initialise variables for x and y acceleration
	int incx=0, incy=0;

	//Auto-level. Initial position
	int inity=(accelY), initx=(accelX);

	uint16_t period;

	for(;;) {
		//Read values from accelerometer
		accelerometer->readAccelerometerXYZ(&accelStatus, &accelX, &accelY, &accelZ);

		//Auto-level calculation. Difference between initial position and final
		incx=accelX-initx;
		incy=accelY-inity;

		//Calculation from accelerometer range to LCD pixel range
		y=(CENTRE_Y+(((incy)*LCD_HEIGHT)/ACCEL_RANGE));
		x=(CENTRE_X-(((incx)*LCD_WIDTH)/ACCEL_RANGE));

		//Series of if statements to keep pointer on screen
		if (y>(LCD_HEIGHT-(CIRCLE_RADIUS))) {
			y=(LCD_HEIGHT-(CIRCLE_RADIUS));
		}

		if (x>(LCD_WIDTH-(CIRCLE_RADIUS))) {
			x=(LCD_WIDTH-(CIRCLE_RADIUS));
		}

		if (y<CIRCLE_RADIUS) {
			y=CIRCLE_RADIUS;
		}

		if (x<CIRCLE_RADIUS) {
			x=CIRCLE_RADIUS;
		}

		//Clear old cursor and draw new one with new values
		waitMS(50);
		drawCursor(lcd, yOld, xOld, BACKGROUND_COLOUR);
		drawCursor(lcd, y, x, FOREGROUND_COLOUR);
		xOld = x;
		yOld = y;

		//Calculate period as the max value of 8000 minus the equation for distance away from origin
		//(Range is around 4000 to 8000)
		period = (ACCEL_RANGE - (sqrt(pow(incx,2) + pow(incy,2))));

		//Send calculated period value to setNotePeriod
		setNotePeriod(period);

	}
}
