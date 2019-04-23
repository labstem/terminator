#include <Servo.h> 

#define SERVO_PIN 8
#define LEFT_TRIGGER_PIN 3
#define LEFT_ECHO_PIN 2
#define MIDDLE_TRIGGER_PIN 5
#define MIDDLE_ECHO_PIN 4
#define RIGHT_TRIGGER_PIN 7
#define RIGHT_ECHO_PIN 6
#define MAX_DISTANCE 200

Servo Robot;
int previousAngle = 90;
unsigned int DistanceThreasold = 50;  // Distance that fires servo turning
int duration, distance;               //declare variable for unltrasonic sensor

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_TRIGGER_PIN, OUTPUT);
  pinMode(MIDDLE_TRIGGER_PIN, OUTPUT);
  pinMode(RIGHT_TRIGGER_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);
  pinMode(MIDDLE_ECHO_PIN, INPUT);
  pinMode(RIGHT_ECHO_PIN, INPUT);
   
  Robot.attach(SERVO_PIN,900,2100);   // attach your servo
  Robot.writeMicroseconds(1500);
  Robot.write(90);                    // Turn a little bit the servo because we use 2 different gears (3/4 diff)
  // Make servo looks front
//  Robot.write(previousAngle);
  Serial.println("Servo set to Look Front");
}

void loop() {
  
  // ================================================================
  // LEFT ultrasonic code 
  // ================================================================
  digitalWrite(LEFT_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LEFT_TRIGGER_PIN,HIGH);
  _delay_ms(500);
  digitalWrite(LEFT_TRIGGER_PIN, LOW);
  
  duration = pulseIn(LEFT_ECHO_PIN,HIGH); 
  distance = microsecondsToCentimeters(duration); 
  if(distance <= DistanceThreasold && distance > 10) {// if ultrasonic sensor detects an obstacle less than DistanceThreasold cm.
//    Robot.write(0);                   //servo rotates at full speed to the left
    turn(0,90);
    Serial.print("LEFT -> "); //print distance unit cm
    Serial.println(distance);//distance    
    delay(1500);
    turn(90,0);
  } 


  // ================================================================
  // MIDDLE ultrasonic code 
  // ================================================================
//  digitalWrite(MIDDLE_TRIGGER_PIN, LOW);
//  delayMicroseconds(2);
//  digitalWrite(MIDDLE_TRIGGER_PIN,HIGH);
//  _delay_ms(500);
//  digitalWrite(MIDDLE_TRIGGER_PIN, LOW);
//  
//  duration = pulseIn(MIDDLE_ECHO_PIN,HIGH); 
//  distance = microsecondsToCentimeters(duration); 
//  if(distance <= DistanceThreasold && distance > 0 ) {// if ultrasonic sensor detects an obstacle less than DistanceThreasold cm.
//    turn(90,0);                         //servo rotates at full speed to the front
//    Serial.print("MIDDLE -> "); //print distance unit cm
//    Serial.println(distance);//distance
//    delay(1500);
//  } 

  // ================================================================
  // RIGHT ultrasonic code 
  // ================================================================
  digitalWrite(RIGHT_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(RIGHT_TRIGGER_PIN,HIGH);
  _delay_ms(500);
  digitalWrite(RIGHT_TRIGGER_PIN, LOW);
  
  duration = pulseIn(RIGHT_ECHO_PIN,HIGH); 
  distance = microsecondsToCentimeters(duration); 
  if(distance <= DistanceThreasold && distance > 10) {// if ultrasonic sensor detects an obstacle less than DistanceThreasold cm.
//    Robot.write(0);                   //servo rotates at full speed to the left
    turn(90,180);
    Serial.print("RIGHT -> "); //print distance unit cm
    Serial.println(distance);//distance    
    delay(1500);
  } 
}

void turn(int newAngle, int previousAngle) {
    
      if(newAngle>previousAngle)
      {
        for(int i=previousAngle; i<=newAngle+20; i++) {
          Robot.write(i); //turn servo by 1 degrees
          delay(30);        //delay for smoothness
        }
      }
    
      if(newAngle<previousAngle){
        for(int i=previousAngle; i>=newAngle; i--)
        {
          Robot.write(i); //turn servo by 1 degrees
          delay(30);        //delay for smoothness
        }
      }
      previousAngle = newAngle;
}

long microsecondsToCentimeters(long microseconds) {

  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return microseconds / 29 / 2;

}
