/*
AMC-ROBOT Project
Copyright(C) 2016, AMC - Alexandre Miguel de Carvalho
professorcarvalho @ roboticando . com

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include <ThreadController.h>
#include <Thread.h>
#include <DueTimer.h>
#include "ControleFuzzy.h"
#include "SensorLinha.h"
#include "MotorCC.h"
#include "MPU6050spec.h"




bool roboParado = true; //condição inicial


ThreadController raiz;

Thread leSensoresIMU;
Thread leSensoresLinha;
Thread fazControleFuzzy;
Thread acionaMotores;

int pwm1 = 0;		//0-255 M1
int pwm2 = 0;		//0-255 M2
float yawLido = 0;
float pitchLido = 0;
float rollLido = 0;
int resultadoSensorDeLinha = 0;


void leIMU();
void leLinha();
void fazControle();
void pwmAjuste();

void setup()
{
	MPUobj.Setup(0,0);
	Serial.begin(9600);
	Serial.println("setup");
	MotorCCObj.init();
	ControleFuzzyObj.init();

	//tempo em ms
	leSensoresIMU.setInterval(10); 
	leSensoresLinha.setInterval(10); 
	fazControleFuzzy.setInterval(10);
	acionaMotores.setInterval(10);
	
	leSensoresIMU.onRun(leIMU);
	leSensoresLinha.onRun(leLinha);
	fazControleFuzzy.onRun(fazControle);
	acionaMotores.onRun(pwmAjuste);


	raiz.add(&leSensoresIMU);
	raiz.add(&leSensoresLinha);
	raiz.add(&fazControleFuzzy);
	raiz.add(&acionaMotores);



	
}

void loop()
{
	
	Serial.println("Executa!");
	raiz.run();
	

}


void leIMU() {


	yawLido = MPUobj.leYaw();
	pitchLido = MPUobj.lePitch();
	rollLido = MPUobj.leRoll();
}


//************************************************************************************//
// S1		S2		S3		S4		Codigo		Significado		resultadoSensorDeLinha
// 0		0		0		0		0000		reta					0
// 0		0		1		0		0010		direita suave			2
// 0		0		0		1		0001		direita forte			1
// 0		0		1		1		0011		direita					3
// 0		1		0		0		0100		esquerda suave			4
// 1		0		0		0		1000		esquerda forte			8
// 1		1		0		0		1100		esquerda				12
//*************************************************************************************//
void leLinha() {

	resultadoSensorDeLinha = SensorLinhaObj.manobra();
}

void fazControle() {

	//Variaveis de entrada
	ControleFuzzyObj.fuzzy->setInput(1, yawLido);
	ControleFuzzyObj.fuzzy->setInput(2, pitchLido);
	ControleFuzzyObj.fuzzy->setInput(3, resultadoSensorDeLinha);
	//Variaveis de saida
	pwm1 = ControleFuzzyObj.output1fuzzy();
	pwm2 = ControleFuzzyObj.output2fuzzy();
}

void pwmAjuste() {
	analogWrite(motorM1pino, pwm1); // Ajusta a velocidade do motor M1
	analogWrite(motorM2pino, pwm2); // Ajusta a velocidade do motor M2
}