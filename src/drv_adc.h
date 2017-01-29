/*********************************************************************************************************
 *
 * File                : drv_adc.h
 * Hardware Environment: BeagleBoneBlack
 * Build Environment   : GCC in BeagleBoneBlack
 * Version             : V1.0
 * By                  : Amaruk
 *                      https://amaruk.github.io/
 *
 *********************************************************************************************************/
#ifndef DRV_ADC_H_
#define DRV_ADC_H_

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

#define STATUS_RELEASE	0
#define STATUS_PRESS	1

#define THREASHOLD_GND		2700	/* ADC value when connected to GND */
#define THREASHOLD_VALID	3700	/* Valid ADC value when connected to VDD */
#define FLT_CNT_PRESS		2		/* Press filter counter */
#define FLT_CNT_RELEASE		2		/* Release filter counter */
#define FLT_CNT_INIT		0		/* Initial value of counters */

extern int adcGetChVal(int ch);
extern void adcInit(void);

#endif /* DRV_ADC_H_ */
