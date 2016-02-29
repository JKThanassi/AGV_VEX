#pragma config(Sensor, in1,    line3,          sensorLineFollower)
#pragma config(Sensor, in2,    line2,          sensorLineFollower)
#pragma config(Sensor, in3,    line1,          sensorLineFollower)
#pragma config(Sensor, in4,    line0,          sensorLineFollower)
#pragma config(Sensor, in5,    lineNeg1,       sensorLineFollower)
#pragma config(Sensor, in6,    lineNeg2,       sensorLineFollower)
#pragma config(Sensor, in7,    lineNeg3,       sensorLineFollower)
#pragma config(Motor,  port7,           illuminator,   tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           motorDrive,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motorSteer,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//globals cause why not
int P;
float I;
float D;
int prevError;
float prevPID;

 float calcCorrection(int sensorPos,int desiredPos){
  const float kP = 25,kI = .2,kD = 100;
  float PID;
  if(sensorPos <= 3){
  int error = desiredPos-sensorPos;
  P = error * kP;
  I += error;
  I *=kI;
  D = (error - prevError)*kD;
  prevError = error;
  PID = (P+I+D);
  	prevPID = PID;
  	return PID;
  }
  else{
  return prevPID;
  }
}




int getSensorPos(){
  const int threshold = 1600;
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
   	return 9;
  }

}



task main(){
  P=0;
  I=0;
  D=0;
  prevError=0;
  prevPID = 0;
	bool isDriverActive = false;
  int sensorPos = 0;
	motor[illuminator] = 0;
  int frontMotorSpeed = 35, rearMotorSpeed = 0;
  while(isDriverActive){
  	motor[motorDrive] = vexRT[Ch2];
  	motor[motorSteer] = vexRT[Ch1];

  	if(vexRT[Btn6U] == 1){
  		isDriverActive = false;
  		wait1Msec(1000);
  	}

  }


  while(getSensorPos()!=7 && !isDriverActive ){
    sensorPos = getSensorPos();
    rearMotorSpeed=calcCorrection(sensorPos, 0);
    motor[motorSteer] = 0 + rearMotorSpeed;
    if(sensorPos == 9){
    motor[motorDrive] = frontMotorSpeed*.75;
    motor[motorSteer] = 0 + (rearMotorSpeed*2);
    }
    else{
      motor[motorSteer] = 0 + rearMotorSpeed;
    	motor[motorDrive] = frontMotorSpeed;
    }
    // if(rearMotorSpeed != 0){
    //   motor[motorDrive] = 20;
    // }
  //   else{
  //     //TODO change this to motorDrive
  //   motor[motorSteer] = rearMotorSpeed;
  // }
  	if(vexRT[Btn6U] == 1){
  		isDriverActive = true;
  	}
    wait1Msec(5);
   }

}
