#pragma config(Sensor, S1,     backSensor,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     frontSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          beltA,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          beltD,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Configuration - Change these to fine tune.
	int drivingSpeed = 15;
	int drivingDuration = 1000;
	int waitingDuration = 2000; //Time to wait after sending out a bot
	int parkedDistance = 7; //distance which means there IS a car in the bay
	
//Variables
	int frontDistance = 0;
	int backDistance = 0;

//States
	bool frontBayFull = false;
	bool backBayFull = false;
	


//Variables




//Stop driving
void stopMoving()
{
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
}

//Moves Forward
void moveForward()
{
	setMotorSpeed(leftMotor, drivingSpeed);		//Set the leftMotor (motor1) to half power (50)
	setMotorSpeed(rightMotor, drivingSpeed);  //Set the rightMotor (motor6) to half power (50)
}

//Overload - for a duration
void moveForward(int duration)
{
	moveForward();
	sleep(duration);
	stopMoving();
}

//Moves Backwards
void moveBackward()
{
	setMotorSpeed(leftMotor, -drivingSpeed);		//Set the leftMotor (motor1) to half power (50)
	setMotorSpeed(rightMotor, -drivingSpeed);  //Set the rightMotor (motor6) to half power (50)
}

//Overload - for a duration
void moveBackward(int duration)
{
	moveBackward();
	sleep(duration);
	stopMoving();
}

//Sense if both the delivery Robots are present
void checkBays()
{
	//if one is there
	if (frontDistance < parkedDistance)
	{
		fronBayFull = true;
	}
	else
	{
		fronBayFull = false;
	}
	
	if (backDistance < parkedDistance)
	{
		backBayFull = true;
	}
	else
	{
		backBayFull = false;
	}
	
	
	//if they are not
	//return false;
}


task main()
{
	//Infinite Loop
	while(true)
	{
		//update variables
		frontDistance = getUSDistance(frontSensor);
		backDistance = getUSDistance(backSensor);
		
		//check for bots
		checkBays();
		
		//moveForward(drivingDuration);
		//moveBackward(drivingDuration);
		if (frontBayFull && backBayFull)
		{
			moveForward(drivingDuration);
			sleep(waitingDuration);
			moveBackward(drivingDuration);
			sleep(waitingDuration);	
		}
		else
		{
			moveForward(1);
			moveBackward(1);
		}
	}


}
