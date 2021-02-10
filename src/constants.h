#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// Pin Assignments
#define ENCODER_PIN_A   0
#define ENCODER_PIN_B   1
#define ENCODER_BUTTON  2

#define I2C_SCL         19
#define I2C_SDA         18

#define SPI_CS          10
#define SPI_DOUT        11
#define SPI_DIN         12
#define SPI_CLK         14

// Menu
#define MENU_ITEM_LENGTH 16
#define MENU_DISPLAY_SIZE 4

#define ARRAY_SIZE(x) ((unsigned int) (sizeof(x) / sizeof(x[0])))

#endif