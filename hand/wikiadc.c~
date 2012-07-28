#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp;
int main(void)
{
	char read_value[4];
	char adcVal2[6];
	int i=0;
	if (( fp = fopen("/sys/class/hwmon/hwmon0/device/in2_input", "r")) == NULL)
	{
		printf("Can not open hwmon0 \n");
		exit(1);
	}
	while(i<10)
	{
		rewind(fp);
		fread(&read_value, sizeof(char), 1 , fp);
		strcpy(adcVal2 , read_value);
		printf("\nADC 2 value = %s \n",adcVal2);
		fclose(fp);
	}
	return 0;
}
