// This sketch has been Refurbished by BUHOSOFT
// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
#define DEBUG
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9 // can be a digital pin
#define XP 8 // can be a digital pin

#define TS_MINX 960
#define TS_MINY 150
#define TS_MAXX 150
#define TS_MAXY 940

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

// which window is loaded 0 = main window, 1 = measurement window
int currentWindow = 0;  
// declare variables for cursor settings [x, y]
int cursorStartDate[] = {15, 0};
int cursorStartTimeHour[] = {280, 0};
int cursorStartTimeMin[] = {297, 0};
int cursorStartStatus[] = {80, 230};

unsigned long setupLogWindow() {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  currentWindow = 1;

  // Draw Lines
  tft.drawLine(0, 45, 320, 45, WHITE);
  tft.drawLine(0, 155, 320, 155, WHITE);
  tft.drawLine(0, 220, 320, 220, WHITE);
    
  // Set date and time text 
  tft.setCursor(cursorStartDate[0], cursorStartDate[1]);
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(1);
  tft.println("04. April 2016");
  tft.setCursor(cursorStartTimeHour[0], cursorStartTimeHour[1]);
  tft.println("07");
  tft.setCursor(292, 0);
  tft.println(":");
  tft.setCursor(cursorStartTimeMin[0], cursorStartTimeMin[1]);
  tft.println("25");

  // Set program name
  tft.setTextColor(RED, BLACK);  tft.setTextSize(2);
  tft.setCursor(75, 20);
  tft.println("Lars Gartenhilfe");
  
  // Some Text
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(2);
  tft.setCursor(10, 53);
  tft.println("Beet 1 Bodenfeuchte: 80%");
  tft.setCursor(10, 73);
  tft.println("Beet 2 Bodenfeuchte: 75%");
  tft.setCursor(10, 93);
  tft.println("Luftfeuchtigkeit: 20%");
  tft.setCursor(10, 113);
  tft.println("Temperatur: 26 Grad");

  // Logs Button
  tft.fillRect(200, 172, 102, 32, CYAN);
  tft.drawRect(199, 171, 102, 32, WHITE);
  tft.setTextColor(WHITE, CYAN);  tft.setTextSize(2);
  tft.setCursor(225, 181);
  tft.println("Main");
  
  return micros() - start;
}

unsigned long setupMainWindow() {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  currentWindow = 0;
  // Set white lines
  tft.drawLine(0, 45, 320, 45, WHITE);
  tft.drawLine(160, 45, 160, 155, WHITE);
  tft.drawLine(0, 155, 320, 155, WHITE);
  tft.drawLine(0, 220, 320, 220, WHITE);
  
  // Set date and time text 
  tft.setCursor(15, 0);
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(1);
  tft.println("04. April 2016");
  tft.setCursor(280, 0);
  tft.println("07");
  tft.setCursor(292, 0);
  tft.println(":");
  tft.setCursor(297, 0);
  tft.println("25");

  // Set program name
  tft.setTextColor(RED, BLACK);  tft.setTextSize(2);
  tft.setCursor(75, 20);
  tft.println("Lars Gartenhilfe");

  // Set zone 1
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(2);
  tft.setCursor(40, 53);
  tft.println("Beet 1");
  // Startbutton zone 1
  tft.fillRect(25, 90, 100, 30, GREEN);
  tft.drawRect(24, 89, 102, 32, WHITE);
  tft.setTextColor(WHITE, GREEN);  tft.setTextSize(2);
  tft.setCursor(45, 97);
  tft.println("Start");

  // Set zone 2
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(2);
  tft.setCursor(210, 53);
  tft.println("Beet 2");
  // Startbutton zone 2
  tft.fillRect(200, 90, 100, 30, GREEN);
  tft.drawRect(199, 89, 102, 32, WHITE);
  tft.setTextColor(WHITE, GREEN);  tft.setTextSize(2);
  tft.setCursor(220, 97);
  tft.println("Start");

  // Stop Button
  tft.fillRect(25, 172, 102, 32, RED);
  tft.drawRect(24, 171, 102, 32, WHITE);
  tft.setTextColor(WHITE, RED);  tft.setTextSize(2);
  tft.setCursor(50, 181);
  tft.println("Stop");

  // Logs Button
  tft.fillRect(200, 172, 102, 32, CYAN);
  tft.drawRect(199, 171, 102, 32, WHITE);
  tft.setTextColor(WHITE, CYAN);  tft.setTextSize(2);
  tft.setCursor(225, 181);
  tft.println("Werte");
  
  // Set status text
  tft.setCursor(cursorStartStatus[0], cursorStartStatus[1]);
  tft.setTextColor(WHITE, BLACK);  tft.setTextSize(1);
  tft.println("Place for status messages...");
  return micros() - start;
}

void setup(void) {
  Serial.begin(9600);
  tft.reset();

  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);  tft.setTextSize(1);
    tft.println("Initialize Display!");
    delay(1000);
  }
  tft.fillScreen(BLACK);
  setupMainWindow();
}


void loop(void) {  
 //  digitalWrite(13, HIGH);
  // Recently Point was renamed TSPoint in the TouchScreen library
  // If you are using an older version of the library, use the
  // commented definition instead.
  // Point p = ts.getPoint();
  TSPoint p = ts.getPoint();
 // digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
 
    // scale from 0->1023 to tft.width
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));

    if(p.x >160 && p.x < 210 && p.y > 20 && p.y < 95){
      Serial.println("Button 1 gedrueckt");
    }
    else if(p.x >160 && p.x < 210 && p.y > 150 && p.y < 220){
      Serial.println("Button 2 gedrueckt");
    }
    else if(p.x > 60 && p.x < 100 && p.y > 20 && p.y < 90){
      Serial.println("Stop Button gedrueckt");
    }
    else if(p.x > 60 && p.x < 100 && p.y > 150 && p.y < 220){
      Serial.println("Log Button gedrueckt");
      if (currentWindow == 1){
          setupMainWindow();
        } 
      else if (currentWindow == 0){
          setupLogWindow(); 
        }      
    }
    // Serial.print("X = "); Serial.print(p.x);
    // Serial.print("\tY = "); Serial.print(p.y);
    // Serial.print("\tPressure = "); Serial.println(p.z);
  }
}

unsigned long setDate() {
  unsigned long start = micros();
  
  return micros() - start;
}


unsigned long setTimeHour() {
  unsigned long start = micros();
  
  return micros() - start;
}

unsigned long setTimeMin() {
  unsigned long start = micros();
  
  return micros() - start;
}

unsigned long setStatusText() {
  unsigned long start = micros();
  
  return micros() - start;
}
