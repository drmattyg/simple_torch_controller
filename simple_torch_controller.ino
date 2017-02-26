#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define NONE 1000
#define SELECT 722
#define LEFT 482
#define DOWN 310
#define UP 133
#define RIGHT 10

/*
PINOUTS:
128x32 I2C OLED: uses SDA/SCL, and pin 4 for reset
LCD/Button panel: doesn't use the LCD.  Just uses A0, 5V, GND on Uno and breakout for detecting buttons
*/

Adafruit_SSD1306 display(OLED_RESET);
int speed = 0;
int currKey = NONE;
char displayOutput[50];

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Torch Song\r\nv0.1");
  display.display();
  delay(500);

}

int getKey() {
	int inputVal = analogRead(A0);
	if(inputVal < RIGHT + 20) return RIGHT;
	if(inputVal < UP + 20) return UP;
	if(inputVal < DOWN + 20) return DOWN;
	if(inputVal < LEFT + 20) return LEFT;
	if(inputVal < SELECT + 20) return SELECT;
	return NONE;
	
}

void speedUp() {
	speed = speed + 10;
	if(speed > 255) speed = 255;
	analogWrite(3, speed);
}

void speedDown() {
	speed = speed - 10;
	if(speed < 0) speed = 0;
	analogWrite(3, speed);
}

void loop() {

	int keyPressed = getKey();
	switch(keyPressed) {
		// case NONE:  
		// 	keyName = "None";
		// 	break;
		// case SELECT: 
		// 	keyName = "Select";
		// 	break;
		// case LEFT: 
		// 	keyName = "Left";
		// 	break;
		case DOWN: {
			speedDown();
			delay(100);
			break;
		}
		// case RIGHT: 
		// 	keyName = "Right";
		// 	break;
		case UP: {
			speedUp();
			delay(100);
			break;
		}
		default:
			break;
	}
	display.clearDisplay();
	display.setCursor(0,0);
	sprintf(displayOutput, "Speed: %d\nKeypressed: %d", speed, keyPressed);
	display.print(displayOutput);
	display.display();
  
}
