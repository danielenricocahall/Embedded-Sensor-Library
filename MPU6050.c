/*
 * MPU6050.c
 *
 *  Created on: Dec 21, 2015
 *      Author: Danny
 */

//MPU6050 - Source: Danny

#include <msp430.h>

#include "I2C.h"

#include "MPU6050.h"


//Globals MPU6050

int xAccel;
int yAccel;
int zAccel;
int xAngle;
int yAngle;
int zAngle;
int temperature;

const unsigned char PWR_MGMT_1   = 0x6B;	// MPU-6050 register address
const unsigned char ACCEL_XOUT_H = 0x3B;	// MPU-6050 register address
const unsigned char ACCEL_XOUT_L = 0x3C;	// MPU-6050 register address
const unsigned char ACCEL_YOUT_H = 0x3D;	// MPU-6050 register address
const unsigned char ACCEL_YOUT_L = 0x3E;	// MPU-6050 register address
const unsigned char ACCEL_ZOUT_H = 0x3F;	// MPU-6050 register address
const unsigned char ACCEL_ZOUT_L = 0x40;	// MPU-6050 register address
const unsigned char ACCEL_CONFIG = 0x1C;    //MPU-6050 register address
const unsigned char GYRO_XOUT_H = 0x43;
const unsigned char GYRO_XOUT_L = 0x44;
const unsigned char GYRO_YOUT_H = 0x45;
const unsigned char GYRO_YOUT_L = 0x46;
const unsigned char GYRO_ZOUT_H = 0x47;
const unsigned char GYRO_ZOUT_L = 0x48;
const unsigned char TEMP_OUT_H = 0x41;
const unsigned char TEMP_OUT_L = 0x42;

void initMPU6050() {
	P1SEL |= BIT6 + BIT7;
	P1SEL2|= BIT6 + BIT7;
	P1DIR |= 0x08;

	slaveAddress = 0x68;	// Set slave address for MPU-6050

	i2cInit();

	// Wake up the MPU-6050
	slaveAddress = 0x68;					// MPU-6050 address
	TX_Data[1] = 0x6B;						// address of PWR_MGMT_1 register
	TX_Data[0] = 0x00;						// set register to zero (wakes up the MPU-6050)
	TX_ByteCtr = 2;
	i2cWrite(slaveAddress);

	//placing the accelerometer in mode 3
	//which is +/- 16g
	//Note:
	//

	TX_Data[1] = 0x1C;
	TX_Data[0] = 0x18;
	TX_ByteCtr = 2;
	i2cWrite(slaveAddress);

	//gyro handling
	TX_Data[1] = 0x1B;
	TX_Data[0] = 0x18;
	TX_ByteCtr = 2;
	i2cWrite(slaveAddress);

	//low pass filter handling
	TX_Data[1] = 0x1A;
	TX_Data[0] = 0x06;
	TX_ByteCtr = 2;
	i2cWrite(slaveAddress);
}

void getMPU6050(){
	// Point to the ACCEL_ZOUT_H register in the MPU-6050
	slaveAddress = 0x68;					// MPU-6050 address
	TX_Data[0] = 0x3B;					// register address
	TX_ByteCtr = 1;
	i2cWrite(slaveAddress);

	RX_ByteCtr = 14;
	i2cRead(slaveAddress);
	xAccel  = RX_Data[13] << 8;				// MSB
	xAccel |= RX_Data[12];					// LSB
	yAccel  = RX_Data[11] << 8;				// MSB
	yAccel |= RX_Data[10];					// LSB
	zAccel  = RX_Data[9] << 8;				// MSB
	zAccel |= RX_Data[8];					// LSB
	temperature = RX_Data[7] << 8;          //MSB
	temperature |= RX_Data[6];               //LSB
	xAngle  = RX_Data[5] << 8;				// MSB
	xAngle |= RX_Data[4];					// LSB
	yAngle  = RX_Data[3] << 8;				// MSB
	yAngle |= RX_Data[2];					// LSB
	zAngle  = RX_Data[1] << 8;				// MSB
	zAngle |= RX_Data[0];					// LSB
	//__no_operation();

}
//get the z-acceleration values
int getZAccel()
{
	return zAccel;
}
//get the y-acceleration values
int getYAccel()
{
	return yAccel;
}
//get the x-acceleration values
int getXAccel()
{
	return xAccel;
}

//get the z-gyro values
int getZAngle()
{
	return zAngle;
}
//get the y-gyro values
int getYAngle()
{
	return yAngle;
}
//get the x-gyro values
int getXAngle()
{
	return xAngle;
}

int getTemp()
{
	return temperature;
}
