#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp;
const int STAND=150;
const int TIMES=5;//TIMES <= 9 && TIMES >= 0
int trans(char c[])
{
	int i=0, target=0;
	target=0;
	while(c[i])
	{
		target *= 10;
		target += c[i]-'0';
		i++;
	}
	return target;
}
int main()
{
	char read_value[10], adcVal7[10];
	int value[10]={0};
	long int avVal=0;
	int i=0,j=0;
	system("insmod /media/card/gumstix/pwm/pwm.ko timers=8 servo=1 servo_min=5000 servo_max=25000 servo_start=5000");
	//使用8号端口进行pwm输出
	while(j<60)
	{
		avVal=0;
		for(i=0; i<TIMES; i++)
		{
			fp = fopen("/sys/class/hwmon/hwmon0/device/in7_input", "r");
			//adc_7号端口进行adc输入
			rewind(fp);
			//fread(&read_value, sizeof(char), 1 , fp);
			fgets(read_value, 6, fp);
			strcpy(adcVal7 , read_value);
			value[i]=trans(adcVal7);
			avVal+=value[i];
			fclose(fp);
		}
		avVal/=TIMES;
		//算若干次取得的肌电信号的平均值，若超过某一值则控制舵机旋转
		if(avVal>=STAND)
		{
			printf("%ld  , pwmOUT : 9000\n", avVal);
			system("echo 9000 > /dev/pwm8");
			system("sleep 1");
		}
		else
		{
			printf("%ld  , pwmOUT : 5000\n", avVal);
			system("echo 5000 > /dev/pwm8");
			system("sleep 1");
		}
		j++;
	}
	system("rmmod pwm");
	return 0;
}
