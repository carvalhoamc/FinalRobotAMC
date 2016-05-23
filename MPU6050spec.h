/* MPU6050 Basic Example with IMU
by: Kris Winer
date: May 10, 2014
license: Beerware - Use this code however you'd like. If you
find it useful you can buy me a beer some time.

Demonstrate  MPU-6050 basic functionality including initialization, accelerometer trimming, sleep mode functionality as well as
parameterizing the register addresses. Added display functions to allow display to on breadboard monitor.
No DMP use. We just want to get out the accelerations, temperature, and gyro readings.

SDA and SCL should have external pull-up resistors (to 3.3V).
10k resistors worked for me. They should be on the breakout
board.

Hardware setup:
MPU6050 Breakout --------- Arduino
3.3V --------------------- 3.3V
SDA ----------------------- A4
SCL ----------------------- A5
GND ---------------------- GND

Note: The MPU6050 is an I2C sensor and uses the Arduino Wire library.
Because the sensor is not 5V tolerant, we are using a 3.3 V 8 MHz Pro Mini or a 3.3 V Teensy 3.1.
We have disabled the internal pull-ups used by the Wire library in the Wire.h/twi.c utility file.
We are also using the 400 kHz fast I2C mode by setting the TWI_FREQ  to 400000L /twi.h utility file.
*/


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


// MPU6050spec.h

#ifndef _MPU6050SPEC_h
#define _MPU6050SPEC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <cmath>
#include <Wire.h>
#include <math.h>

const  byte  XGOFFS_TC = 0x00; // Bit 7 PWR_MODE, bits 6:1 XG_OFFS_TC, bit 0 OTP_BNK_VLD                 
const  byte  YGOFFS_TC = 0x01;
const  byte  ZGOFFS_TC = 0x02;
const  byte  X_FINE_GAIN = 0x03; // [7:0] fine gain
const  byte  Y_FINE_GAIN = 0x04;
const  byte  Z_FINE_GAIN = 0x05;
const  byte  XA_OFFSET_H = 0x06; // User-defined trim values for accelerometer
const  byte  XA_OFFSET_L_TC = 0x07;
const  byte  YA_OFFSET_H = 0x08;
const  byte  YA_OFFSET_L_TC = 0x09;
const  byte  ZA_OFFSET_H = 0x0A;
const  byte  ZA_OFFSET_L_TC = 0x0B;
const  byte  SELF_TEST_X = 0x0D;
const  byte  SELF_TEST_Y = 0x0E;
const  byte  SELF_TEST_Z = 0x0F;
const  byte  SELF_TEST_A = 0x10;
const  byte  XG_OFFS_USRH = 0x13;  // User-defined trim values for gyroscope; supported in MPU-6050?
const  byte  XG_OFFS_USRL = 0x14;
const  byte  YG_OFFS_USRH = 0x15;
const  byte  YG_OFFS_USRL = 0x16;
const  byte ZG_OFFS_USRH = 0x17;
const  byte ZG_OFFS_USRL = 0x18;
const  byte SMPLRT_DIV = 0x19;
const  byte CONFIG = 0x1A;
const  byte GYRO_CONFIG = 0x1B;
const  byte ACCEL_CONFIG = 0x1C;
const  byte FF_THR = 0x1D;  // Free-fall
const  byte FF_DUR = 0x1E;  // Free-fall
const  byte MOT_THR = 0x1F;  // Motion detection threshold bits [7:0]
const  byte MOT_DUR = 0x20;  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
const  byte ZMOT_THR = 0x21;  // Zero-motion detection threshold bits [7:0]
const  byte ZRMOT_DUR = 0x22;  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
const  byte FIFO_EN = 0x23;
const  byte I2C_MST_CTRL = 0x24;
const  byte I2C_SLV0_ADDR = 0x25;
const  byte I2C_SLV0_REG = 0x26;
const  byte I2C_SLV0_CTRL = 0x27;
const  byte I2C_SLV1_ADDR = 0x28;
const  byte I2C_SLV1_REG = 0x29;
const  byte I2C_SLV1_CTRL = 0x2A;
const  byte I2C_SLV2_ADDR = 0x2B;
const  byte I2C_SLV2_REG = 0x2C;
const  byte I2C_SLV2_CTRL = 0x2D;
const  byte I2C_SLV3_ADDR = 0x2E;
const  byte I2C_SLV3_REG = 0x2F;
const  byte I2C_SLV3_CTRL = 0x30;
const  byte I2C_SLV4_ADDR = 0x31;
const  byte I2C_SLV4_REG = 0x32;
const  byte I2C_SLV4_DO = 0x33;
const  byte I2C_SLV4_CTRL = 0x34;
const  byte I2C_SLV4_DI = 0x35;
const  byte I2C_MST_STATUS = 0x36;
const  byte INT_PIN_CFG = 0x37;
const  byte INT_ENABLE = 0x38;
const  byte DMP_INT_STATUS = 0x39;  // Check DMP interrupt
const  byte INT_STATUS = 0x3A;
const  byte ACCEL_XOUT_H = 0x3B;
const  byte ACCEL_XOUT_L = 0x3C;
const  byte ACCEL_YOUT_H = 0x3D;
const  byte ACCEL_YOUT_L = 0x3E;
const  byte ACCEL_ZOUT_H = 0x3F;
const  byte ACCEL_ZOUT_L = 0x40;
const  byte TEMP_OUT_H = 0x41;
const  byte TEMP_OUT_L = 0x42;
const  byte GYRO_XOUT_H = 0x43;
const  byte GYRO_XOUT_L = 0x44;
const  byte GYRO_YOUT_H = 0x45;
const  byte GYRO_YOUT_L = 0x46;
const  byte GYRO_ZOUT_H = 0x47;
const  byte GYRO_ZOUT_L = 0x48;
const  byte EXT_SENS_DATA_00 = 0x49;
const  byte EXT_SENS_DATA_01 = 0x4A;
const  byte EXT_SENS_DATA_02 = 0x4B;
const  byte EXT_SENS_DATA_03 = 0x4C;
const  byte EXT_SENS_DATA_04 = 0x4D;
const  byte EXT_SENS_DATA_05 = 0x4E;
const  byte EXT_SENS_DATA_06 = 0x4F;
const  byte EXT_SENS_DATA_07 = 0x50;
const  byte EXT_SENS_DATA_08 = 0x51;
const  byte EXT_SENS_DATA_09 = 0x52;
const  byte EXT_SENS_DATA_10 = 0x53;
const  byte EXT_SENS_DATA_11 = 0x54;
const  byte EXT_SENS_DATA_12 = 0x55;
const  byte EXT_SENS_DATA_13 = 0x56;
const  byte EXT_SENS_DATA_14 = 0x57;
const  byte EXT_SENS_DATA_15 = 0x58;
const  byte EXT_SENS_DATA_16 = 0x59;
const  byte EXT_SENS_DATA_17 = 0x5A;
const  byte EXT_SENS_DATA_18 = 0x5B;
const  byte EXT_SENS_DATA_19 = 0x5C;
const  byte EXT_SENS_DATA_20 = 0x5D;
const  byte EXT_SENS_DATA_21 = 0x5E;
const  byte EXT_SENS_DATA_22 = 0x5F;
const  byte EXT_SENS_DATA_23 = 0x60;
const  byte MOT_DETECT_STATUS = 0x61;
const  byte I2C_SLV0_DO = 0x63;
const  byte I2C_SLV1_DO = 0x64;
const  byte I2C_SLV2_DO = 0x65;
const  byte I2C_SLV3_DO = 0x66;
const  byte I2C_MST_DELAY_CTRL = 0x67;
const  byte SIGNAL_PATH_RESET = 0x68;
const  byte MOT_DETECT_CTRL = 0x69;
const  byte USER_CTRL = 0x6A;  // Bit 7 enable DMP, bit 3 reset DMP
const  byte PWR_MGMT_1 = 0x6B; // Device defaults to the SLEEP mode
const  byte PWR_MGMT_2 = 0x6C;
const  byte DMP_BANK = 0x6D;  // Activates a specific bank in the DMP
const  byte DMP_RW_PNT = 0x6E;  // Set read/write pointer to a specific start address in specified DMP bank
const  byte DMP_REG = 0x6F;  // Register in DMP from which to read or to which to write
const  byte DMP_REG_1 = 0x70;
const  byte DMP_REG_2 = 0x71;
const  byte FIFO_COUNTH = 0x72;
const  byte FIFO_COUNTL = 0x73;
const  byte FIFO_R_W = 0x74;
const  byte WHO_AM_I_MPU6050 = 0x75; // Should return 0x68
const  byte MPU6050_ADDRESS = 0x68;  // Device address


// Set initial input parameters
enum Ascale {
	AFS_2G = 0,
	AFS_4G,
	AFS_8G,
	AFS_16G
};

enum Gscale {
	GFS_250DPS = 0,
	GFS_500DPS,
	GFS_1000DPS,
	GFS_2000DPS
};




class MPU6050class
{
public:

	/*Configura MPU6050
	arduinoPino - pino onde o sensor é conectado no Arduino.
	escalaAcelerometro - modo de operação conforme Ascale
	escalaGiroscopio - modo de operação conforme Gscale
	aRes - Acell scale resolutions per LSB for the sensors
	gRes - Gyro scale resolutions per LSB for the sensors
	*/
	MPU6050class();
	void Setup(byte escalaAcelerometro, byte escalaGiroscopio);
	void startRead();
	void getGres();
	void getAres();
	void readAccelData(int16_t * destination);
	void readGyroData(int16_t * destination);
	int16_t readTempData();
	void LowPowerAccelOnlyMPU6050();
	void initMPU6050();
	void calibrateMPU6050(float * dest1, float * dest2);
	void MPU6050SelfTest(float * destination);
	void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
	uint8_t readByte(uint8_t address, uint8_t subAddress);
	void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
	void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz);
	float leYaw();
	float lePitch();
	float leRoll();



private:

	float aRes;
	float gRes;
	byte Gscale;
	byte Ascale;
	int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
	float ax, ay, az;       // Stores the real accel value in g's
	int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
	float gx, gy, gz;       // Stores the real gyro value in degrees per seconds
	float gyroBias[3] = { 0, 0, 0 }, accelBias[3] = { 0, 0, 0 }; // Bias corrections for gyro and accelerometer
	int16_t tempCount;   // Stores the real internal chip temperature in degrees Celsius
	float temperature;
	float SelfTest[6];
	// parameters for 6 DoF sensor fusion calculations
	float GyroMeasError = PI * (40.0f / 180.0f);     // gyroscope measurement error in rads/s (start at 60 deg/s), then reduce after ~10 s to 3
	float beta = 0.866025403784 * GyroMeasError;  // compute beta
	float GyroMeasDrift = PI * (2.0f / 180.0f);      // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
	float zeta = 0.866025403784 * GyroMeasDrift;  // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
	float pitch, yaw, roll;
	float deltat = 0.0f;                              // integration interval for both filter schemes
	uint32_t lastUpdate = 0, firstUpdate = 0;         // used to calculate integration interval
	uint32_t Now = 0;                                 // used to calculate integration interval
	float q[4] = { 1.0f, 0.0f, 0.0f, 0.0f };            // vector to hold quaternion

};

extern MPU6050class MPUobj;

#endif

