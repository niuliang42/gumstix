//RMS就是指对获得的数次输入的平方和的均值进行开方，得到的值
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
const int STAND=150;
const int TOTALTIMES=100;//how many result numbers you want to get
const int RMSTIMES=10;//how many times' adc to get a result
FILE *fp;

int trans(char c[])//change string into numbers
{
	int i=0, target=0;
	while(c[i++])
	  if(c[i]<='9' && c[i]>='0')
	  {
		  target *= 10;
		  target += c[i]-'0';
	  }
	return target;
}

int main()
{
	fp=fopen("/sys/class/hwmon/hwmon0/device/in7_input", "r");
	char read_value[10];
	int value[RMSTIMES];
	long long valuesq[RMSTIMES];
	long long valsqsum=0;
	//double valsqsum=0;
	double result=0;
	//system("insmod /media/card/gumstix/pwm/pwm.ko timers=8,11 servo=1 servo_min=5000 servo_max=25000 servo_start=15000");
	int i=0,k=0;//k->totaltimes;j->rmstimes;i->rmstimes
	//while(j<60)
	for(k=0; k<TOTALTIMES; k++)
	{
		//initialization
		memset(value, 0, sizeof(value));
		memset(valuesq, 0, sizeof(valuesq));
		valsqsum=0;
		result=0;

		//get the adc_value
		for(i=0; i<RMSTIMES; i++)
		{
			memset(read_value, 0, sizeof(read_value));
			rewind(fp);
			//fread(read_value, sizeof(char), 4 , fp);
			fgets(read_value, 6, fp);
			read_value[9]='\0';
			value[i]=trans(read_value);
			printf("value:%d, ", value[i]);
			valuesq[i]=value[i]*value[i];
			printf("valuesq:%lld.\n", valuesq[i]);
			valsqsum+=valuesq[i];
		}
		result=sqrt((double)valsqsum/RMSTIMES);
		/*
		 * if(result>=STAND) system("echo 25000 > /sys/pwm8;echo 25000 > /sys/pwm11");
		 * else system("echo 5000 > /sys/pwm8;echo 5000 > /sys/pwm11");
		 */
		printf("valsqsum:%lld, result: %lf\n-----------------------------------------\n",valsqsum, result);
	}
	fclose(fp);
	system("rmmod pwm");
	return 0;
}
