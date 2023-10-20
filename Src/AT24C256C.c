/*
 * AT24C256C.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Malefetsane Lenka
 */

#include "AT24C256C.h"

/*
 *  @Brief: Writes data to EEPROM
 *	@param: hi2c  Pointer to I2C_HandleTypeDef structure that contains
 *        the configuration information for the specified I2C.
 *  @param: pData, pointer to the transmit buffer
 *  @param: number of bytes to transmit buffer, must always be less than 256
 *  @retval: HAL_StatusTypedef
 *  @Note:   Page increment and byte increment is taken care by this function
 */
HAL_StatusTypeDef write(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size) {
  HAL_StatusTypeDef status;

  uint8_t temp = size / NUM_BYTES_PP;
  static uint8_t byte = 0;
  static uint16_t page = 0;

  if (temp >= 1) {
    for (int i = 0; i < temp; i++) {
      status = HAL_I2C_Mem_Write(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                 pData, NUM_BYTES_PP, 100);
      HAL_Delay(1000); // Wait for write to complete
      page += 1;
      if (i < (temp - 1)) {
        pData += NUM_BYTES_PP;
      }
    }
    // Extra byte left
    if (size % NUM_BYTES_PP) {
      pData += NUM_BYTES_PP;
      status = HAL_I2C_Mem_Write(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                 pData, size % NUM_BYTES_PP, 100);
      HAL_Delay(1000); // Wait for write to complete
      byte += (size % NUM_BYTES_PP);
    }
  }

  else {
    uint8_t byteLeft = NUM_BYTES_PP - byte;

    if (size >= byteLeft) {
      status = HAL_I2C_Mem_Write(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                 pData, byteLeft, 100);
      byte = 0;
      page += 1;
      HAL_Delay(1000);

      if (size - byteLeft) {
        pData += byteLeft;
        status = HAL_I2C_Mem_Write(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                   pData, size - byteLeft, 100);
        HAL_Delay(1000);
        byte += (size - byteLeft); // Inceremnt
      }

    }

    else {
      status = HAL_I2C_Mem_Write(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                 pData, size, 100);
      HAL_Delay(1000);
      byte += (size); // Inceremnt
    }
  }

  return status;
}
/*
 *  @Brief: Reads data from EEPROM
 *	@param: hi2c  Pointer to I2C_HandleTypeDef structure that contains
 *        the configuration information for the specified I2C.
 *  @param: pData, pointer to the receive buffer
 *  @param: number of bytes in the receive buffer, must always be less than 256
 *  @retval: HAL_StatusTypedef
 *  @Note:   Page increment and byte increment is taken care by this function
 */

HAL_StatusTypeDef read(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size) {
  HAL_StatusTypeDef status;

  uint8_t temp = size / NUM_BYTES_PP;
  static uint8_t byte = 0;
  static uint8_t page = 0;

  if (temp >= 1) {
    for (int i = 0; i < temp; i++) {
      status = HAL_I2C_Mem_Read(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                pData, NUM_BYTES_PP, 100);
      HAL_Delay(1000); // Wait for write to complete
      page += 1;
      if (i < (temp - 1)) {
        pData += NUM_BYTES_PP;
      }
    }
    // Extra byte left
    if (size % NUM_BYTES_PP) {
      pData += NUM_BYTES_PP;
      status = HAL_I2C_Mem_Read(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                pData, size % NUM_BYTES_PP, 100);
      HAL_Delay(1000); // Wait for write to complete
      byte += (size % NUM_BYTES_PP);
    }
  }

  else {
    uint8_t byteLeft = NUM_BYTES_PP - byte;

    if (size >= byteLeft) {
      status = HAL_I2C_Mem_Read(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                pData, byteLeft, 100);
      byte = 0;
      page += 1;
      HAL_Delay(1000);

      if (size - byteLeft) {
        pData += byteLeft;
        status = HAL_I2C_Mem_Read(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                  pData, size - byteLeft, 100);
        HAL_Delay(1000);
        byte += (size - byteLeft); // Inceremnt
      }

    }

    else {
      status = HAL_I2C_Mem_Read(hi2c, I2C_ADDRESS << 1, page << 6 | byte, 2,
                                pData, size, 100);
      HAL_Delay(1000);
      byte += (size); // Inceremnt
    }
  }

  return status;
}
