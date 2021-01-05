/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// the setup routine runs once when you press reset:
  LiquidCrystal_I2C lcd(0x27, 16, 2);

// StopWatch
unsigned long begin_stop_watch = 0;
// BACKLIGHT
uint8_t backlight_enabled = 0;
// Pin DEFAULTS
  uint8_t left_pin  = 7;
  uint8_t right_pin = 8;
  uint8_t enter_pin = 9;
  uint8_t left_pin_state  = LOW;
  uint8_t right_pin_state = LOW;
  uint8_t enter_pin_state = LOW;
// Mode Const
// Default mode
  uint8_t mode = 0;
  uint8_t menu_item_selected = 0;
// Modes:
/*   
 *    1 - Main menu
 *    2 - 
 */
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  Serial.print("DEBUG: Entering setup()\r\n");
  lcd.init();  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Hello F0XY Rain");
  lcd.setCursor(0,1);
  lcd.print("Staring...");
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);
  pinMode(enter_pin, INPUT);
  delay(1500);
}
  // the loop routine runs over and over again forever:

void ReadPinsData(){
  Serial.print("DEBUG: Entering ReadPinsData()\r\n");
  left_pin_state  = digitalRead(left_pin); 
  right_pin_state = digitalRead(right_pin); 
  enter_pin_state = digitalRead(enter_pin);
  lcd.setCursor(0,1);
  lcd.print(left_pin_state);
  lcd.setCursor(3,1);
  lcd.print(right_pin_state);
  lcd.setCursor(5,1);
  lcd.print(enter_pin_state);
  lcd.setCursor(7,1);
  lcd.print(menu_item_selected); 
  delay(10);
}
void StopWatch(){
  begin_stop_watch = millis();
  
  Serial.print("DEBUG: Entering StopWatch()\r\n");
  unsigned long current_time = 0;
  uint8_t days = 0;
  uint8_t hours = 0;
  uint8_t minutes = 0;
  uint8_t seconds = 0;
  uint16_t mseconds = 0;
  uint8_t stopwatch_stopped = 0;
  while (1){
  if (enter_pin_state == HIGH){
    begin_stop_watch = millis();
  }
  unsigned long current_time = millis() - begin_stop_watch;

  days = current_time / 86400000;
  current_time = current_time - 86400000 * days;
  hours = current_time / 3600000;
  current_time = current_time - 3600000 * hours;
  minutes = current_time / 60000;
  current_time = current_time - 60000 * minutes;
  seconds = current_time / 1000;
  current_time = current_time - 1000 * seconds;
  mseconds = current_time;

  if (left_pin_state == HIGH){
    menu_item_selected = 0;
    break; 
  }
  ReadPinsData();
  
    delay(300);
    // Output time  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(days);
    lcd.print(":");
    lcd.print(hours);
    lcd.print(":");
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);  
    lcd.print(":");
    lcd.print(mseconds);  
  
  }
}
void loop() {
  Serial.print("DEBUG: Entering loop()\r\n");
  delay(300);
  ReadPinsData();
  if (left_pin_state == HIGH)
    menu_item_selected--;
  if (right_pin_state == HIGH)
    menu_item_selected++;
  switch(mode){
    case 0:{
      // default mode
      lcd.clear();
      mode = 1;
      break;
    }
    case 1:{
      // Main menu mode
      if (enter_pin_state == HIGH){
        switch(menu_item_selected){
          case 0:
            StopWatch();
            break;
          }
        }
      }
      break;
    
  }
  


 
}
