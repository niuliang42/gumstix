#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp;
int main(void)
{
   char read_value[4];
   char adcVal2[6];
   if (( fp = fopen("/sys/class/hwmon/hwmon1/device/in2_input", "r")) == NULL)
   {
       printf("Can not open hwmon1 \n");
       exit(1);
   }
   rewind(fp);
   fread(&read_value, sizeof(char), 1 , fp);
   strcpy(adcVal2 , read_value);
   fclose(fp);
   printf("\nADC 2 value = %s \n",adcVal2);
   return 0;
}
