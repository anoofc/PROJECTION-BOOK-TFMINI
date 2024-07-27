#define DEBUG 0

#define BAUD_RATE 9600

#define LEFT_SENSOR 26
#define RIGHT_SENSOR 27


#define HOLD_TIME 3000


#include <Arduino.h>

uint8_t count = 1;
uint8_t lastCount = 1;

bool flag_1 = false;
bool flag_2 = false;

unsigned long prevMillis = 0;


void debugData(){
  // if (DEBUG){Serial.println("Dist 1: " + String(dist_1) + "\t flag 1: " + String(flag_1) + "\t Dist 2: " + String(dist_2) + "\t Flag 2: " + String(flag_2));}
  
}


void swipe_check_right(){
  while (flag_1){
    if (digitalRead(RIGHT_SENSOR) == LOW){
      if (DEBUG){Serial.println("RIGHT");}
      if (count<4){count++;}
      if (count==1 && lastCount==1){
         Serial.println("A");
         lastCount = count;
      } else if (count==2 && lastCount==1){
         Serial.println("B");
         lastCount = count;
      } else if (count==3 && lastCount==2){
         Serial.println("C");
         lastCount = count;
      } else if (count==4 && lastCount==3){
         Serial.println("D");
         lastCount = count;
      } 
      Serial.println(String(count));
      delay(1000);
      flag_1 = false;
      flag_2 = false;
    }
    if (millis() - prevMillis > HOLD_TIME){
      Serial.println("EXIT");
      flag_1 = false;
      flag_2 = false;
    }
  }
}
void swipe_check_left(){
  while (flag_2){
    if (digitalRead(LEFT_SENSOR) == LOW){
      if (DEBUG){Serial.println("LEFT");}
      if (count>1){count--;}
      if (count==1 && lastCount==2){
         Serial.println("G");
         lastCount = count;
      } else if (count==2 && lastCount==3){
         Serial.println("F");
         lastCount = count;
      } else if (count==3 && lastCount==4){
         Serial.println("E");
         lastCount = count;
      }
      Serial.println(String(count));
      
      delay(1000);
      flag_2 = false;
      flag_1 = false;
    }
    if (millis() - prevMillis > HOLD_TIME){
      Serial.println("EXIT");
      flag_2 = false;
      flag_1 = false;
    }
  }
}

void checkSensor(){
  if (digitalRead(LEFT_SENSOR) == LOW && digitalRead(RIGHT_SENSOR) == HIGH){
    flag_1 = true;
    if (DEBUG){Serial.println("Left Sensor Triggered");}
    prevMillis = millis();
    swipe_check_right();
  }else {
    flag_1 = false;
  }
  if (digitalRead(RIGHT_SENSOR) == LOW && digitalRead(LEFT_SENSOR) == HIGH){
    flag_2 = true;
    if (DEBUG){Serial.println("Right Sensor Triggered");}
    prevMillis = millis();
    swipe_check_left();
} else {
    flag_2 = false;
  }
}


void setup()
{
  Serial.begin(BAUD_RATE);         //set bit rate of serial port connecting Arduino with computer
  pinMode(LEFT_SENSOR, INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);

}
 
 
void loop() {

  checkSensor();

}