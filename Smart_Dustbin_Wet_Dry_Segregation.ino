
#include <LiquidCrystal.h>

#include <Servo.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal.h> // Library for LCD
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int irsensor = A2;
int pos = 0;    // variable to store the servo position
int value = A0;
#define trigPin 7
#define echoPin 8
#define trigPin1 10
#define echoPin1 13
#define buzz 6
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzz, OUTPUT);
 lcd.begin(16, 2);
 
  lcd.setCursor(0, 0);
  lcd.print("TRASH IN");
  lcd.setCursor(0, 1);
  lcd.print("CASH OUT");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo objec
  myservo.write(100);
  delay(1000);
  pinMode (irsensor, INPUT);
  pinMode (value, INPUT);
}

void loop() {
  value = analogRead(A0);
  if (digitalRead(A2) == LOW && value > 950)
  {
    myservo.write(30);
    delay(1000);
    myservo.write(100);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("DRY Waste");
    lcd.setCursor(0, 1);
    lcd.print("materials");
    delay (1000);
    lcd.clear();
  }
  else
  {



  }
  lcd.clear();
  value = analogRead(A0);
  if (value < 900) {
    Serial.println(value);
    myservo.write(150);
    delay(1000);
    myservo.write(100);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("WET Waste ");
    lcd.setCursor(0, 1);
    lcd.print("materials");
    delay (1000);
    lcd.clear();
  }
  else
  {



  }
  lcd.clear();
  long duration1, inches1, cm1, duration2, inches2, cm2;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  

  // Take reading on echo pin
  duration1 = pulseIn(echoPin, HIGH);
digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  

  // Take reading on echo pin
  duration2 = pulseIn(echoPin1, HIGH);

  // convert the time into a distance
  inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);
  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);
 

  if (inches1 <4 || inches2 <4)
  {
   
    digitalWrite(buzz, HIGH);
 lcd.print("FULL");

    delay(500);
  } else {
    lcd.print("empty");
    digitalWrite(buzz, LOW);

    delay(500);
  }
lcd.clear();
  delay(100);
}

long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}