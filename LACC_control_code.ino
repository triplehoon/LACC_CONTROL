#include "system_control.h"


void setup(void)
{
	auto sysCon = new SystemControl();
	//loop function
	while (true)
	{		
		blink_LED(1, 50);
		blink_LED(2, 50);
		blink_LED(3, 50);
		blink_LED(4, 50);
		blink_LED(5, 50);
		blink_LED(4, 50);
		blink_LED(3, 50);
		blink_LED(2, 50);
		blink_LED(1, 50);
		sysCon->WaitForCommand();
	}
}
