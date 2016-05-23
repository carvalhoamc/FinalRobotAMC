// 
// 
// 

#include "SensorLinha.h"

byte SensorLinhaClass::leSensorLinha1()
{
	return digitalRead(IR1);
}

byte SensorLinhaClass::leSensorLinha2()
{
	return digitalRead(IR2);
}

byte SensorLinhaClass::leSensorLinha3()
{
	return digitalRead(IR3);
}

byte SensorLinhaClass::leSensorLinha4()
{
	return digitalRead(IR4);
}


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


unsigned int SensorLinhaClass::manobra()
{
	byte s1 = 0;
	byte s2 = 0;
	byte s3 = 0;
	byte s4 = 0;
	byte resultado = 0;
	byte mascaraS4 = 0x0001b;
	byte mascaraS3 = 0x0010b;
	byte mascaraS2 = 0x0100b;
	byte mascaraS1 = 0x1000b;

	//linha
	pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
	pinMode(IR3, INPUT);
	pinMode(IR4, INPUT);	

	s1 = leSensorLinha1();
	s2 = leSensorLinha2();
	s3 = leSensorLinha3();
	s4 = leSensorLinha4();

	if (s1 == 1) {

		resultado |= mascaraS1;               //bit vai para 1
	}
	else {
		resultado = resultado & (~mascaraS1); //bit vai para 0
	}

	if (s2 == 1) {

		resultado |= mascaraS2;
	}
	else {
		resultado = resultado & (~mascaraS2);
	}

	if (s3 == 1) {

		resultado |= mascaraS3;
	}
	else {
		resultado = resultado & (~mascaraS3);
	}

	if (s4 == 1) {

		resultado |= mascaraS4;
	}
	else {
		resultado = resultado & (~mascaraS4);
	}

	return resultado;

}

SensorLinhaClass SensorLinhaObj;