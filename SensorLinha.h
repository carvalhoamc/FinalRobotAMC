// SensorLinha.h

#ifndef _SENSORLINHA_h
#define _SENSORLINHA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


//Pinos sensor Linha YL-70
const int IR1 = 47;
const int IR2 = 49;
const int IR3 = 51;
const int IR4 = 53;





class SensorLinhaClass
{
 private:
	 byte leSensorLinha1();
	 byte leSensorLinha2();
	 byte leSensorLinha3();
	 byte leSensorLinha4();

 public:
	 //**************************************************************************//
	 // S1		S2		S3		S4		Codigo		Significado		valorDecimal
	 // 0		0		0		0		0000		reta			0
	 // 0		0		1		0		0010		direita suave	2
	 // 0		0		0		1		0001		direita forte	1
	 // 0		0		1		1		0011		direita			3
	 // 0		1		0		0		0100		esquerda suave	4
	 // 1		0		0		0		1000		esquerda forte	8
	 // 1		1		0		0		1100		esquerda		12
	 //**************************************************************************//
	 unsigned int manobra();
	
};

extern SensorLinhaClass SensorLinhaObj;

#endif

