/*
 * lcd_driver.c
 *
 *  Created on: Sep 24, 2023
 *      Author: malef
 */

#include "lcd_driver.h"
#include "stm32f0xx_hal.h"
#include "main.h"

static void lcd_enable();
static void write_nibble(uint8_t value);

/*
 * @Brief: Send command to the LCD
 * @Param: 8bit commad
 * @Retval: None
 */
void lcd_send_command(uint8_t cmd){
	/*set RS low*/
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	write_nibble(cmd>>4);  /*send upper nibble*/
	write_nibble(cmd&0xF); /*send lower nibble*/

	HAL_Delay(10);  /*wait*/
}

/*
 *
 */
void lcd_print_char(uint8_t data){
	/*set RS high*/
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	write_nibble(data>>4);  /*send upper nibble*/
	write_nibble(data&0xF); /*send lower nibble*/

}


void lcd_init(void){
	/*LCD initialization*/
	HAL_Delay(40);
	write_nibble(0x3);
	/*wait*/
	HAL_Delay(5);
	write_nibble(0x3);
	/*wait*/
	HAL_Delay(1);
	write_nibble(0x3);
	write_nibble(0x2);

	/*function set command*/

	lcd_send_command(LCD_CMD_4DL_5X8F);

	/*display on and cursor on*/
	lcd_send_command(LCD_CMD_DON_CURON);

	/*display clear*/
	 lcd_display_clear();

	/*Entry mode set*/
	lcd_send_command(LCD_CMD_INCADD);




}


static void lcd_enable(){
	/*sent enable pulse*/
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);

}


static void write_nibble(uint8_t value){
	/*LSB goes to DB4, MSB to D7*/
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (GPIO_PinState)((value>>0)&1));
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (GPIO_PinState)((value>>1)&1));
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (GPIO_PinState)((value>>2)&1));
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (GPIO_PinState)((value>>3)&1));
	lcd_enable();

}

void lcd_display_clear(void){
	lcd_send_command(LCD_CMD_DIS_CLEAR);
	HAL_Delay(3); /*wait*/

}

void lcd_print_string(char* message){
	do{
		lcd_print_char((uint8_t)*message++);
	}while(*message!='\0');
}

void lcd_display_return_home(void){
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);
	HAL_Delay(3);
}



void lcd_set_cursor(uint8_t row,uint8_t column){
	column--;

	switch(row)
	{
		case 1:
			/* Set cursor to first row and add index*/
			lcd_send_command(column|=0x80);
			break;
		case 2:
			/*set cursor to 2nd row address and add index*/
			lcd_send_command(column|=0xC0);
			break;
		default:
			break;
	}
}

