#include <msp430.h>
#include "tempSensor.h"
#include "MPU6050.h"


//Written to save temperature values
//Although can be modified to fit other applications
void write_flash (char *pntr)
{
  char *Flash_ptr = pntr;                   // set Flash pointer
  int i,x;									//loop counter variables

  //Writes to 24, 512 byte segments
  //Which is ~12 KB
  for(x=23;x>0;--x)
  {
	  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
	  FCTL3 = FWKEY;                            // Clear Lock bit
	  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

	  FCTL1 = FWKEY + WRT;                     // Set WRT bit for write operation
	  for (i=512; i>0; --i)                    //iterate to 512 because each segment is separate bytes                                     //by 512 bytes
	    {
		  __delay_cycles(10000);				//100 Hz sampling rate
	  	  //int temp = tempOut();					//Read current temp
	  	  getMPU6050();							//Acquire current accelerations
	  	  //*Flash_ptr++ = temp;                 // Write value to flash
	  	  //int xAccel = getXAccel();				//Read current x-acceleration value
	  	  *Flash_ptr++ = getZAccel();                 // Write value to flash
	  	  *Flash_ptr++ = getZAccel() >> 8;
	  	  *Flash_ptr++= getYAccel();				//Read current y-acceleration value
	  	  *Flash_ptr++ = getYAccel() >> 8;                 // Write value to flash
	  	  *Flash_ptr++ = getXAccel();                 // Write value to flash
	  	  *Flash_ptr++ = getXAccel() >> 8;
	  	  *Flash_ptr++ = getZAngle();                 // Write value to flash
	  	  *Flash_ptr++ = getZAngle() >> 8;
	  	  *Flash_ptr++ = getYAngle();                 // Write value to flash
	  	  *Flash_ptr++ = getYAngle() >> 8;
	    }

	  FCTL1 = FWKEY;                           // Clear WRT bit
	  FCTL3 = FWKEY + LOCK;                    // Set LOCK bit
  }

}
