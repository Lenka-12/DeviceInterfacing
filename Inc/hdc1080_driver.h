#ifndef INC_HDC1080_DRIVER_H_
#define INC_HDC1080_DRIVER_H_

#include "stm32f0xx_hal.h"
#define DEVICE_ADDRESS 0x40 /*7  bit i2c device address*/
#define MEMADD_SIZE 2       /*Memory address size*/

/*Device internal addresses*/
#define TEMP_REG 0x00   /*temperetaure register*/
#define HUM_REG 0x01    /*humidity value register*/
#define CONFIG_REG 0x02 /*Configuration register*/

#define MANUFID_REG 0xFE  /*Manufacture ID Register*/
#define DEVICEID_REG 0xFF /*Device ID register*/

/*******************************************************
 * Serial ID registers, reset values are device indepent
 *******************************************************/

#define SERIAL_REG0 0xFB
#define SERIAL_REG1 0xFC
#define SERIAL_REG2 0xFD

/****************************************************
 *User configurable ITEMS
 ****************************************************/

/*
 *@Temperature Resolution
 */
#define TEMP_RES_14BITS 0x0
#define TEMP_RES_11BITS 0x1

/*
 *@Humidity Resolution
 */

#define HUMIDITY_RES_14BITS 0x00
#define HUMIDITY_RES_11BITS 0x01
#define HUMIDITY_RES_8BITS 0x10

/*
 *@MODE
 */
#define TEMP_OR_HUM 0x0
#define TEMP_AND_HUM 0x1

/*
 *@Heater Enabling
 */
#define HEATER_OFF 0x0
#define HEATER_ON 0x1

/*
 *@Software Reset
 */
#define SOFTWARE_RESET 0x1
#define NORMAL_OP 0x0

typedef struct {
  uint8_t temperatureResolution; // see @Temperature Resolution
  uint8_t humidityResolution;    // see @Humidity Resolution
  uint8_t readMode;              // see @MODE
  uint8_t heaterCtrl;            // see @Heater Enabling
  uint8_t softwareResetCtrl;     //  see @Software Reset
} HDC_Config_t;

void hdc1080_setdefault(HDC_Config_t *phdc);

HAL_StatusTypeDef get_deviceinfo(I2C_HandleTypeDef *hi2c, uint8_t *pData);
HAL_StatusTypeDef hdc1080_config(I2C_HandleTypeDef *hi2c,HDC_Config_t* phdc);
HAL_StatusTypeDef get_deviceconfig_andstatus(I2C_HandleTypeDef *hi2c,uint8_t *pData);
HAL_StatusTypeDef get_humidity(I2C_HandleTypeDef *hi2c,uint8_t *pData);
HAL_StatusTypeDef get_temperature(I2C_HandleTypeDef *hi2c,uint8_t *pData);
HAL_StatusTypeDef get_humandtemp(I2C_HandleTypeDef *hi2c,uint8_t *pData);


#endif
