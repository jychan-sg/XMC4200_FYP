/*
 * Demonstrates use of DIGITAL_IO APP to for Pin Allocation as Input or Output
 * LED toggles on/off every 0.5 second (hardcoded based on MCU's CPU Clock Speed
 * LED1 (DIGITIAL_IO) - I/O Connection for LED
 */
#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {
    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  //DIGITAL_IO_SetOutputHigh(&LED1); //SetOutputHigh or SetOutputLow can also be used
	  DIGITAL_IO_ToggleOutput(&LED1);
	  for(float count = 0 ; count < 2500000 ; count++); // 0.5 sec ON | 0.5 sec OFF
	  //DIGITAL_IO_SetOutputLow(&LED1);
	  DIGITAL_IO_ToggleOutput(&LED1);
	  for(float count = 0 ; count < 2500000 ; count++); // 0.5 sec ON | 0.5 sec OFF
  }
}