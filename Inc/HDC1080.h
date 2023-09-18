/***
*** HDC1080 STM32 HAL LIBRARY
*** Writted by: Malefetsane Lenka
*** Date:     18th May 2023
*/

#ifndef HDC1080_H
#define HDC1080_H
#include "stm32f0xx_hal.h"


#define HDC1080_ADD 0x40
#define HDC1080_CONFIG 0x02
#define TEMP_REG 0x00
#define HUM_REG 0x01
#define DEVICE_ID   0xFF
#define MANUF_ID    0xFE



HAL_StatusTypeDef HDC1080_Init(I2C_HandleTypeDef* hi2c);
HAL_StatusTypeDef getMeasurement(I2C_HandleTypeDef* hi2c,uint8_t* pData);
HAL_StatusTypeDef get_ids(I2C_HandleTypeDef *hi2c,uint8_t* pData);

#endif
