#include <NewPing.h>
#include <Servo.h> 

#define SERVO_PIN 8
#define LEFT_TRIGGER_PIN 3
#define LEFT_ECHO_PIN 2
#define MIDDLE_TRIGGER_PIN 5
#define MIDDLE_ECHO_PIN 4
#define RIGHT_TRIGGER_PIN 7
#define RIGHT_ECHO_PIN 6
#define MAX_DISTANCE 40

// NewPing setup of pins and maximum distance
NewPing left(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE); 
NewPing middle(MIDDLE_TRIGGER_PIN, MIDDLE_ECHO_PIN, MAX_DISTANCE); 
NewPing right(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE); 

Servo RobotHead;
int previousAngle = 90;
//unsigned int DistanceThreasold = 30;

void setup() {
   Serial.begin(9600);
   RobotHead.attach(SERVO_PIN,900,2100);
  // Make servo looks front
  RobotHead.write(previousAngle);
  Serial.println("Servo set to 90 degrees");
  delay(2000);
}

void loop() {
  digitalWrite(LEFT_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  unsigned int distanceLeft = left.ping_cm();

  if (distanceLeft <= DistanceThreasold && distanceLeft > 0) { 
      Serial.println("============================================================");
      Serial.print("TURN LEFT -->");
      turn(0);
      delay(3000);
      Serial.println("... CLEAR LEFT after 3 secs");
      digitalWrite(LEFT_TRIGGER_PIN, LOW);
      delayMicroseconds(10);  
      turn(90);   
      Serial.println("============================================================"); 
  }

  digitalWrite(MIDDLE_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  unsigned int distanceMiddle = middle.ping_cm();

  if (distanceMiddle <= DistanceThreasold && distanceMiddle > 0) { 
      Serial.print("TURN MIDDLE -->");
      turn(90);
      delay(3000);
      Serial.println("... CLEAR MIDDLE after 3 secs");
      digitalWrite(MIDDLE_TRIGGER_PIN, LOW);
      delayMicroseconds(10);
  }

  digitalWrite(RIGHT_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  unsigned int distanceRight = right.ping_cm();

  if (distanceRight <= DistanceThreasold && distanceRight > 0) { 
      Serial.print("TURN RIGHT -->");
      turn(180);
      delay(3000);
      Serial.println("... CLEAR RIGHT after 3 secs");
      digitalWrite(RIGHT_TRIGGER_PIN, LOW);
      delayMicroseconds(10);    
      turn(90);  
  }

}



void turn(int newAngle) {
    
      if(newAngle>previousAngle)
      {
        for(int i=previousAngle; i<=newAngle; i++) {
          RobotHead.write(i); //turn servo by 1 degrees
          delay(15);        //delay for smoothness
        }
      }
    
      if(newAngle<previousAngle){
        for(int i=previousAngle; i>=newAngle; i--)
        {
          RobotHead.write(i); //turn servo by 1 degrees
          delay(10);        //delay for smoothness
        }
      }
      previousAngle = newAngle;
}
