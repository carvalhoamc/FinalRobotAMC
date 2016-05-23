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


// AMCSensores.h

#ifndef _AMCSENSORES_h
#define _AMCSENSORES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class AMCSensoresClass
{
public:
	//Marque os sensores disponíveis no seu hardware{GY-80, MPU6050, etc}
	AMCSensoresClass(bool giroscopio, bool acelerometro, bool bussola, bool barometro);
	
	void setupGiroscopio(void);
	void setupAcelerometro(void);
	void setupBussola(void);
	void setupBarometro(void);	
	void setupSensorDeLinhas(void);
	
	void readGiroscopio(void);
	void readAcelerometro(void);
	void readBussola(void);   
	void readBarometro(void); 
	void readSensorDeLinhas(void);
	
	void fusaoDeDadosSensores(void);

private:

	




};

extern AMCSensoresClass AMCSensores(bool giroscopio, bool acelerometro, bool bussola, bool barometro);

#endif

