#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// Pin Assignments
#define ENCODER_PIN_A   0
#define ENCODER_PIN_B   1
#define ENCODER_BUTTON  2

#define I2C_SCL         19
#define I2C_SDA         18

#define SPI_SCK         14
#define SPI_DOUT        11
#define SPI_CS1         10
#define SPI_RST          9
#define SPI_DC           8
#define TFT_LED          6

// Menu
#define MENU_ITEM_LENGTH 16
#define MENU_DISPLAY_SIZE 4

// Convenience function for array size
#define ARRAY_SIZE(x) ((unsigned int) (sizeof(x) / sizeof(x[0])))

#endif