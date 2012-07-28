#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

const int THRESHOLD=    ;// 阈值

int char2int(char c[])
{
	int re=0;
	for(int i=0; c[i]; i++)
	{
		re*=10;
		re+=c[i]-'0';
	}
	return re;
}

int main(void)
{
	char read_value[4];
	char adcCharVal2[6];
	int adcIntVal;
	//int i=0;
	if ( ( fp = fopen("/sys/class/hwmon/hwmon0/device/in7_input", "r") ) == NULL)
	{
		printf("Can not open hwmon0 \n");
		exit(1);
	}
	system("insmod pwm.ko timers=8 servo=1 servo_min=5000 servo_max=25000");//need to change
	while(1)
	{
		rewind(fp);
		fread(&read_value, sizeof(char), 1 , fp);
		strcpy(adcCharVal2 , read_value);
		//printf("\nADC 2 value = %s \n",adcCharVal2);
		adcIntVal=char2int(adcCharVal);
		if(adcIntVal>=THRESHOLD)
		{
			system("echo 20000 > /dev/pwm8");
		}
		else
		{
			system("echo 5000 > /dev/pwm8");
		}
	}
	fclose(fp);
	return 0;
}
