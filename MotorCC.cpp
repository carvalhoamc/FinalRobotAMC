// 
// 
// 

#include "MotorCC.h"

void MotorCCClass::init()
{
	//motor
	pinMode(motorM1pino, OUTPUT);
	pinMode(motorM2pino, OUTPUT);
	pinMode(motorM1rotacaopino, OUTPUT);
	pinMode(motorM2rotacaopino, OUTPUT);
	digitalWrite(motorM1rotacaopino, HIGH); //rotacao para frente
	digitalWrite(motorM2rotacaopino, HIGH); //rotacao para frente

}


MotorCCClass MotorCCObj;

