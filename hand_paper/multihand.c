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
	while(j<60)
	{
		avVal=0;
		for(i=0; i<TIMES; i++)
		{
			fp = fopen("/sys/class/hwmon/hwmon0/device/in7_input", "r");
			rewind(fp);
			//fread(&read_value, sizeof(char), 1 , fp);
			fgets(read_value, 6, fp);
			strcpy(adcVal7 , read_value);
			value[i]=trans(adcVal7);
			avVal+=value[i];
			fclose(fp);
		}
		avVal/=TIMES;
		if(avVal>=STAND)
		{
			printf("%ld  , pwmOUT : 9000\n", avVal);
			system("sleep 1");
		}
		else
		{
			printf("%ld  , pwmOUT : 5000\n", avVal);
			system("sleep 1");
		}
		j++;
	}
	return 0;
}
