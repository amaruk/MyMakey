#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SYSFS_ADC_DIR_CHMAX	7
#define SYSFS_ADC_DIR_CH0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define SYSFS_ADC_DIR_CH1 "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define SYSFS_ADC_DIR_CH2 "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define SYSFS_ADC_DIR_CH3 "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"
#define SYSFS_ADC_DIR_CH4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define SYSFS_ADC_DIR_CH5 "/sys/bus/iio/devices/iio:device0/in_voltage5_raw"
#define SYSFS_ADC_DIR_CH6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define SYSFS_ADC_DEV "/sys/devices/bone_capemgr.9/slots"
#define MAX_BUF 64

#define THREAD_VAL		3500
#define THREASHOLD	1

static int _getAdcChVal(int ch)
{
    FILE  *fd=NULL;
    char a[10];
    int x;

    char *adcChStrP[SYSFS_ADC_DIR_CHMAX] = {NULL};

    adcChStrP[0] = SYSFS_ADC_DIR_CH0;
    adcChStrP[1] = SYSFS_ADC_DIR_CH1;
    adcChStrP[2] = SYSFS_ADC_DIR_CH2;
    adcChStrP[3] = SYSFS_ADC_DIR_CH3;
    adcChStrP[4] = SYSFS_ADC_DIR_CH4;
    adcChStrP[5] = SYSFS_ADC_DIR_CH5;
    adcChStrP[6] = SYSFS_ADC_DIR_CH6;

	fd=fopen(adcChStrP[ch],"r+");
	fscanf(fd,"%s",a);
//			printf("%s",a);
	if(strlen(a)==4)
	{
		x=((int)a[0]-48)*1000+((int)a[1]-48)*100+((int)a[2]-48)*10+((int)a[3]-48);
	}
	else if(strlen(a)==3)
	{
		x=((int)a[0]-48)*100+((int)a[1]-48)*10+((int)a[2]-48);
	}
	else if(strlen(a)==2)
	{
		x=((int)a[0]-48)*10+((int)a[1]-48);
	}
	else
	{
		x=((int)a[0]-48);
	}
	fclose(fd);

	return x;
}

void adcTest(void)
{
	int sysCallRtn = 0xffff;
    FILE  *fd=NULL;
    int x;
    char adcStatus[SYSFS_ADC_DIR_CHMAX] = {0,0,0,0,0,0};
    char adcStatusCnt[SYSFS_ADC_DIR_CHMAX] = {0,0,0,0,0,0};
    int adcChIdx = 0;

    fd=fopen(SYSFS_ADC_DIR_CH0,"w");
    if (fd==NULL)     /* Load ADC if it is not loaded*/
    {
        fd=fopen(SYSFS_ADC_DEV,"w");
        fwrite("BB-ADC",sizeof(int),6,fd);   /* "BB-ADC" has 6 characters */
        fclose(fd);
    }

    while(1)
    {
    	for (adcChIdx = 0; adcChIdx < SYSFS_ADC_DIR_CHMAX; adcChIdx++)
		{

    		x = _getAdcChVal(adcChIdx);
//			adc=((float)x/4095.0)*1.8;
//			printf("[%4f] ",adc);
			if (x < THREAD_VAL)
			{
				printf("-%d:%d \n", adcChIdx, x);
			}
			else
			{
				//printf("#%d:%d ", adcChIdx, x);
			}
//			if (6 == adcChIdx)
//			{ printf("\n"); }

			if ((x < THREAD_VAL) && (adcStatus[adcChIdx] == 0))
			{
				char *musicP = NULL;
				if (THREASHOLD != adcStatusCnt[adcChIdx])
				{ adcStatusCnt[adcChIdx]++; }
				if (THREASHOLD == adcStatusCnt[adcChIdx])
				{
					adcStatus[adcChIdx] = 1;
					//printf("[%d] ON[%d]\n", adcChIdx, x);
					switch (adcChIdx)
					{
					case 0:
						musicP = "./wavPlayer ./Piano/C4.wav &";
						break;
					case 1:
						musicP = "./wavPlayer ./Piano/D4.wav &";
						break;
					case 2:
						musicP = "./wavPlayer ./Piano/E4.wav &";
						break;
					case 3:
						musicP = "./wavPlayer ./Piano/F4.wav &";
						break;
					case 4:
						musicP = "./wavPlayer ./Piano/G4.wav &";
						break;
					case 5:
						musicP = "./wavPlayer ./Piano/A4.wav &";
						break;
					case 6:
						musicP = "./wavPlayer ./Piano/B4.wav &";
						break;
					default:
						printf("Impossible!\n");
						break;
					}
					printf("playing: %s\n", musicP);
					sysCallRtn = system(musicP);
				}
			}
			else if ((x >= THREAD_VAL) && (x != 4095) && (adcStatus[adcChIdx] == 1))
			{
				if (0 != adcStatusCnt[adcChIdx])
				{ adcStatusCnt[adcChIdx]--; }
				if (0 == adcStatusCnt[adcChIdx])
				{
					adcStatus[adcChIdx] = 0;
					//printf("[%d] OFF[%d]\n", adcChIdx, x);
				}
			}

			usleep(1000);
		}
    	//printf("\n");
    }

}
#if 0
{
    FILE  *fd=NULL;
    char a[10];
    int x;
    float adc;
    char *adcChStrP[SYSFS_ADC_DIR_CHMAX] = {NULL};
    char adcStatus[SYSFS_ADC_DIR_CHMAX] = {0,0,0,0,0,0};
    char adcStatusCnt[SYSFS_ADC_DIR_CHMAX] = {0,0,0,0,0,0};
    char adcChIdx = 0;

    adcChStrP[0] = SYSFS_ADC_DIR_CH0;
    adcChStrP[1] = SYSFS_ADC_DIR_CH1;
    adcChStrP[2] = SYSFS_ADC_DIR_CH2;
    adcChStrP[3] = SYSFS_ADC_DIR_CH3;
    adcChStrP[4] = SYSFS_ADC_DIR_CH4;
    adcChStrP[5] = SYSFS_ADC_DIR_CH5;
    adcChStrP[6] = SYSFS_ADC_DIR_CH6;

    fd=fopen(SYSFS_ADC_DIR_CH0,"w");
    if (fd==NULL)     /* Load ADC if it is not loaded*/
    {
        fd=fopen(SYSFS_ADC_DEV,"w");
        fwrite("BB-ADC",sizeof(int),6,fd);   /* "BB-ADC" has 6 characters */
        fclose(fd);
    }

    while(1)
    {
    	for (adcChIdx = 0; adcChIdx < SYSFS_ADC_DIR_CHMAX; adcChIdx++)
		{
			fd=fopen(adcChStrP[adcChIdx],"r+");
			fscanf(fd,"%s",a);
//			printf("%s",a);
			if(strlen(a)==4)
			{
				x=((int)a[0]-48)*1000+((int)a[1]-48)*100+((int)a[2]-48)*10+((int)a[3]-48);
			}
			else if(strlen(a)==3)
			{
				x=((int)a[0]-48)*100+((int)a[1]-48)*10+((int)a[2]-48);
			}
			else if(strlen(a)==2)
			{
				x=((int)a[0]-48)*10+((int)a[1]-48);
			}
			else
			{
				x=((int)a[0]-48);
			}
//			adc=((float)x/4095.0)*1.8;
//			printf("[%4f] ",adc);
			if (x < THREAD_VAL)
			{
				printf("-%d:%dx \n", adcChIdx, x);
			}
			else
			{
				//printf("#%d:%dx ", adcChIdx, x);
			}
//			if (6 == adcChIdx)
//			{ printf("\n"); }

			if ((x < THREAD_VAL) && (adcStatus[adcChIdx] == 0))
			{
				char *musicP = NULL;
				if (THREASHOLD != adcStatusCnt[adcChIdx])
				{ adcStatusCnt[adcChIdx]++; }
				if (THREASHOLD == adcStatusCnt[adcChIdx])
				{
					adcStatus[adcChIdx] = 1;
					//printf("[%d] ON[%d]\n", adcChIdx, x);
					switch (adcChIdx)
					{
					case 0:
						musicP = "./wavPlayer ./Piano/C4.wav &";
						break;
					case 1:
						musicP = "./wavPlayer ./--Piano/D4.wav &";
						break;
					case 2:
						musicP = "./wavPlayer ./Piano/E4.wav &";
						break;
					case 3:
						musicP = "./wavPlayer ./Piano/F4.wav &";
						break;
					case 4:
						musicP = "./wavPlayer ./Piano/G4.wav &";
						break;
					case 5:
						musicP = "./wavPlayer ./Piano/A4.wav &";
						break;
					case 6:
						musicP = "./wavPlayer ./Piano/B4.wav &";
						break;
					default:
						break;
					}
					system(musicP);
				}
			}
			else if ((x >= THREAD_VAL) && (x != 4095) && (adcStatus[adcChIdx] == 1))
			{
				if (0 != adcStatusCnt[adcChIdx])
				{ adcStatusCnt[adcChIdx]--; }
				if (0 == adcStatusCnt[adcChIdx])
				{
					adcStatus[adcChIdx] = 0;
					//printf("[%d] OFF[%d]\n", adcChIdx, x);
				}
			}

			fclose(fd);
			usleep(1000);
		}
    	//printf("\n");
    }
}
#endif
