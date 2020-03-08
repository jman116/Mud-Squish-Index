//################################INCLUDES#######################################################
//
#include "LedControl.h"                                                                              //Library used to control the LED Matrices
//
//################################USER SET VARIABLES#############################################
//
double heatTime = 6;                                                                                 //time in minutes to run the heat portion of the measurement device, later converted to milliseconds
int intensity = 5;                                                                                   //Value from 1 -> 15, 1 being lowest brightness on the LED Matrix
int count = 0;                                                                                       //Used to keep track of the loops
//
//
//################################HARD CODED VARIABLES###########################################
//
LedControl disp = LedControl(12, 11, 10, 4);                                                         //12 = Data in, 11 = CLK, 10 = LOAD, Num of attached LEDS = 4, this initializes the LED Matrix panel
                                                                                                     //Below are all the letters used for the LED Matrices
//byte s[] = {B‭01110011‬, B‭11111100‬, B‭11000000‬, B‭11111100‬, B‭01111110‬, B0000‭0110‬, B‭01111110‬, B0‭0011100‬};
  byte s[] = {B01111100, B11111100, B11000000, B11111100, B01111110, B00000110, B01111110, B01111100};
//byte a[] = {B‭00111100‬, B‭01100110‬, B‭01100110‬, B‭01111110‬, B‭01111110‬, B‭01100110‬, B‭01100110‬, B‭01100110‬};
  byte a[] = {B00111100, B01100110, B01100110, B01111110, B01111110, B01100110, B01100110, B01100110};
//byte f[] = {B‭11111110‬, B‭11111000‬, B‭11000000‬, B‭11000000‬, B‭11111110‬, B‭11111000‬, B‭11000000‬, B‭11000000‬};
  byte f[] = {B11111110, B11111000, B11000000, B11000000, B11111110, B11111000, B11000000, B11000000};
//byte e[] = {B‭11111110‬, B‭11111100‬, B‭11000000‬, B‭11111100‬, B‭11111100‬, B‭11000000‬, B‭11111100‬, B‭11111110‬};
  byte e[] = {B11111110, B11111100, B11000000, B11111100, B11111100, B11000000, B11111100, B11111110};
//byte n[] = {B‭11100011‬, B‭11110011‬, B‭11110011‬, B‭11111011‬, B‭11011111‬, B‭11001111‬, B‭11001111‬, B‭11000111‬};
  byte n[] = {B11100010, B11110010, B11110010, B11111010, B11011110, B11001110, B11001110, B11000110};
//byte o[] = {B‭11111110‬, B‭11111110‬, B‭11000110‬, B‭11000110‬, B‭11000110‬, B‭11000110‬, B‭11111110‬, B‭11111110‬};
  byte o[] = {B11111110, B11111110, B11000110, B11000110, B11000110, B11000110, B11111110, B11111110};
//byte g[] = {B‭11111110‬, B‭11111110‬, B‭11000000‬, B‭11011100‬, B‭11011110‬, B‭11000110‬, B‭11111110‬, B‭11111110‬};
  byte g[] = {B11111110, B11111110, B11000000, B11011100, B11011110, B11000110, B11111110, B11111110};
//byte t[] = {B‭01111110‬, B‭01111110‬, B‭00011000‬, B‭00011000‬, B‭00011000‬, B‭00011000‬, B‭00011000‬, B‭00011000‬};
  byte t[] = {B01111110, B01111110, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
//byte b[] = {B‭11111000‬, B‭11001100‬, B‭11000110‬, B‭11111100‬, B‭11000100‬, B‭11000110‬, B‭11111110‬, B‭11111100‬};
  byte b[] = {B11111000, B11001100, B11000110, B11111100, B11000100, B11000110, B11111110, B11111100};
//byte u[] = {B‭11000011‬, B‭11111110‬, B‭11000110‬, B‭11000110‬, B‭11000110‬, B‭11000110‬, B‭11111110‬, B‭11111110‬};
  byte u[] = {B11000110, B11000110, B11000110, B11000110, B11000110, B11000110, B11111110, B11111110};
//byte y[] = {B‭01000010‬, B‭01100110‬, B‭01111110‬, B‭00111100‬, B‭00011000‬, B‭00011000‬, B‭00011000‬, B‭00011000‬};
  byte y[] = {B01000010, B01100110, B01111110, B00111100, B00011000, B00011000, B00011000, B00011000};
                                              
void displayLetter(byte letter[], int square);                                                       //Method blueprints          
void displaySAFE();
void displayNOGO();
void displayBUSY();

void setup() {
  heatTime = ((heatTime * 60) / .001);                                                               //convert heatTime from minutes to miliseconds
  for (int i = 0; i < 5; i++) {
    disp.shutdown(i, false);                                                                         //Wake LED Matrix Panel from sleep mode
    disp.setIntensity(i, intensity);                                                                 //Set the intensity of the LED Matrix Panel to the value requested above
    disp.clearDisplay(i);                                                                            //Clear the display in case any errant 1's were activated
  }
  pinMode(9, INPUT);                                                                                 //Used to get data from the MMS (Mud Moisture Sensor)
  pinMode(8, OUTPUT);                                                                                //Used to manipulate the relay                                                                        
}

void loop() {
  delay(1);                                                                                          //Delay 1ms
  heatTime--;                                                                                        //Decrement the timer
  if(heatTime <= 0 && digitalRead(9) == HIGH){                                                       //Statement TRUE if sample is WET and heatTime is 0 or NEGATIVE
    while(1==1){
      digitalWrite(8, LOW);                                                                          //Switches the relay (heat gun) off
      displayNOGO();                                                                                 //Displays NOGO on the LED Matrix Panel
    }
  }else if(heatTime > 0 && digitalRead(9) == LOW){                                                   //Statement TRUE if sample is DRY and heatTime is above 0
    while(1==1){;                                                                                    
      digitalWrite(8, LOW);                                                                          //Switches the relay (heat gun) off
      displaySAFE();                                                                                 //Displays SAFE on the LED Matrix Panel
    }
  }else if (cycle == 0) {
    
    displayBUSY();                                                                                   //Displays SAFE on the LED Matrix Panel
    digitalWrite(8, HIGH);                                                                           //Switches the relay (heat gun) off
    cycle++;
    
  }

}
void displayBUSY(){
  
    for (int i = 0; i < 5; i++) {
     disp.clearDisplay(i);                                                                           //Clear the display in case any errant 1's were activated
    }  
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(b[i], 3, i);
     delay(50);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(u[i], 2, i);
     delay(50);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(s[i], 1, i);
     delay(50);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(y[i], 0, i);
     delay(50);
    }
}
void displaySAFE(){
    delay(1000);
    for (int i = 0; i < 5; i++) {
      disp.clearDisplay(i);                                                                          //Clear the display in case any errant 1's were activated
    }  
    delay(1000);
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(s[i], 3, i);
     delay(1);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(a[i], 2, i);
     delay(1);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(f[i], 1, i);
     delay(1);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(e[i], 0, i);
     delay(1);
     
    }
}

void displayNOGO(){
    delay(1000);
    for (int i = 0; i < 5; i++) {
      disp.clearDisplay(i);                                                                          //Clear the display in case any errant 1's were activated
    }  
    delay(1000);
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
      displayLetter(n[i], 3, i);
      delay(1);
     }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(o[i], 2, i);
     delay(1);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(g[i], 1, i);
     delay(1);
    }
    for (int i = 0; i < 9; i++) {                                                                    //Loop to iterate through array that contains on/off information for the matrix specified
     displayLetter(o[i], 0, i);
     delay(1);
    }
    
}
void displayLetter(byte letter, int square, int i) {

    disp.setRow(square, i, letter);                                                                  //Sends a byte to the row of a chosen matrix

  }
