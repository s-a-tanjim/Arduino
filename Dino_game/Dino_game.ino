// MCUFRIEND_kbv and Adafruit_GFX library for TFT display
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

// Screen direction
#define DIRECTION_OF_SCREEN 1

// wiring TFT display with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0
//   LCD_WR   connects to Analog pin A1
//   LCD_RS   connects to Analog pin A2
//   LCD_CS   connects to Analog pin A3
//   LCD_RST  connects to Analog pin A4
//   LCD_D0   connects to digital pin 8
//   LCD_D1   connects to digital pin 9
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7

// wiring Joystick with Mega2560
// VRx  connects to Analog pin A6
// VRy  connects to Analog pin A7
// SW   connects to digital pin 31

// wiring Buzzer with Mega2560
// +Ve  connects to digital pin 33


// Pin Define   ....................................................................

// TFT pin define
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3    // Chip Select goes to Analog 3
#define LCD_CD A2    // Command/Data goes to Analog 2
#define LCD_WR A1    // LCD Write goes to Analog 1
#define LCD_RD A0    // LCD Read goes to Analog 0

// Joystick pin define
#define VRx A6
#define VRy A7
#define SW 31

// Buzzer pin define
#define BUZZER 33

// 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


// Initialize tft for TFT display
MCUFRIEND_kbv tft;


// Position of Dino, Tree & Ground define 
#define DINO_BASE_POINT_X 40
#define DINO_BASE_POINT_Y 154
#define GROUND_BASE_POINT 200
#define TREE_BASE_POINT_Y 160


//Variables

// Stores present position of Tree and Dino
int dino_y_pos = DINO_BASE_POINT_Y;
int tree_x_pos = 480; // 480 is the width of screen

// Stores previous position of Dino and Tree to clear the screen
int trex_prev_pos_x=DINO_BASE_POINT_X;
int trex_prev_pos_y=DINO_BASE_POINT_Y;
int tree_prev_pos_x=tree_x_pos;
int tree_prev_pos_y=TREE_BASE_POINT_Y;

// Joystick value
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;   // 1 or 0
int mapX = 0;
int mapY = 0;

// For Game
boolean playState = false; 
//the game starts only when this becomes true
// This is a common method used in coding games
unsigned int highScore = 0;     // Stores HighScore
unsigned int score = 0;         // Stores present score
int gameSpeed = 1;              // Speed of Tree
boolean gameOverMsgFlag=true;
// After showing gameOver massage this flag will set False so that
// gameOver massage shows only 1 time

// Custom functions for game
#include "utility_func.h"
#include "game_func.h"


void setup()
{
  Serial.begin(9600);

  // Joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // TFT
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(DIRECTION_OF_SCREEN);
  welcomeMsg();   // Show welcome message
}

void loop()
{
  // Reads data from joystick
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  /*
  // Printing data for debugging
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  */

  if (!playState)
  {
    if (highScore != 0)
    {
      if(gameOverMsgFlag)
      {
        gameOverMsg(highScore,score);
        gameOverMsgFlag=false;
        stop_buzzer();
      }
    }
    if (SW_state == 0)    //Button pressed from joystick!
    {
      playState = true;
      score=0;      // Score sets to zero
      tft.fillScreen(WHITE);  // Screen color sets white
      printLand();  // Land will print here
      t_rex(DINO_BASE_POINT_X,DINO_BASE_POINT_Y);   // Dino will print here
    }
  }

  if (playState)
  {
    startGame();
  }

  delay(5);
}
