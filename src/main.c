/*********************************************************************************************************
 *
 * File                : main.c
 * Hardware Environment: BeagleBoneBlack
 * Build Environment   : GCC in BeagleBoneBlack
 * Version             : V1.0
 * By                  : Amaruk
 *                      https://amaruk.github.io/
 *
 *********************************************************************************************************/
#include "common.h"
#include "drv_adc.h"

/* ADC channel status: PRESS/RELEASE */
char adcStatus[SYSFS_ADC_DIR_CHMAX] =
{ STATUS_RELEASE, STATUS_RELEASE, STATUS_RELEASE,
	STATUS_RELEASE, STATUS_RELEASE, STATUS_RELEASE };
/* ADC channel press filter counter */
char adcPressCnt[SYSFS_ADC_DIR_CHMAX] =
{ FLT_CNT_INIT, FLT_CNT_INIT, FLT_CNT_INIT,
	FLT_CNT_INIT, FLT_CNT_INIT, FLT_CNT_INIT };
/* ADC channel release filter counter */
char adcReleaseCnt[SYSFS_ADC_DIR_CHMAX] =
{ FLT_CNT_INIT, FLT_CNT_INIT, FLT_CNT_INIT,
	FLT_CNT_INIT, FLT_CNT_INIT, FLT_CNT_INIT };

void makey(void)
{
	int adcVal = 0; /* ADC channel value */
	int adcChIdx = 0;

	for (adcChIdx = 0; adcChIdx < SYSFS_ADC_DIR_CHMAX; adcChIdx++)
	{
		adcVal = adcGetChVal(adcChIdx);

		/* Release status + Press detected */
		if ((adcVal < THREASHOLD_GND) && (adcStatus[adcChIdx] == STATUS_RELEASE))
		{
			char *musicP = NULL;
			/* Press filter */
			if (FLT_CNT_PRESS > adcPressCnt[adcChIdx])
			{
				adcPressCnt[adcChIdx]++;
			}
			if (FLT_CNT_PRESS == adcPressCnt[adcChIdx])
			{
				adcStatus[adcChIdx] = STATUS_PRESS;
				adcReleaseCnt[adcChIdx] = FLT_CNT_INIT;
				//printf("[%d] ON[%d]\n", adcChIdx, adcVal);
				/* Play the wav file */
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
					printf("Fatal Error!\n");
					break;
				}
				//printf("playing: %s\n", musicP);
				system(musicP);
			}
		}
		/* Press status + Press detected */
		else if ((adcVal < THREASHOLD_GND) && (adcStatus[adcChIdx] == STATUS_PRESS))
		{
			adcReleaseCnt[adcChIdx] = FLT_CNT_INIT;
		}
		/* Press status + Release detected */
		else if ((adcVal >= THREASHOLD_GND) && (adcVal <= THREASHOLD_VALID)
				&& (adcStatus[adcChIdx] == STATUS_PRESS))
		{
			/* Release filter */
			if (FLT_CNT_RELEASE > adcReleaseCnt[adcChIdx])
			{
				adcReleaseCnt[adcChIdx]++;
			}
			if (FLT_CNT_RELEASE == adcReleaseCnt[adcChIdx])
			{
				adcStatus[adcChIdx] = STATUS_RELEASE;
				adcPressCnt[adcChIdx] = FLT_CNT_INIT;
				//printf("[%d] OFF[%d]\n", adcChIdx, adcVal);
			}
		}
		/* Release status + Release detected */
		else if ((adcVal >= THREASHOLD_GND) && (adcVal <= THREASHOLD_VALID)
				&& (adcStatus[adcChIdx] == STATUS_RELEASE))
		{
			adcPressCnt[adcChIdx] = FLT_CNT_INIT;
		}

		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	adcInit();

	for (;;)
	{ makey(); }

	exit(0);
}
