#include <Wire.h>
#include <Adafruit_MotorShield.h> 
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myStepper = AFMS.getStepper(200,2);
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>

Adafruit_DCMotor *motor = AFMS.getMotor(1);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
int t=800;
volatile int n = 0;
volatile int r = 0;
int total_degrees = 360;
int players;
int cards;
float steps_per_degree = .555; // For this motor, 360 degrees = 200 steps
int degrees_per_player = total_degrees / (players);
float steps = degrees_per_player * steps_per_degree;
int done = HIGH;
 
 //digitalRead(buttonPin3);
 // Serial.println(done); 
  //delay(500); 

const int buttonPin = 1; // Define the pin number connected to the button 
const int buttonPin2 = 0;
const int buttonPin3 = 5;
 // Variable to count button presses 

void setup() { 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);// Set pin as input with internal pull-up resistor 
attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
 attachInterrupt(digitalPinToInterrupt(buttonPin2), charlie, RISING);
 //Interrupt on button press 
  Serial.begin(9600); // Start serial communication 

  AFMS.begin();
   myStepper->setSpeed(10);
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); 
} 

void loop() { // Main program code here that won't affect button counting 
  n=0;
  done = HIGH;
  lcd.clear();
   done = digitalRead(buttonPin3);

 while (done == HIGH) {
  lcd.setCursor(0,0); 
  lcd.print("Players = ");
  lcd.setCursor(10,0);
  lcd.print(n);
  done = digitalRead(buttonPin3);
 }
 players = n;
 
  delay(500); 

   lcd.setCursor(0,1); 
   lcd.print("Yee Hah ");
  delay(2000);

lcd.clear();
done = HIGH;
n=0;
   while (done == HIGH){
    lcd.setCursor(0,0); 
   lcd.print("Cards =");
   lcd.setCursor(9,0);
   lcd.print(n);
   done = digitalRead(buttonPin3);
  } 
cards = n;
  delay (500);
   lcd.setCursor(0,1); 
   lcd.print("Yee Hah ");
  delay(2000);
lcd.clear();
done = HIGH;

 lcd.setCursor(0,0); 
   lcd.print("Players =");
   lcd.setCursor(10,0);
   lcd.print(players);
    lcd.setCursor(0,1); 
   lcd.print("Cards =");
   lcd.setCursor(8,1);
   lcd.print(cards);
   delay(5000);
lcd.clear();
while (done == HIGH){
    lcd.setCursor(0,0); 
   lcd.print("Is this correct?");
   done = digitalRead(buttonPin3);
  } 
delay(500);
 lcd.setCursor(0,1); 
   lcd.print("Yee Hah ");

   delay(2000);
 
int degrees_per_player = total_degrees / (players);
float steps = degrees_per_player * steps_per_degree;
delay(3000);

for (int c=1; c <= cards; c++) {

for (int i=1; i <= players; i++) {
   myStepper->step(steps, FORWARD, SINGLE);
   Serial.print("steps to ");
   Serial.print(steps);
   Serial.println(" steps");
   delay(1000);
   motor->setSpeed(200);
   motor->run(BACKWARD);
   delay(60);
   motor->run(FORWARD);
   delay(100);
    motor->run(RELEASE);
    delay(500);
 
}


}

} 

  void buttonISR() { 
    n++; 
  }

  void charlie() {
    n = 0;
  }
  
  
   
