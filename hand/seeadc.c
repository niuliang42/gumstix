#include <stdio.h>
int mian()
{
	/*The method to read adc value.*/
	while(1)
	{
		system("cat /sys/class/hwmon/hwmon0/device/in7_input");
		system("sleep(0.5)");
	}
	return 0;
}
