#pragma config(Sensor, in1,    line3,          sensorLineFollower)
#pragma config(Sensor, in2,    line2,          sensorLineFollower)
#pragma config(Sensor, in3,    line1,          sensorLineFollower)
#pragma config(Sensor, in4,    line0,          sensorLineFollower)
#pragma config(Sensor, in5,    lineNeg1,       sensorLineFollower)
#pragma config(Sensor, in6,    lineNeg2,       sensorLineFollower)
#pragma config(Sensor, in7,    lineNeg3,       sensorLineFollower)
#pragma config(Motor,  port2,           motorDrive,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motorSteer,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//globals cause why not
int P = 0;
int I = 0;
int D = 0;
int prevError = 0;

 int calcCorrection(int sensorPos,int desiredPos){
  const int kP = 30,kI = 7,kD = 4;
  int error = sensorPos-desiredPos;
  P = error * kP;
  I += error;
  I *=kI;
  D = error - prevError;

  return P+I+D;

}

int getSensorPos(){
  const int threshold = 900;
  if(SensorValue[line3] > threshold){
    return 3;
  }
  if(SensorValue[line2] > threshold){
    return 2;
  }
  if(SensorValue[line1] > threshold){
    return 1;
  }
  if(SensorValue[line0] > threshold){
    return 0;
  }
  if(SensorValue[lineNeg1] > threshold){
    return -1;
  }
  if(SensorValue[lineNeg2] > threshold){
    return -2;
  }
  if(SensorValue[lineNeg3] > threshold){
    return -3;
  }
  //this statement checks if the sensor array has encountered a horizontal black line
  if (SensorValue[lineNeg3] > threshold
    && SensorValue[lineNeg2] > threshold
    && SensorValue[lineNeg1] > threshold
    && SensorValue[line0] > threshold
    && SensorValue[line1] > threshold
    && SensorValue[line2] > threshold
    && SensorValue[line3] > threshold) {
    return 7;
  }
  else{
   	return NULL;
  }

}



task main(){
  int frontMotorSpeed = 50, rearMotorSpeed = 0;
  while(getSensorPos()!=7){
    rearMotorSpeed+=calcCorrection(0,getSensorPos());
    motor[motorSteer] = rearMotorSpeed;
    motor[motorDrive] = frontMotorSpeed;
  }

}
