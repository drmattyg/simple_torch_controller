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

Adafruit_SSD1306 display(OLED_RESET);
void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Torch Song");
  display.display();
  delay(200);

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

void loop() {
	char* keyName;
	switch(getKey()) {
		case NONE:  
			keyName = "None";
			break;
		case SELECT: 
			keyName = "Select";
			break;
		case LEFT: 
			keyName = "Left";
			break;
		case DOWN: 
			keyName = "Down";
			break;
		case RIGHT: 
			keyName = "Right";
			break;
		case UP: 
			keyName = "Up";
			break;
		default:
			"wat";
			break;
	}
	display.clearDisplay();
	display.setCursor(0, 0);
	display.println(keyName);
	display.setCursor(0, 16);
	display.println(getKey());
	display.display();
  
}
