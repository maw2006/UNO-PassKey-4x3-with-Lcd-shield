#include <Password.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Password password = Password("12357");
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3',},
  {'4','5','6',},
  {'7','8','9',},
  {'*','0','#',}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13}; //connect to the column pinouts of the keypad
const int buttonPin = A5;
int buttonState = 0;
int pos = 90;    // variable to store the servo position
int mov = 180;    // variable to store the servo move to position
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
#define  MAXCOLUMNS  16
#define  MAXLINES  2
#define ledPin A2
#define ledvdd A3
#define spk A1
#define spkvdd A4
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
  // d4, d5, d6, d7 on pins 4, 5, 6, 7
// LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); // initialize the library with the numbers of the interface pins  
// LCD sheild
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledvdd, OUTPUT);
  pinMode(spk, OUTPUT);
  pinMode(spkvdd, OUTPUT);
  pinMode(buttonPin, INPUT);
  // set up the LCD's number of rows and columns:
  lcd.begin(MAXCOLUMNS, MAXLINES);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledvdd, LOW);
  digitalWrite(spk, LOW);
  digitalWrite(spkvdd, LOW);
//Serial.begin(9600);
keypad.addEventListener(keypadEvent); //add an event listener for this keypad
keypad.setDebounceTime(50);
lcd.begin(16, 2);
lcd.print("Enter Password :");
lcd.setCursor(0, 1);
myservo.attach(A4);  // attaches the servo on pin 9 to the servo object
myservo.write(pos);  // tell servo to go to position in variable 'pos'
}

void loop(){
keypad.getKey();
//buttonState = digitalRead(buttonPin);
//lcd.print(digitalRead(buttonPin));
if (digitalRead(buttonPin) == LOW)
      {
//lcd.clear();
//digitalWrite(ledPin ,HIGH );
}
}
void keypadEvent(KeypadEvent eKey){
switch (keypad.getState()){
case PRESSED:

switch (eKey){
case '#': guessPassword(); break;
case '*': password.reset(); //resets password after INCORRECT entry
          lcd.clear();
          lcd.print("Enter Password :");
          lcd.setCursor(0, 1);
           break;
default:
password.append(eKey);
lcd.print("*");//lcd.print(eKey);
digitalWrite(spk, HIGH);
digitalWrite(ledPin,HIGH);
delay(10);
digitalWrite(spk, LOW);
digitalWrite(ledPin,LOW);
}
}}

void guessPassword(){
if (password.evaluate()){
//delay(500);
password.reset(); //resets password after correct entry
lcd.clear();
lcd.setCursor(2, 1);
lcd.print("(( Welcome ))");
digitalWrite(ledPin,HIGH); //activates garaged door relay
myservo.write(mov);  // tell servo to go to position in variable 'mov'
delay(2000);
digitalWrite(ledPin,LOW); //turns off door relay after .5 sec
myservo.write(pos);  // tell servo to go to position in variable 'pos'
lcd.clear();
lcd.print("Enter Password :");
lcd.setCursor(0, 1);
}


else{
digitalWrite(ledPin,LOW);
myservo.write(pos);  // tell servo to go to position in variable 'pos'
lcd.clear();
lcd.setCursor(0, 1);
lcd.print("INVALID PASSWORD ");
password.reset(); //resets password after INCORRECT entry
digitalWrite(ledPin,LOW);
digitalWrite(ledvdd, HIGH);
delay(1000);
digitalWrite(ledvdd, LOW);
lcd.clear();
lcd.print("Enter Password :");
lcd.setCursor(0, 1);
}
}
