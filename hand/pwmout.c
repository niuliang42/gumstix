#include <stdio.h>
int main()
{
	system("insmod pwm.ko timers=8 servo=1 servo_min=5000 servo_max=25000");
	system("echo 20000 > /dev/pwm8");
	return 0;
}
