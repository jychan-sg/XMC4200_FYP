/*
 * Demonstrates use of TIMER APP to vary timer interval and toggling of LED
 * LED toggles at 0.1s interval for 5s before toggling at 0.5s interval. This sequence is repeated in a loop.
 * TIMER_0 - Vary the time tick interval
 * INTERRUPT_0 - Interrupt for timer event
 * LED1 (DIGITIAL_IO) - I/O Connection for LED
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_ccu4.h"

#define TIMER_500MS 500000*100U // Global variable for 500ms (0.5s) , actual value scaled by x100
#define TIMER_100MS 100000*100U // Global variable for 100ms (0.1s) , actual value scaled by x100
volatile uint32_t timetick_count = 0; // Global variable (unsigned-int 32bit) for time tick count

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
  }
  return 1;
}

void interval_handler(void)
{
	/* Clears interrupt status, next event will be considered new */
	TIMER_ClearEvent(&TIMER_0);
	/* Toggles LED */
	DIGITAL_IO_ToggleOutput(&LED1);
	/* A 'count' increment for every tick (varying) of the TIMER */
	timetick_count++;

	/*  */
	if(timetick_count == 10) //if TRUE > Stop Timer & Set Interval to 0.1sec
	{
		TIMER_Stop(&TIMER_0); // Stops TIMER if running, no further event.
		/* Sets new time interval (0.1s) */
		TIMER_SetTimeInterval(&TIMER_0 , TIMER_100MS);
	}

	else if (timetick_count == 60 ) //if TRUE > Stop Timer & Set Interval to 0.5sec & Reset count
	{
		TIMER_Stop(&TIMER_0); // Stops TIMER if running, no further event.
		/* Sets new time interval (0.1s) */
		TIMER_SetTimeInterval(&TIMER_0 , TIMER_500MS);
		/* Resets count */
		timetick_count = 0;
	}

	TIMER_Start(&TIMER_0); // Starts TIMER
}
