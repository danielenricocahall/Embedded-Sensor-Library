#include <msp430.h> 
#include "MPU6050.h"
#include "tempSensor.h"
#include "FlashMemory.h"
#include "I2C.h"
#include <math.h>
//***//***************************************************************************************
//  FireFly
//
//  Description; Using internal temperature sensor, and MPU-6050 Accelerometer,
//  record real time data to flash memory
//  Sampling Rate: 100 Hz
//  Memory allocated: ~12 KB
//
//  Daniel Cahall, Christopher Frederickson, Craig Szot
//  Rowan University
//  December 2015
//  Built with Code Composer Studio v5
//***************************************************************************************
int zAccel;
int yAccel;
int xAccel;
int zAngle;
int yAngle;
int zAngle;
int temp;

 int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    BCSCTL1 = CALBC1_1MHZ;//sets clock to 1 MHz - up to discretion and application
    DCOCTL  = CALDCO_1MHZ;
    initMPU6050();
    tempInit();
    int temp_predicted = tempOut();
    //infinite loop
    while(1)
    {
    	getMPU6050();//Updates acceleration values
    	zAccel = getZAccel();
    	yAccel = getYAccel();
    	xAccel = getXAccel();
    	zAngle = getZAngle();
    	yAngle = getYAngle();
    	xAngle = getXAngle();
	temp = getTemprature();

    	//__no_operation();

    	//maximum threshold acceleration value, assuming sensitivity is +/- 16gs
    	if(zAccel > 1*1024)
    	{
    		//this is for writing temperature and acceleration to flash
    		//Although this can be modified to write other quantites
    		char *Flash_ptr = (char *)0xC714; 		//Flash pointer starting position - this is determined based on where your code ends in memory
    		write_flash(Flash_ptr);					//Call function to clear/write temp to flash
    	}
    }

}






