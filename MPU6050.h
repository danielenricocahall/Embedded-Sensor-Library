/*
 * MPU6050.h
 *
 *  Created on: Dec 21, 2015
 *      Author: Danny
 */

#ifndef MPU6050_H_
#define MPU6050_H_

extern unsigned char RX_ByteCtr;
extern unsigned char TX_ByteCtr;

void initMPU6050();
void getMPU6050();
int getXAccel();
int getYAccel();
int getZAccel();
int getHumidity();
int getYAngle();
int getZAngle();
int getTemp();
int getPressure();

#endif /* MPU6050_H_ */
