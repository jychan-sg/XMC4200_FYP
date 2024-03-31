/*
 * Demonstrates use of TIMER APP to vary timer interval and toggling of LED
 * TIMER running at 'base interval'/tick of 0.1ms and desired frequency/delay is calculated base on the tick
 * TIMER_0 - Vary the time tick interval
 * INTERRUPT_0 - Interrupt for timer event
 * LED1 (DIGITIAL_IO) - I/O Connection for LED
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_ccu4.h"

/* NOTE: Time Interval is based on us (micro-second) & requires a x100 scaling factor */
#define TIMER_1S 1000000*100U // Base unit in ms , scaling by x100
#define TIMER_100MS 100000*100U
#define TIMER_10MS 10000*100U
#define TIMER_1MS 1000*100U
#define TIMER_d1MS 100*100U
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