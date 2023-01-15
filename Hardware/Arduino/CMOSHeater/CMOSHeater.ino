/* Code modified and adapted from the below credits
   menus and cycles completely changed
   adapted to use adafruit liquid crystal
  Richard Matthews 03 January 2018 Australia

*/

/* Rebuilt by Doug 07/02/2017 Australia.
   This is a bare bones menu using buttons to navigate and select, there are no special libraries,
   I am using an I2C LCD2004, but any display will work with minor mods. This has been translated from,
   I believe Slovakian, that was fun, stripped down and modified for button control, I have found that
   buttons are less picky than rotary encoders, even the good ones, just my experience.
   I believe that I have removed all unnecessary script, but I may have missed some.
   look at the last 2 --page()-- sections for instruction on extending down even further, I don't think
   that there is a limit to how many levels you can have, how many do you really need.
   The original sketch is from: Stanislav Petrek of Slovakia, you can find sketch on YouTube comments.
   https://www.youtube.com/watch?v=gIP29m12wjQ&t=41s
   Have fun with the translation  ;-}
   The last thing I did before posting was to relaod and test this sketch, so it works.
*/


#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_MCP9808.h"
#include "PID_v1.h"


// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

//LCD setup code

Adafruit_LiquidCrystal lcd(0);

byte customChar[] = {     //custom character 0 which will print the line at the absolute top of the screen as a cursor indicator
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte customDegree[] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


// menu system
int poz = 0; //  cursor position on actual page
int poz_max = 4;
int poz_min = 1;
String str[2];
int poz_x = 0;
int poz_x_max = 60;
int poz_x_min = 0 ;

int pozOld = 0;
int pozNew = 0;

int page = 0; //  actual page
int page_max = 3;
int page_min = 0;

int press = 0;
int press_max = 1;

int keypad_pin = A0;                      //analoge A0 to sense button values.
int keypad_value = 0;
int sensor_value = 0;
int keypad_value_old = 0;
char btn_push;

//Richard Variables

int cur_page = 99;


int debounce = 50;
char lastValues[2] = {'a', 'a'};

//"Binary" Flags
int fan = 0;  //Fan Flag - options 0,1,2
int previousFanMode;
int runner = 0; // run flag
double temp_setpoint = 21; // initial temperature setpoint degrees celsius
int modes = 0;
int previousModes;
String modeNames[] = {"   HEAT             ", "   COOL             "};
int runningMode = 0;

int screen_change = 1; //print screen flag


//h bridge setup
// PWM is connected to pin 3.
const int pinPwm = 3;

// DIR is connected to pin 2.
const int pinDir = 2;


// Speed of the motor.
static int iSpeed = 0;

// Acceleration of the motor.
static int iAcc = 1;

double c, Output;

long time = 0;

int debounce_count = 10;

/****************************************************************setup*****************************************
   This is the setup function for the arduino code.
   this code will run once and is needed regardless of what happens within the main body of the code.
 **************************************************************************************************************/



PID coolerPID(&c, &Output, &temp_setpoint, 2, 5, 1, REVERSE);
PID heaterPID(&c, &Output, &temp_setpoint, 10, 0.5, 1, DIRECT);

void setup() {
  Serial.begin(9600);
  Serial.println("CMOS Heater V1.0");
  lcd.begin(20, 4);
  Serial.println("LCD initialised");
  lcd.clear();
  lcd.home();


  //Relay Pins
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);


  lcd.createChar(0, customChar);
  lcd.createChar(1, customDegree);

  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    lcd.setCursor(0,0);
    lcd.print("MCP ERROR");
    while (1);
  }

  c = tempsensor.readTempC();
  

  pinMode(pinPwm, OUTPUT);
  pinMode(pinDir, OUTPUT);

  coolerPID.SetMode(AUTOMATIC);
  heaterPID.SetMode(AUTOMATIC);
  Serial.println("End Setup Routine");

}


char *debug = malloc(5);

/************************************************************loop************************************************
   Main loop of Arduino Code.
  ***************************************************************************************************************/
void loop() {


  MainmenuBtn(); //

  //Debug Statements
  //sprintf(debug,"The value of the variables are as follows:\n Press: %02d\n poz: %02d\n page: %02d\n cur_page: %02d", press, poz, page, cur_page);
  //Serial.println(debug);


  // page select
  switch (page) {
    case 0:
      page0(); //Home
      break;
    case 1:
      page1(); //Set Point
      break;
    case 2:
      page2(); // Mode
      break;
    case 3:
      page3(); //Fan
      break;
    case 4:
      page4(); //Run
      break;
  }


}


char *reading;
char *current_state;
int counter = 0;

//****************************************************Button Control************************************************
void MainmenuBtn() {
  char sensor_value = "x";
  btn_push = ReadKeypad(); // check to see if buttons have been pushed
  //btn_push = ReadKeypad();
  /* decode buttons based on the following code
       S - Select             --> press++
       B - Back (Home button) --> page = 0
       U - Up                 --> poz--
       D - Down               --> poz++
       R - Right              --> poz_x++
       L - Left               --> poz_x--

    - empty character does nothing
  */

  //  int updateOutput = 1;
  //
  //  for (int i = 0; i < 2; i++) {
  //    if (lastValues[i] != sensor_value) {
  //      updateOutput = 0;
  //    }
  //
  //    if (i > 0) {
  //      lastValues[(i - 1)] = lastValues[i];
  //    }
  //  }
  //
  //  if (updateOutput == 1) {
//
//  if (millis() != time) {
//    reading = sensor_value;
//
//    if (reading == current_state && counter > 0)
//    {
//      counter--;
//    }
//    if (reading != current_state)
//    {
//      counter++;
//    }
//    // If the Input has shown the same value for long enough let's switch it
//    if (counter >= debounce_count)
//    {
//      counter = 0;
//      btn_push = reading;
//
//    }
//    time = millis();
//  }

  //  }
  //  else {
  //    btn_push = " ";
  //  }
  //
  //  lastValues[1] = sensor_value;

  //sprintf(debug,"updateOutput: %01d.\n btn_push: %s.\n Sensor_value: %s.\n", updateOutput, btn_push, sensor_value);
  //Serial.print(debug);




  if (btn_push == 'S') { //enter selected menu
    press++;
    sprintf(debug, "Pushed: Select variable press now equals: %01d\n", press);
    Serial.print(debug);
    delay(debounce);
    if (press > press_max) {
      press = 0;
    }
  }

  else if (btn_push == 'B') {
    //instantly go back home
    sprintf(debug, "Pushed: Home variable Page now equals: %01d\n", page);
    Serial.print(debug);
    delay(debounce);
    page = 0;
    cur_page = 5;
  }

  else if (btn_push == 'U') {
    poz--;
    sprintf(debug, "Pushed: up variable poz now equals: %01d\n", poz);
    Serial.print(debug);
    delay(debounce);
    if (poz < poz_min) {
      poz = poz_max;
    }

  }

  else if (btn_push == 'D') {
    poz++;
    sprintf(debug, "Pushed: Down variable poz now equals: %01d\n", poz);
    Serial.print(debug);
    if (poz > poz_max) {
      poz = poz_min;
    }
  }

  else if (btn_push == 'R') {
    Serial.print("Right"); Serial.print("\n");
    delay(debounce);
    poz_x++;
    if (poz_x > poz_x_max) {
      poz_x = poz_x_min;
    }
  }

  else if (btn_push == 'L') {
    Serial.print("Left"); Serial.print("\n");
    delay(debounce);
    poz_x--;
    if (poz_x < poz_x_min) {
      poz_x = poz_x_max;
    }
  }

}







/*************************************************************read buttons***********************************
  Edited by Richard Matthews to include double sided limits and added the final else case.

  Buttons return one of the following characters
  R - Right
  D - Down
  U - Up
  L - Left
  S - Select
  B - Back (Home button)
    - empty character does nothing
 **********************************************************************************************************/
char ReadKeypad() {
  //Serial.println("In ReadKeyPad");
  int bufferSize = 3;
  int averager[bufferSize] = {};

  keypad_value = analogRead(keypad_pin);

//  for (int i = 0; i < bufferSize; i++) {
//    averager[i] = analogRead(keypad_pin);
//    sprintf(debug,"averager at position %01d: %03d.\n",i, averager[i]);
//    Serial.print(debug);
//    //delay(500);
//  }
//
//
//  for (int i = 0; i < bufferSize; i++) {
//
//    if (i == 0) {
//      keypad_value == averager[i];
//    }
//    else {
//      keypad_value = (keypad_value + averager[i]) / 2;
//    }
//
//  }

  //sprintf(debug,"keypad_value: %03d.\n", keypad_value);
  //Serial.print(debug);
  //delay(500);

  //Serial.println(keypad_value);
  if (keypad_value > 680 && keypad_value < 720) {
    while (keypad_value > 680) {
      keypad_value = analogRead(keypad_pin);
    }
    return 'R';
  }
  else if (keypad_value > 920 && keypad_value < 955) {
    while (keypad_value > 920) {
      keypad_value = analogRead(keypad_pin);
      //waiting for button release
    }
    return 'D'; //down
  }
  else if (keypad_value > 585 && keypad_value < 640) {
    while (keypad_value > 585) {
      keypad_value = analogRead(keypad_pin);
      //waiting for button release
    }
    return 'U'; //up
  }
  else if (keypad_value > 860 && keypad_value < 880) {
    while (keypad_value > 860) {
      keypad_value = analogRead(keypad_pin);
      //waiting for button release
    }
    return 'L'; //left
  }
  else if (keypad_value > 830 && keypad_value < 850) {
    while (keypad_value > 830) {
      keypad_value = analogRead(keypad_pin);
      //waiting for button release
    }
    return 'S'; //select
  }
  else if (keypad_value > 550 && keypad_value < 575) {
    while (keypad_value > 550) {
      keypad_value = analogRead(keypad_pin);
      //waiting for button release
    }
    return 'B'; //Return
  }
  else {
    return ' ';
  }
}








//*******************************************************Front Page 0*******************************************
void page0() {

  poz_min = 0;
  poz_max = 3;
  press_max = 1;



  if (cur_page != page) {
    lcd.setCursor(0, 0);
    lcd.print("   Set Point        ");
    lcd.setCursor(0, 1);
    lcd.print("   Mode             ");
    lcd.setCursor(0, 2);
    lcd.print("   Fan              ");
    lcd.setCursor(0, 3);
    lcd.print("   Run              ");
    cur_page = page;
    Serial.println("Finished printing home screen");
  }



  switch (poz) {
    case 0:

      //draw cursor
      lcd.setCursor(0, 0);
      lcd.print("->");

      //remove all other cursors
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 2);
      lcd.print("  ");
      lcd.setCursor(0, 3);
      lcd.print("  ");

      if (press == 1) {
        press = 0;
        poz = 0;
        page = 1;
      }
      break;
    case 1:
      //draw cursor
      lcd.setCursor(0, 1);
      lcd.print("->");

      //remove all other cursors
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 2);
      lcd.print("  ");
      lcd.setCursor(0, 3);
      lcd.print("  ");

      if (press == 1) {
        press = 0;
        poz = 0;
        page = 2;
      }
      break;
    case 2:
      //draw cursor
      lcd.setCursor(0, 2);
      lcd.print("->");

      //remove all other cursors
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 3);
      lcd.print("  ");


      // action for when pressed
      if (press == 1) {
        press = 0;
        poz = 0;
        page = 3;
      }


      break;
    case 3:
      //draw cursor
      lcd.setCursor(0, 3);
      lcd.print("->");

      //remove all other cursors
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 2);
      lcd.print("  ");

      if (press == 1) {
        press = 0;
        poz = 0;
        page = 4;
      }
      break;
  }
}









//*************************************************Set Point*****************************************
void page1() {
  poz_min = 0;
  poz_max = 2;
  press_max = 1;

  poz_x_max = 60;
  poz_x_min = 0;

  if (cur_page != page) {
    lcd.setCursor(0, 0);
    lcd.print(" ****SET  POINT**** ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("  ");
    lcd.setCursor(3, 2);
    lcd.print(temp_setpoint); lcd.write(1); lcd.print("C");
    lcd.setCursor(0, 3);
    lcd.print("    Return          ");
    cur_page = page;
  }

  switch (poz) {

    case 0:
      //draw cursor


      // action if pressed
      if (press == 1) {
        press = 0;
      }
      break;

    case 1:
      //draw screen

      lcd.setCursor(0, 2);
      lcd.print("->");

      lcd.setCursor(0, 3);
      lcd.print("  Return            ");


      //action if pressed
      if (press == 1) {
        press = 0;
        setTemp(3);
      }
      break;

    case 2:
      //draw screen
      lcd.setCursor(0, 3);
      lcd.print("->  Return          ");

      lcd.setCursor(0, 2);
      lcd.print("  ");


      //action if pressed
      if (press == 1) {
        press = 0;
        page = 0;
        poz = 0;
      }

      break;
  }
}







//*************************************************MODE*****************************************
void page2() {
  poz_min = 0;
  poz_max = 2;
  press_max = 1;





  /*
     The mode section is responsible for setting the flag that controls whether the setpoint is less than or greater than during the running screen.
  */
  if (cur_page != page) {
    lcd.setCursor(0, 0);
    lcd.print("    ****MODE****    ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("  ");
    lcd.setCursor(0, 2);
    lcd.print(modeNames[modes]);
    lcd.setCursor(0, 3);
    lcd.print("    Return          ");
    cur_page = page;
  }



  switch (poz) {

    case 0:
      //draw cursor
      lcd.setCursor(0, 2);
      lcd.print("   ");
      lcd.setCursor(0, 3);
      lcd.print("   ");

      // action if pressed
      if (press == 1) {
        press = 0;
      }
      break;

    case 1:
      lcd.setCursor(0, 2);
      lcd.print("-> ");
      lcd.setCursor(0, 3);
      lcd.print("   ");

      if (press == 1) {
        press = 0;
        modes++;

        if (modes == 2) {
          modes = 0;
        }

        if (previousModes != modes) {
          lcd.setCursor(0, 2);
          lcd.print("                    ");
          lcd.setCursor(0, 2);
          lcd.print(modeNames[modes]);
          previousModes = modes;
          Serial.print("Calling modeChange with Mode as: "); Serial.println(modeNames[modes]);

        }
      }
      break;

    case 2:
      //draw screen
      lcd.setCursor(0, 2);
      lcd.print("  ");
      lcd.setCursor(0, 3);
      lcd.print("->  ");

      //action if pressed
      if (press == 1) {
        press = 0;
        page = 0;
        poz = 0;
      }

      break;
  }
}




//*************************************************FAN MODE*****************************************
void page3() {
  poz_min = 0;
  poz_max = 2;
  press_max = 1;



  String fanmodes[] = {"   AUTO             ", "   OFF              ", "   ON               "};
  //fanmode = fanmodes[i];
  if (cur_page != page) {
    lcd.setCursor(0, 0);
    lcd.print("****FAN  CONTROL****");
    lcd.setCursor(0, 1);
    lcd.print("                    ");



    lcd.setCursor(0, 2);
    lcd.print(fanmodes[fan]);

    lcd.setCursor(0, 3);
    lcd.print("   Return           ");
    cur_page = page;
  }
  switch (poz) {
    case 0:
      lcd.setCursor(0, 2);
      lcd.print("   ");


      if (press == 1) {
        press = 0;
      }
      break;

    case 1:

      lcd.setCursor(0, 2);
      lcd.print("-> ");
      lcd.setCursor(0, 3);
      lcd.print("   ");

      //actions
      if (press == 1) {
        press = 0;
        fan++;

        if (fan == 3) {
          fan = 0;
        }

        if (previousFanMode != fan) {
          lcd.setCursor(0, 2);
          lcd.print("                    ");
          lcd.setCursor(0, 2);
          lcd.print(fanmodes[fan]);
          previousFanMode = fan;
          Serial.print("Calling FanRun with Fan as: "); Serial.println(fanmodes[fan]);
          FanRun(fan);
        }
      }

      break;

    case 2:
      lcd.setCursor(0, 2);
      lcd.print("   ");
      lcd.setCursor(0, 3);
      lcd.print("-> Return           ");
      if (press == 1) {
        press = 0;
        page = 0;
        poz = 2;
      }
      break;
  }

}












//*************************************************Run Screen*****************************************
void page4() {
  poz_min = 0;
  poz_max = 1;
  press_max = 1;

  c = tempsensor.readTempC();
  String runner[2] = {"    ****OFF****     ", "    ****RUN****     "};

  if (cur_page != page) {
    lcd.setCursor(0, 0);
    lcd.print(runner[runningMode]);
    lcd.setCursor(0, 1);
    lcd.print("Current= "); //9 characters
    lcd.print(c, 2);
    lcd.setCursor(9, 1);

    lcd.setCursor(0, 2);
    lcd.print(modeNames[modes]); lcd.setCursor(7, 2); lcd.print(" to "); lcd.print(temp_setpoint); lcd.setCursor(13, 2); lcd.write(1); lcd.print("C");
    lcd.setCursor(0, 3);
    lcd.print("    Return          ");
    cur_page = page;
  }

  if (runningMode == 1) {
    lcd.setCursor(0, 1);
    lcd.print("Current= "); //9 characters
    lcd.print(c, 2);
    lcd.setCursor(9, 1);
  }

  peltier(runningMode, c);

  switch (poz) {

    case 0:
      lcd.setCursor(0, 0);
      lcd.print("    ***********     ");
      lcd.setCursor(0, 0);
      lcd.print(runner[runningMode]);
      lcd.setCursor(0, 1);
      if (runningMode == 1) {
        lcd.setCursor(0, 1);
        lcd.print("Current= "); //9 characters
        lcd.print(c, 2);
        lcd.setCursor(9, 1);
      }
      lcd.setCursor(0, 3);
      lcd.print("    ");

      if (press == 1) {
        press = 0;
        runningMode++;
        if (runningMode == 2) {
          runningMode = 0;
        }
        break;

      case 1:
        lcd.setCursor(0, 0);
        lcd.print(runner[runningMode]);
        if (runningMode == 1) {
          lcd.setCursor(0, 1);
          lcd.print("Current= "); //9 characters
          lcd.print(c, 2);
          lcd.setCursor(9, 1);
        }
        lcd.setCursor(0, 3);
        lcd.print("--> Return          ");
        if (press == 1) {
          press = 0;
          page = 0;
          poz = 4;
        }
        break;
      }
  }
}













/* * * * * setTemp * * * *

   Function is used to set the setpoint within the LCD screen. this will change the temperature setpoint flag which contains the value that
   we will also draw down upon to check and compare against when powering the peltier plate device.

   Take in location as i on the screen where we want to write the location of the setpoint
   output character to the LCDs.

   RICHARD MATTHEWS

*/

char setTemp(int i) {
  //variable declerations
  int result;
  boolean Exit = false;
  poz = 0;
  poz_x = 0;
  char *str = malloc(5);

  //main routine
  while (!Exit) {
    MainmenuBtn();//check buttons for press
    Serial.println("Returned to SetTemp");
    lcd.setCursor(i, 2);                // ser cursor
    temp_setpoint = double(poz_x);              // set point is how many times we press the left or right buttons
    Serial.print("poz_x is: "); Serial.println(poz_x);
    Serial.print("TempSetpoint is: "); Serial.println(temp_setpoint);
    //sprintf(str, "%02d", temp_setpoint); // convert the number to string to print to LCD
    lcd.print(temp_setpoint,2);

    if (press == 1) {                 //variable set to '1' when the 'S' key is pressed
      press = 0;
      Exit = true;
    }
  }
}




void FanRun(int fan) {

  switch (fan) {

    case 0: //auto
      digitalWrite(4, HIGH); //fan relay ON
      Serial.println("Turning Fan to Auto");
      break;

    case 1: //off
      digitalWrite(4, LOW); //fan relay OFF
      Serial.println("Turning Fan to OFF");
      break;

    case 2: //on
      digitalWrite(4, HIGH); //fan relay ON
      Serial.println("Turning Fan to ON");
      break;

  }
}

void peltier(int runningMode, double c) {

  /*
     Some notes on power settings to the peltier:
      - 254 is full power
      - 0 is off
      - 50 is not enough to stablisie the temperature.
      - 150 is enough to push the temperature down further.
  */


  switch (runningMode) {
    case 0:
      //off
      analogWrite(pinPwm, 0); //turn peltier OFF
      break;

    case 1:
      //run
      switch (modes) {
        case 0:
          //heat
          digitalWrite(pinDir, HIGH);
          
          heaterPID.Compute();
          Serial.print("Output is wirtten as: "); Serial.println(Output);
          
          analogWrite(pinPwm, Output);
          break;
          
        case 1:
          //cool
          digitalWrite(pinDir, LOW);
          
          coolerPID.Compute();
          Serial.print("Output is wirtten as: "); Serial.println(Output);
          
          analogWrite(pinPwm, Output);




          //          if (c > temp_setpoint + 10) {
          //            analogWrite(pinPwm, 254);
          //          }
          //          else if (c > temp_setpoint + 5) {
          //            analogWrite(pinPwm, 200);
          //          }
          //          else if (c> temp_setpoint+1){
          //            analogWrite(pinPwm, 150);
          //          }
          //          else{
          //            analogWrite(pinPwm, 70); //stabilise temperature
          //          }
          break;
      }

  }
}
