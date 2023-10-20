/*
 * hdc1080_driver.c
 *
 *  Created on: Oct 20, 2023
 *      Author: malef
 */


#include "hdc1080_driver.h"
static HAL_StatusTypeDef transmit_regptr(I2C_HandleTypeDef *hi2c,uint8_t reg);

/*
 *@Brief: Initialises HDC1080 parameters to default, heater is enabled
 */
void hdc1080_setdefault(HDC_Config_t *phdc) {
  phdc->humidityResolution = HUMIDITY_RES_14BITS; /*14 bits Resolution*/
  phdc->heaterCtrl = HEATER_ON;                   /*set heater on*/
  phdc->readMode = TEMP_OR_HUM; /*Read temperature and humidity independently*/
  phdc->temperatureResolution = TEMP_RES_14BITS; /*14 bit resolution*/
  phdc->softwareResetCtrl = NORMAL_OP;        /*Normal Mode*/
}

/*
 * @Brief: Reads device information, like device ids and serial ID, please see device datasheet
 * @Param: pData, pointer to 10 bytes long array to hold device info
 * @Note: First 6 bytes are serial ID, last 2 bytes are device id and manufacture id
 */
HAL_StatusTypeDef get_deviceinfo(I2C_HandleTypeDef *hi2c, uint8_t *pData){
	HAL_StatusTypeDef status;

	for(int i=0; i<5; i++){
		status = transmit_regptr(hi2c,SERIAL_REG0+i);  /*transmit register ptr*/
		if(status!=HAL_OK){
			return status;
		}
		HAL_Delay(100);  //wait for 100ms


		status = HAL_I2C_Master_Receive(hi2c, DEVICE_ADDRESS<<1|1, &pData[i*2], 2, 100);  /*read register data*/
		if(status!=HAL_OK){
				return status;
		}
		HAL_Delay(100);  //wait for 100ms



	}

	return status;

}

HAL_StatusTypeDef hdc1080_config(I2C_HandleTypeDef *hi2c,HDC_Config_t* phdc){
	uint8_t tx_buffer[3]={CONFIG_REG,0,0};
	tx_buffer[1] |= ((phdc->softwareResetCtrl<<7)|(phdc->heaterCtrl<<5)|(phdc->readMode<<4)|(phdc->temperatureResolution<<2)|(phdc->humidityResolution));

	return HAL_I2C_Master_Transmit(hi2c, DEVICE_ADDRESS<<1, tx_buffer, 3, 100);

}


HAL_StatusTypeDef get_deviceconfig_andstatus(I2C_HandleTypeDef *hi2c,uint8_t *pData){
	HAL_StatusTypeDef status;

	status = transmit_regptr(hi2c,CONFIG_REG);
	HAL_Delay(100);  /*wait for 100ms*/

	if(status!=HAL_OK){
		return status;
	}

	return HAL_I2C_Master_Receive(hi2c, DEVICE_ADDRESS<<1|1, pData, 2, 100);
}

/*
 * @Brief: Transmit given hdc1080 register pointer
 * @Param: hi2c, pointer to i2c handle configuration structure
 * @Param: reg, 8bit internal hdc1080 register pointer
 * @Retval: HAL_StatusTypeDef
 */
static HAL_StatusTypeDef transmit_regptr(I2C_HandleTypeDef *hi2c,uint8_t reg){
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Transmit(hi2c, DEVICE_ADDRESS<<1, &reg, 1, 100);

	return status;
}

/*
 * @Brief: Read 2 bytes of humidity
 */
HAL_StatusTypeDef get_humidity(I2C_HandleTypeDef *hi2c,uint8_t *pData){
	HAL_StatusTypeDef status;
	status = transmit_regptr(hi2c, HUM_REG);
	HAL_Delay(1000);   /*wait for measurement to complete*/

	if(status!=HAL_OK){
		return status;
	}

	return HAL_I2C_Master_Receive(hi2c, DEVICE_ADDRESS<<1|1, pData, 2, 100);
}



/*
 * @Brief: Read 2 bytes of temperature
 */
HAL_StatusTypeDef get_temperature(I2C_HandleTypeDef *hi2c,uint8_t *pData){
	HAL_StatusTypeDef status;
	status = transmit_regptr(hi2c, TEMP_REG);
	HAL_Delay(1000);   /*wait for measurement to complete*/

	if(status!=HAL_OK){
		return status;
	}

	return HAL_I2C_Master_Receive(hi2c, DEVICE_ADDRESS<<1|1, pData, 2, 100);
}



/*
 * @Brief: Read temperature and humidity
 */
HAL_StatusTypeDef  get_humandtemp(I2C_HandleTypeDef *hi2c,uint8_t *pData){
	HAL_StatusTypeDef status;
	status = transmit_regptr(hi2c, TEMP_REG);

	HAL_Delay(1000);   /*wait for measurement to complete*/

	if(status!=HAL_OK){
		return status;
	}

	return HAL_I2C_Master_Receive(hi2c, DEVICE_ADDRESS<<1|1, pData, 4, 100);
}
