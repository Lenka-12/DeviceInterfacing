/*
 * AT24C256C.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Malefetsane Lenka
 */

#ifndef INC_AT24C256C_H_
#define INC_AT24C256C_H_

#include "stm32f0xx_hal.h"

#define I2C_ADDRESS   0x50             //EEPROM I2C Address
#define NUM_PAGES     512              //Number of pages
#define NUM_BYTES_PP  64               //Bytes per page


HAL_StatusTypeDef write(I2C_HandleTypeDef* hi2c, uint8_t* pData, uint8_t size);
HAL_StatusTypeDef read(I2C_HandleTypeDef* hi2c, uint8_t* pData, uint8_t size);


#endif /* INC_AT24C256C_H_ */
