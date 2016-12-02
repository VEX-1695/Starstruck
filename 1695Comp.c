#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           frontLeft,     tmotorVex393_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_3)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_4)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, PIDControl, encoderPort, I2C_5)
#pragma config(Motor,  port6,           rightLift,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void pre_auton()
{

	bStopTasksBetweenModes = true;

}
void autoDrive(float speed, float sec)
{
	motor(frontLeft) = speed;
	motor(frontRight) = speed;
	motor(backLeft) = speed;
	motor(backRight) = speed;
	sec *=1000;
	wait1Msec(sec);
}
void autoDrive(float speed)
{
	motor(frontLeft) = speed;
	motor(frontRight) = speed;
	motor(backLeft) = speed;
	motor(backRight) = speed;
}
void autoStop()
{
	motor(frontLeft) = 0;
	motor(frontRight) = 0;
	motor(backLeft) = 0;
	motor(backRight) = 0;
}

void autoDriveEnc(float speed, int enc)
{
	int initialEncoder = getMotorEncoder(backRight);
	while (abs(getMotorEncoder(backRight) - initialEncoder) < abs(enc)){
		autoDrive(speed);
		autoStop();
	}
}
void autoFire()
{
	motor(leftLift) = 127;
	motor(rightLift) = 127;
	wait1Msec(2000);
	motor(leftLift) = -127;
	motor(rightLift) = -127;
	wait1Msec(2000);
}
void autoTurn(bool dir, int sec)// write true for right and false for left
{
	if(dir){
	motor(frontLeft) = 100;
	motor(frontRight) = 0;
	motor(backLeft) = 100;
	motor(backRight) = 0;
	sec*=1000;
	wait1Msec(sec);}
	else{
	motor(frontLeft) = 0;
	motor(frontRight) = 100;
	motor(backLeft) = 0;
	motor(backRight) = 100;
	sec*=1000;
	wait1Msec(sec);
	}
}
void auto1()
{
	autoDrive(150, 2);
	autoFire();
	autoDrive(-150, 2);
}
task teleDrive()
{
	motor(backLeft) = vexRT(Ch3);
	motor(frontLeft) = vexRT(Ch3);
	motor(backRight) = vexRT(Ch1);
	motor(frontRight) = vexRT(Ch1);
}
bool shift = false;
bool shift1 = false;
task starLaunch()
{
	if(Btn5U){
		if(!shift)
			// figure out this toggle
		{
			motor(leftLift) = 127;
			motor(rightLift) = 127;
		}
		shift = true;
	}
	else
	{
		shift = false;
	}
 if(Btn5D){
		if(!shift1)
			// figure out this toggle
		{
			motor(leftLift) = -127;
			motor(rightLift) = -127;
		}
		shift1 = true;
	}
	else
	{
		shift1 = false;
	}
}
//////////////////actual runing
task autonomous()
{
	auto1();
}
task usercontrol()
{
	startTask(starLaunch);
	startTask(teleDrive);
	while (true)
	{
		wait1Msec(1);
	}
}
