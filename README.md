# DeviceInterfacing

This contains stm32 HAL compatible code for TI temperature and humidity I2C sensor(HDC1080),AT24C256C EEEPROM and 16x2 display LCD

### HOW to Use this drivers

1. Clone the repository to the local machine
2. Copy .h files to Core/Inc folder from stm32 cube generated project
3. Copy .c files to Core/Src folder from stm32 cube generated project

#### Note that EEEPROM address incrementing is taken care by the code, but there is no handling beyond 512th page

#### LCD code is written for 4 data lines, during stm32cubeide/cubemx code initialisation enter user label for the pins as follows
LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7


* HAPPY EMBEDDED PROGRAMMING