#pragma config(Motor,  port2,           front,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rear,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

motor[front] = 127;
motor[rear] = 127;
wait1Msec(1000);


}
