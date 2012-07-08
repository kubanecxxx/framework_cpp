/**************************************************************************/
/*! 
*/
/**************************************************************************/
#ifndef __ST7735_H__
#define __ST7735_H__

#ifdef __cplusplus
	extern "C" {
#endif


#include "port/st7735_port.h"
/**************************************************************************
    ST7735 CONNECTOR
    -----------------------------------------------------------------------
    Pin   Function        Notes
    ===   ==============  ===============================
      1   NC
      2   GND
      3   LED K/-
      4   LED A/+         3.0V
      5   GND
      6   RESET
      7   RS
      8   SDA   - MOSI    Serial Data
      9   SCL   - SCK     Serial Clock
     10   VCC             2.8-3.4V
     11   VCC             2.8-3.4V
     12   CS
     13   GND
     14   NC

 **************************************************************************/

#ifdef ST7735_default_port
	#define CLR_RS     DISPLAY_RS=0
	#define SET_RS     DISPLAY_RS=1
	#define CLR_SDA    DISPLAY_MOSI=0
	#define SET_SDA    DISPLAY_MOSI=1
	#define CLR_SCL    DISPLAY_SCK=0
	#define SET_SCL   	DISPLAY_SCK=1
	#define CLR_CS   	DISPLAY_CS=0
	#define SET_CS  	DISPLAY_CS=1
	#define CLR_RES		DISPLAY_RESET=0
	#define SET_RES		DISPLAY_RESET=1
	//backlight
	#define CLR_BL		bit_clr(PORTD,2)
	#define SET_BL		bit_set(PORTD,2)
#endif


#define ST7735_NOP      (0x0)
#define ST7735_SWRESET  (0x01)
#define ST7735_SLPIN    (0x10)
#define ST7735_SLPOUT   (0x11)
#define ST7735_PTLON    (0x12)
#define ST7735_NORON    (0x13)
#define ST7735_INVOFF   (0x20)
#define ST7735_INVON    (0x21)
#define ST7735_DISPON   (0x29)
#define ST7735_CASET    (0x2A)
#define ST7735_RASET    (0x2B)
#define ST7735_RAMWR    (0x2C)
#define ST7735_COLMOD   (0x3A)
#define ST7735_MADCTL   (0x36)
#define ST7735_FRMCTR1  (0xB1)
#define ST7735_INVCTR   (0xB4)
#define ST7735_DISSET5  (0xB6)
#define ST7735_PWCTR1   (0xC0)
#define ST7735_PWCTR2   (0xC1)
#define ST7735_PWCTR3   (0xC2)
#define ST7735_VMCTR1   (0xC5)
#define ST7735_PWCTR6   (0xFC)
#define ST7735_GMCTRP1  (0xE0)
#define ST7735_GMCTRN1  (0xE1)

#define ST7735_WIDTH 128
#define ST7735_HEIGHT 160

uint16_t lcdGetHeight(void);
uint16_t lcdGetWidth(void);
void lcdInit(void);
void lcdTest(void);
void lcdFillRGB(uint16_t color);
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void lcdDrawHLine(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color);
void lcdDrawVLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color);
void lcdPutchar(uint8_t znak, uint16_t x, uint16_t y, uint16_t color, uint8_t size);
void lcdPutString (const char * data, uint16_t x, uint16_t y, uint16_t color, uint8_t size);
void lcdPutsStringBackground (const char * data, uint16_t x, uint16_t y, uint16_t color,uint16_t background_color, uint8_t size);

#ifdef ST7735_RAM_BUFFER
//ram functions
void lcdPutCharRam (uint8_t znak, uint16_t x, uint16_t y, uint16_t color, uint8_t size);
void lcdPutStringRam (const uint8_t * data, uint16_t x , uint16_t y, uint16_t color, uint8_t size);
void lcdFillColorRam (uint16_t color);
void lcdWriteBuffer (void);
void lcdWriteBufferPart (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
#endif

#ifdef __cplusplus
}
#endif

#endif
