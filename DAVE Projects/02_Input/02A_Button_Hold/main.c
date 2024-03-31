/*
 * Demonstrates use of DIGITAL_IO APP to detect input of port pin (user push button)
 * Base code is from 01A_Blinking_BaseTimer
 * During normal operation (button not pushed), the LED toggles at 50Hz. Upon button push & held, LED toggles at 5Hz
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_ccu4.h"

/* NOTE: Time Interval is based on us (micro-second) & requires a x100 scaling factor */
#define TIMER_1MS 1000*100U
#define TIMER_d1MS 100*100U
volatile uint32_t timetick_count = 0; // Global variable (unsigned-int 32bit) for time tick count

int main(void)
{
  uint32_t pin_status; /* Declare variable for input level of pin (range 0 - 1) */
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
		  pin_status = DIGITAL_IO_GetInput(&BTN1);
		  if (pin_status == 0) // 0 for close | 1 for open , N.O push button
		  {
			  TIMER_Stop(&TIMER);
			  TIMER_SetTimeInterval(&TIMER , TIMER_1MS);
			  TIMER_Start(&TIMER);
		  }
	  }
	  return 1;
}

void interval_handler(void)
{
	TIMER_ClearEvent(&TIMER);
	TIMER_Stop(&TIMER);
	/* Set the time division for the TIMER */
	TIMER_SetTimeInterval(&TIMER , TIMER_d1MS);

	if(timetick_count == 200) // Condition will be based on the desired frequency. Eg: 20Hz @ interval of 0.1ms = 500 ticks
	{
		DIGITAL_IO_ToggleOutput(&LED1);
		timetick_count = 0;
	}
	else
	{
		timetick_count++;
	}
	TIMER_Start(&TIMER);
}
