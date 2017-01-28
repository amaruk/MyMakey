#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "drv_adc.h"

/* ADC device file names */
static char *_adcChStrP[SYSFS_ADC_DIR_CHMAX] = { NULL };

/* Get ADC channel value 0~4095 */
int adcGetChVal(int ch)
{
	char adcChStr[10]; 		/* String ADC value */
	int adcChStrLen = 0; 	/* String ADC value length */
	int adcChInt = 0; 		/* Integer ADC value */
	FILE *fd = NULL; 		/* Point to ADC device` file */
	int idx = 0;

	fd = fopen(_adcChStrP[ch], "r+");
	fscanf(fd, "%s", adcChStr);

	/* Record ADC value string length */
	adcChStrLen = strlen(adcChStr);

	/* Translate character into number */
	for (idx = 0; idx < adcChStrLen; idx++)
	{
		/* Invalid character */
		if (('\0' != adcChStr[idx]) &&
			(('0' > adcChStr[idx]) ||
			('9' < adcChStr[idx])))
		{
			adcChStrLen = 0;
			break;
		}
		/* Character to number */
		else
		{ adcChStr[idx] -= '0'; }
	}

	/* Make up the int value */
	switch (adcChStrLen)
	{
		case 4:
			adcChInt = adcChStr[0] * 1000 + adcChStr[1] * 100
					+ adcChStr[2] * 10 + adcChStr[3];
			break;
		case 3:
			adcChInt = adcChStr[0] * 100 + adcChStr[1] * 10
					+ adcChStr[2];
			break;
		case 2:
			adcChInt = adcChStr[0] * 10 + adcChStr[1];
			break;
		case 1:
			adcChInt = adcChStr[0];
			break;
		default:
			adcChInt = THREASHOLD_VALID + 1; /* Invalid */
			break;
	}

	fclose(fd);

	return adcChInt;
}

/* ADC initialization */
void adcInit(void)
{
	FILE *fd = NULL;

	_adcChStrP[0] = SYSFS_ADC_DIR_CH0;
	_adcChStrP[1] = SYSFS_ADC_DIR_CH1;
	_adcChStrP[2] = SYSFS_ADC_DIR_CH2;
	_adcChStrP[3] = SYSFS_ADC_DIR_CH3;
	_adcChStrP[4] = SYSFS_ADC_DIR_CH4;
	_adcChStrP[5] = SYSFS_ADC_DIR_CH5;
	_adcChStrP[6] = SYSFS_ADC_DIR_CH6;

	fd = fopen(SYSFS_ADC_DIR_CH0, "w");
	if (fd == NULL) /* Load ADC if it is not loaded*/
	{
		fd = fopen(SYSFS_ADC_DEV, "w");
		fwrite("BB-ADC", sizeof(int), 6, fd); /* "BB-ADC" has 6 characters */
		fclose(fd);
	}
}
