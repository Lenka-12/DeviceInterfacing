
/**
** @Author: Malefetsane Lenka
** Date:  May,18th  2023
*/
#include "HDC1080.h"
#include "stm32f0xx_hal.h"
#include <string.h>




/**
  * @brief  Initializes HDC1080 to measure both temperature and humidity in 14 bit
  *         mode, the Heater is also enabled.
  * @param  pointer to I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @retval HAL status
  */
HAL_StatusTypeDef HDC1080_Init(I2C_HandleTypeDef* hi2c){
	uint16_t config_data = 0x9000;
	uint8_t tx_buf[3];

	// First byte of transmit buffer is the register address (0x02)
	tx_buf[0] = HDC1080_CONFIG;

	// Copy the configuration data (2 bytes) to the transmit buffer
	tx_buf[1] = (uint8_t)(config_data >> 8); // MSB configuration
	tx_buf[2] = (uint8_t)(config_data & 0xFF); // LSB Configuration

	// Transmit the data over I2C
	  HAL_StatusTypeDef status;
	  status = HAL_I2C_Master_Transmit(hi2c, HDC1080_ADD <<1, tx_buf, 3, 1000);
	  HAL_Delay(1500);  //Wait for sensor to setup
	  return status;

}


/**
  * @brief  Retrives temperature and humidity from HDC1080 at the same time
  * @param  Pointer to hi2c I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  temp pointer to variable that will hold temperature raw binary value.
  * @param  humidity pointer to variable that will hold himidity binary value.
  * @retval HAL status
  */
HAL_StatusTypeDef getMeasurement(I2C_HandleTypeDef* hi2c,uint8_t* pData){
	uint8_t buffer[4];  //buffer to store sensor data
	buffer[0] = TEMP_REG;

	HAL_StatusTypeDef status;
	status=HAL_I2C_Master_Transmit(hi2c, HDC1080_ADD <<1, buffer, 1, 1000);
	if (status != HAL_OK){
		return status;
	}
	else{
		HAL_Delay(500); //wait for measurement to complete
		status = HAL_I2C_Master_Receive(hi2c, HDC1080_ADD <<1|1, pData, 4, 1000);
		return status;

	}


}
/*
 * @Brief: Reads HDC1080, manufacture ID and Device ID
 */
HAL_StatusTypeDef get_ids(I2C_HandleTypeDef *hi2c,uint8_t* pData){
	uint8_t buffer[1];
	buffer[0] = DEVICE_ID;
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Transmit(hi2c, HDC1080_ADD<<1, buffer, 1, 100);

	status = HAL_I2C_Master_Receive(hi2c,HDC1080_ADD <<1|1,pData, 2, 100);
	pData+=2;

	buffer[0] = MANUF_ID;

	status = HAL_I2C_Master_Transmit(hi2c, HDC1080_ADD<<1, buffer, 1, 100);

	status = HAL_I2C_Master_Receive(hi2c,HDC1080_ADD <<1|1,pData, 2, 100);


	return status;



}

