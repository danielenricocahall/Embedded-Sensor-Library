#include <msp430.h> 
#include "MPU6050.h"
#include "tempSensor.h"
#include "FlashMemory.h"
#include "I2C.h"

//***//***************************************************************************************
//  FireFly
//
//  Description; Using internal temperature sensor, and MPU-6050 Accelerometer,
//  record real time data to flash memory
//  Sampling Rate: 100 Hz
//  Memory allocated: 12 KB
//
//  Daniel Cahall, Christopher Frederickson, Craig Szot
//  Rowan University
//  December 2015
//  Built with Code Composer Studio v5
//***************************************************************************************
int xAccel;
int yAccel;
int zAccel;
int xAngle;
int yAngle;
int zAngle;
int temp;
int tempX;
int hum;
int pressure;
 int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    BCSCTL1 = CALBC1_1MHZ;//sets clock to 1 MHz - up to discretion and application
    DCOCTL  = CALDCO_1MHZ;
    initMPU6050();
    tempInit();
    //infinite loop
    while(1)
    {
    	//__delay_cycles(10000);
    	getMPU6050();//Updates acceleration values
    	hum = getHumidity();
    	tempX = getTemp();
    	pressure = getPressure();
    	__no_operation();
    	//maximum threshold acceleration value, assuming sensitivity is +/- 16gs
    	if(getZAccel() > 2048)
    	{
    		//this is for writing temperature and acceleration to flash
    		//Although this can be modified to write pressure, etc.
    		char *Flash_ptr = (char *)0xC714; 		//Flash pointer starting position - this is determined based on where your code ends in memory
    		write_flash(Flash_ptr);					//Call function to clear/write temp to flash
    	}
    }
}
