// include the library code:
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_MCP9808.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

int buttonsPin = A0;
int buttonValue = 0;
int debounce = 200;


//H Bridge Setup
// PWM is connected to pin 3.
const int pinPwm = 3;

// DIR is connected to pin 2.
const int pinDir = 2;

// Speed of the Peltier.
static int iSpeed = 1023; //speed for peltier is full (motor controller)

// Acceleration of the Peltier.
static int iAcc = 1;

int buttonPress = 0;
int menu=0;

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);

    // set up the LCD's number of rows and columns: 
  lcd.begin(20, 4);

  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);


  // Initialize the PWM and DIR pins as digital outputs.
  pinMode(pinPwm, OUTPUT);
  pinMode(pinDir, OUTPUT);
  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  
}
int x = 0;



//Starting Menu drawn to screen.
void startMenu(){ 
    lcd.setCursor(0,0);
    lcd.print("-> Set Point");
  
    lcd.setCursor(0,1);
    lcd.print("-> Mode");
  
    lcd.setCursor(0,2);
    lcd.print("-> Fan Override");
    
    lcd.setCursor(0,3);
    lcd.print("-> Start");   
}

void loop() {
  // put your main code here, to run repeatedly:
  startMenu();
//
//
//
//  
// 
//  
//  
//  
//  
//  
//  float c = tempsensor.readTempC();
//  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
//  lcd.setCursor(0,3);
//  lcd.print(c); 
//    
//  // read the value from the sensor:
//    buttonValue = analogRead(buttonsPin);
//     
//    if(buttonValue>554 && buttonValue<570){
//      buttonPress = 1;
//    }
//    else if(buttonValue>604 && buttonValue<622){
//      buttonPress = 2;
//    }
//  
//    else if(buttonValue>860 && buttonValue<873){
//      buttonPress = 3;
//    }
//  
//    else if(buttonValue>835 && buttonValue<844){
//      buttonPress = 4;
//    }
//  
//    else if(buttonValue>689 && buttonValue<698){
//      buttonPress = 5;
//    }
//  
//    else if(buttonValue>928 && buttonValue<933){
//      buttonPress = 6;
//    }
//
//
//
//
//
//
//  
//  switch(buttonPress){
//    Serial.println("button value: " + buttonValue);
//    case 1:
//     
//      if (x == 0) {
//        // Toggle on
//               digitalWrite(4, HIGH);
//              x = 1;
//              lcd.setCursor(0,3);
//              lcd.print("Fan ON");
//       } 
//       else {
//          // Toggle off
//          digitalWrite(4, LOW);
//          x = 0;
//          lcd.setCursor(0,3);
//          lcd.print("Fan Off");
//       }
//     delay(debounce);
//     buttonPress=0;
//      
//    break;
//    case 2:
//      buttonPress = 0;
//      lcd.setCursor(0,3);
//      lcd.print("DOWN  ");
//      Serial.println("DOWN");
//      Serial.println(buttonValue);
//      delay(debounce);
//
//      digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);              // wait for a second
//      digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
//      delay(1000);              // wait for a second
//    break;
//    
//    case 3:
//      buttonPress = 0;
//      lcd.setCursor(0,3);
//      lcd.print("LEFT  ");
//      Serial.println("LEFT");
//      Serial.println(buttonValue);
//      delay(debounce);
//     
//      digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);              // wait for a second
//      digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
//      delay(1000);              // wait for a second  
//    break;
//    
//    case 4:
//      buttonPress = 0;
//      lcd.setCursor(0,3);
//      lcd.print("RIGHT ");
//      Serial.println("RIGHT");
//      Serial.println(buttonValue);
//      delay(debounce);
//
//      digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);              // wait for a second
//      digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//      delay(1000);              // wait for a second
//    break;
//    
//    case 5:
//      buttonPress = 0;
//      lcd.setCursor(0,3);
//      lcd.print("SELECT");
//      Serial.println("SELECT");
//      Serial.println(buttonValue);
//      delay(debounce);
//    break;
//    default:
//    if(buttonValue==1023){
//      //do nothing
//    }
//    else{
//      Serial.println("button value: ");
//      Serial.println(buttonValue);
//    }
//    
//    break;
//  }
//  
//  //Serial.print("Button Value: "); Serial.println(buttonValue);

}


