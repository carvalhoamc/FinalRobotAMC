// MotorCC.h
// Acionamento do motor cc via PWM placa da Robocore Motor Driver 2x2.



#ifndef _MOTORCC_h
#define _MOTORCC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



//Pinos do MotorDriver Robocore2x2
const int motorM1pino = 5;			//velocidade do motor M1 (0-255)
const int motorM2pino = 6;			//velocidade do motor M2 (0-255)			
const int motorM1rotacaopino = 7;	//sentido da rotacao do M1 (horario/anti-horario)
const int motorM2rotacaopino = 8;	//sentido da rotacao do M2 (horario/anti-horario)





class MotorCCClass
{
private:


 public:
	void init();



};

extern MotorCCClass MotorCCObj;

#endif

