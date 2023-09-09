
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "FastTrig.h"
#include "falldetection.h"

MPU6050 mpu6050(Wire);

int timer=0;
int pitch=0;
int roll=0;
int fallCount=0;
bool fallReported = false;

/*
int maxp =-90;
int minp=90;
int maxr=-90;
int minr=90;
int maxy=-90;
*/

void GetPitchnRoll()
{
  int pitch = -(atan2(mpu6050.getAccX(), sqrt(mpu6050.getAccY()*mpu6050.getAccY() + mpu6050.getAccZ()*mpu6050.getAccZ()))*180.0)/MPI;
  int roll = -(atan2(-mpu6050.getAccY(), mpu6050.getAccZ())*180.0)/MPI;
}


void setup() {
  timer=0;
  Serial.begin(BAUD);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  fallCount=0;
  fallReported = false;
}

void loop() {
  mpu6050.update();

  if(millis() - timer > LOOP_DELAY){
/*    
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    */
    timer = millis();

    GetPitchnRoll();

    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print("\t Roll = ");
    Serial.print(roll);


/*
    if (pitch>maxp)
      maxp=pitch;
    else if (pitch< minp)
      minp=pitch;
    if (roll>maxr)
      maxr=roll;
    else if (roll< minr)
      minr=roll;

    Serial.print(" Min Pitch = ");
    Serial.print(minp);
    Serial.print(" Max Pitch = ");;
    Serial.print(maxp);
    Serial.print(" Min Roll = ");
    Serial.print(minr);
    Serial.print(" Max Roll = ");;
    Serial.print(maxr);
    */

    if( (pitch>PITCH_FALL_ANGLE_TRIGGER)||(pitch<-PITCH_FALL_ANGLE_TRIGGER) ||
      (roll>ROLL_FALL_ANGLE_TRIGGER)||(roll<-ROLL_FALL_ANGLE_TRIGGER) )
    {
      fallCount++;
      if(  (pitch>PITCH_FALLEN_ANGLE) || (pitch<-PITCH_FALLEN_ANGLE)  || 
        (roll>ROLL_FALLEN_ANGLE) ||(roll<-ROLL_FALLEN_ANGLE)) 
      {
        Serial.println("\t\t\t\tOn the ground detected."); 
      }
      else if(fallCount>MAX_LONG_FALL_COUNT)
      {
        Serial.println("\t\t\t\tLong Fall detected.");
      }
      else if(fallCount>MAX_FALL_COUNT)
      {
        Serial.println("\t\t\t\tFall detected.");
        fallReported = true;
      }
      else 
        Serial.println();
    }
    else if (fallCount>0)
    {
      fallCount=0;
      if(!fallReported)
      {
        Serial.println("\t\t\t\tStumble detected.");
        fallReported=false;
      }
      else
      {
        Serial.println("\t\t\t\tOK Now?");
      }
    }
    else 
    Serial.println();
;
  }

}

