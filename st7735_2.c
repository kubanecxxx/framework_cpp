/** @defgroup ST7735_display
 * @{
 */

/*!
* \brief nice driver
*/

#include "st7735_2.h"
#include "fonts/fonts.h"
#include "string.h"

#ifdef ST7735_RAM_BUFFER
uint16_t screen_buffer[ST7735_WIDTH][ST7735_HEIGHT];
#endif

/*************************************************/
/* Private Methods                               */
/*************************************************/

/** \fn void st7735WriteCmd(uint8_t command) 
\brief Send command to st7735 via already configured HW SPI
\param command 
*/
void st7735WriteCmd(uint8_t command) 
{
  CLR_CS;
  systickDelay(10);
  CLR_RS;

  low_level_output(command);

  SET_CS; 
}

/*************************************************/
void st7735WriteData(uint8_t data)
{
  CLR_CS;
  systickDelay(10);
  SET_RS; 

  low_level_output(data);

  SET_CS;
}

/*************************************************/
void st7735SetAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  st7735WriteCmd(ST7735_CASET);   // column addr set
  st7735WriteData(0x00);
  st7735WriteData(x0+2);          // XSTART 
  st7735WriteData(0x00);
  st7735WriteData(x1+2);          // XEND

  st7735WriteCmd(ST7735_RASET);   // row addr set
  st7735WriteData(0x00);
  st7735WriteData(y0+1);          // YSTART
  st7735WriteData(0x00);
  st7735WriteData(y1+1);          // YEND
}

/*************************************************/
void st7735InitDisplay(void)
{
  st7735WriteCmd(ST7735_SWRESET); // software reset
  systickDelay(50);
  st7735WriteCmd(ST7735_SLPOUT);  // out of sleep mode
  systickDelay(500);
  
  st7735WriteCmd(ST7735_COLMOD);  // set color mode
  st7735WriteData(0x05);          // 16-bit color
  systickDelay(10);
  
  st7735WriteCmd(ST7735_FRMCTR1); // frame rate control
  st7735WriteData(0x00);          // fastest refresh
  st7735WriteData(0x06);          // 6 lines front porch
  st7735WriteData(0x03);          // 3 lines backporch
  systickDelay(10);
  
  st7735WriteCmd(ST7735_MADCTL);  // memory access control (directions)
  st7735WriteData(0xC8);          // row address/col address, bottom to top refresh
  
  st7735WriteCmd(ST7735_DISSET5); // display settings #5
  st7735WriteData(0x15);          // 1 clock cycle nonoverlap, 2 cycle gate rise, 3 cycle oscil. equalize
  st7735WriteData(0x02);          // fix on VTL
 
  st7735WriteCmd(ST7735_INVCTR);  // display inversion control
  st7735WriteData(0x0);           // line inversion
 
  st7735WriteCmd(ST7735_PWCTR1);  // power control
  st7735WriteData(0x02);          // GVDD = 4.7V 
  st7735WriteData(0x70);          // 1.0uA
  systickDelay(10);
  st7735WriteCmd(ST7735_PWCTR2);  // power control
  st7735WriteData(0x05);          // VGH = 14.7V, VGL = -7.35V 
  st7735WriteCmd(ST7735_PWCTR3);  // power control
  st7735WriteData(0x01);          // Opamp current small 
  st7735WriteData(0x02);          // Boost frequency
  
  
  st7735WriteCmd(ST7735_VMCTR1);  // power control
  st7735WriteData(0x3C);          // VCOMH = 4V
  st7735WriteData(0x38);          // VCOML = -1.1V
  systickDelay(10);
  
  st7735WriteCmd(ST7735_PWCTR6);  // power control
  st7735WriteData(0x11); 
  st7735WriteData(0x15);
  
  st7735WriteCmd(ST7735_GMCTRP1);
  st7735WriteData(0x09);
  st7735WriteData(0x16);
  st7735WriteData(0x09);
  st7735WriteData(0x20);
  st7735WriteData(0x21);
  st7735WriteData(0x1B);
  st7735WriteData(0x13);
  st7735WriteData(0x19);
  st7735WriteData(0x17);
  st7735WriteData(0x15);
  st7735WriteData(0x1E);
  st7735WriteData(0x2B);
  st7735WriteData(0x04);
  st7735WriteData(0x05);
  st7735WriteData(0x02);
  st7735WriteData(0x0E);
  st7735WriteCmd(ST7735_GMCTRN1);
  st7735WriteData(0x0B); 
  st7735WriteData(0x14); 
  st7735WriteData(0x08); 
  st7735WriteData(0x1E); 
  st7735WriteData(0x22); 
  st7735WriteData(0x1D); 
  st7735WriteData(0x18); 
  st7735WriteData(0x1E); 
  st7735WriteData(0x1B); 
  st7735WriteData(0x1A); 
  st7735WriteData(0x24); 
  st7735WriteData(0x2B); 
  st7735WriteData(0x06); 
  st7735WriteData(0x06); 
  st7735WriteData(0x02); 
  st7735WriteData(0x0F); 
  systickDelay(10);
  
  st7735WriteCmd(ST7735_CASET);   // column addr set
  st7735WriteData(0x00);
  st7735WriteData(0x02);          // XSTART = 2
  st7735WriteData(0x00);
  st7735WriteData(0x81);          // XEND = 129

  st7735WriteCmd(ST7735_RASET);   // row addr set
  st7735WriteData(0x00);
  st7735WriteData(0x02);          // XSTART = 1
  st7735WriteData(0x00);
  st7735WriteData(0x81);          // XEND = 160

  st7735WriteCmd(ST7735_NORON);   // normal display on
  systickDelay(10);
  
  st7735WriteCmd(ST7735_DISPON);
  systickDelay(500);
}

/*************************************************/
/* Public Methods                                */
/*************************************************/

/*************************************************/
void lcdInit(void)
{
  // Set control pins to output
	low_level_init();

  // Set pins low by default (except reset)
  CLR_RS;
  CLR_SDA;
  CLR_SCL;
  SET_CS;
  CLR_BL;
  SET_RES;

  // Reset display
  CLR_RES;
  systickDelay(50);
  SET_RES;

  // Run LCD init sequence
  st7735InitDisplay();

  // Fill black
  lcdFillRGB(0);
}

/*************************************************/
void lcdTest(void)
{
  uint8_t i = 0;
  for (i = 0; i < 100; i++)
  {
    lcdDrawPixel(i, i, 0xFF0F);
  }
}

/*************************************************/
void lcdFillRGB(uint16_t color)
{
  uint8_t x, y;
  st7735SetAddrWindow(0, 0, lcdGetWidth() - 1, lcdGetHeight() - 1);
  st7735WriteCmd(ST7735_RAMWR);  // write to RAM
  for (x=0; x < lcdGetWidth(); x++) 
  {
    for (y=0; y < lcdGetHeight(); y++) 
    {
      st7735WriteData(color >> 8);    
      st7735WriteData(color);    
    }
  }
  st7735WriteCmd(ST7735_NOP);
}

/*************************************************/
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
  st7735SetAddrWindow(x,y,x+1,y+1);
  st7735WriteCmd(ST7735_RAMWR);  // write to RAM
  st7735WriteData(color >> 8);  
  st7735WriteData(color);
}

/*************************************************/
void lcdDrawHLine(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color)
{
  // Allows for slightly better performance than setting individual pixels
  uint16_t x, pixels;

  if (x1 < x0)
  {
    // Switch x1 and x0
    x = x1;
    x1 = x0;
    x0 = x;
  }

  // Check limits
  if (x1 >= lcdGetWidth())
  {
    x1 = lcdGetWidth() - 1;
  }
  if (x0 >= lcdGetWidth())
  {
    x0 = lcdGetWidth() - 1;
  }

  st7735SetAddrWindow(x0, y, lcdGetWidth(), y + 1);
  st7735WriteCmd(ST7735_RAMWR);  // write to RAM
  for (pixels = 0; pixels < x1 - x0 + 1; pixels++)
  {
    st7735WriteData(color >> 8);  
    st7735WriteData(color);
  }
  st7735WriteCmd(ST7735_NOP);
}

/*************************************************/
void lcdDrawVLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color)
{
  // Allows for slightly better performance than setting individual pixels
  uint16_t y, pixels;

  if (y1 < y0)
  {
    // Switch y1 and y0
    y = y1;
    y1 = y0;
    y0 = y;
  }

  // Check limits
  if (y1 >= lcdGetHeight())
  {
    y1 = lcdGetHeight() - 1;
  }
  if (y0 >= lcdGetHeight())
  {
    y0 = lcdGetHeight() - 1;
  }

  st7735SetAddrWindow(x, y0, x, lcdGetHeight());
  st7735WriteCmd(ST7735_RAMWR);  // write to RAM
  for (pixels = 0; pixels < y1 - y0 + 1; pixels++)
  {
    st7735WriteData(color >> 8);  
    st7735WriteData(color);
  }
  st7735WriteCmd(ST7735_NOP);
}

/*************************************************/
uint16_t lcdGetWidth(void)
{
  return ST7735_WIDTH;
}

/*************************************************/
uint16_t lcdGetHeight(void)
{
  return ST7735_HEIGHT;
}

/*************************************************/
/**
 * @brief dierect put char to display
 * @param character to be sent to display
 * @param x coordinate
 * @param y coordinate
 * @param color 16-bit
 * @param size of font
 */
void lcdPutchar(uint8_t znak, uint16_t x, uint16_t y, uint16_t color, uint8_t size)
{

	uint8_t i,j;
	uint32_t temp;
	const uint8_t * temp2  = Fonts_GetChar(znak,size);

	if (size == 8)
	for (i = 0 ; i < size ; i++)
	{
		temp = temp2[i];
		for (j = 0 ; j < size ; j++)
		{
		  if (temp & (1 << j))
		  {
			  lcdDrawPixel(x+i,y+j,color);
		  }
		}
	}
	if (size == 16)
		for (i = 0 ; i < size ; i++)
			{
				temp = temp2[i];
				temp |= (temp2[i+16] << 8);
				//endian conversion
				//temp = (temp1 << 8) | (temp1 >> 8);
				for (j = 0 ; j < size ; j++)
				{
				  if (temp & (1 << j))
				  {
					  lcdDrawPixel(x+i,y+j,color);
				  }
				}
			}
}

/**
 * @brief direct put string to display, using lcdPutchar
 * @param data - null terminated string of characters
 * @param x  coordinate of the first char
 * @param y  coordinate of the first char
 * @param color 16-bit
 * @param size of font
 */
void lcdPutString (const char * data, uint16_t x, uint16_t y, uint16_t color, uint8_t size)
{
	while (*data != 0)
	{
		lcdPutchar((uint8_t)*(data++),x,y,color,size);
		x += size;
	}
}

void lcdPutsStringBackground (const char * data, uint16_t x, uint16_t y, uint16_t color,uint16_t background_color, uint8_t size)
{
	uint16_t x2 = size * strlen(data);
	uint16_t temp = x;
	uint16_t temp_y =y;

	  st7735SetAddrWindow(x, y, x + x2 - 1, y + size -1);
	  st7735WriteCmd(ST7735_RAMWR);  // write to RAM

	  for (x=0; x < x2; x++)
	  {
	    for (y=0; y < size; y++)
	    {
	      st7735WriteData(background_color >> 8);
	      st7735WriteData(background_color);
	    }
	  }
	  st7735WriteCmd(ST7735_NOP);

	  lcdPutString(data,temp,temp_y,color,size);

}



#ifdef ST7735_RAM_BUFFER
/**
 * @brief put char into screen_buffer
 * @todo maybe DMA
 * @param character to be stored in buffer
 * @param x  coordinate of the first character
 * @param y coordinate of the first character
 * @param color 16-bit
 * @param size of fonts
 */
void lcdPutCharRam (uint8_t znak, uint16_t x, uint16_t y, uint16_t color, uint8_t size)
{
	uint8_t i,j;
	uint8_t temp;
	const uint8_t * temp2  = Fonts_GetChar(znak,size);

	for (i = 0 ; i < size ; i++)
	{
		temp = temp2[i];
		for (j = 0 ; j < size ; j++)
		{
		  if (temp & (1 << j))
		  {
			  screen_buffer[x+i][y+j] = color;
		  }
		}
	}
	for (i= 0 ; i < 50 ; i++)
		screen_buffer[i][1] = 0;
}
/**
 * @defgroup ST7735 internal ram buffer functions
 * @{
 */

/**
 * @brief put character string to screen_buffer
 * @param data character string
 * @param x,y coordinates of the first character
 * @param color 16-bit
 * @param size of font
 */
void lcdPutStringRam (const uint8_t * data, uint16_t x , uint16_t y, uint16_t color, uint8_t size)
{
	while (*data != 0)
		lcdPutCharRam(*data++,x,y,color,size);
}

/**
 * @brief put same color to entire screen_buffer
 * @param 16-bit color
 * @todo edit to use DMA
 */
void lcdFillColorRam (uint16_t color)
{
	unsigned char i,j;

	for (i = 0 ; i < ST7735_WIDTH ; i++)
		for (j = 0 ; j < ST7735_HEIGHT ; j++)
			screen_buffer[i][j] = color;
}

/**
 * @brief write screen_buffer to real display
 * @todo rozjet HW SPI a použit k tomu DMA
 *	prepracovat na low_level send pole
 */
void lcdWriteBuffer (void)
{
	lcdWriteBufferPart(0,0,ST7735_WIDTH, ST7735_HEIGHT);
}

/**
 * @brief put part of screen buffer to real display
 * @todo v rámci portovatelnosti udělat low_level_send_pole via DMA + callback
 * @param x1 x2 y1 y2 coordinates of window to be put to real display
 */
void lcdWriteBufferPart (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint8_t i,j;
	st7735SetAddrWindow(x1, y1, x2 - 1 , y2 - 1);
	st7735WriteCmd(ST7735_RAMWR);  // write to RAM

	for ( i = x1 ; i < x2 ; i++)
	{
		for ( j = y1  ; j < y2; j++)
		{
			st7735WriteData(screen_buffer[i][j] >> 8);
			st7735WriteData(screen_buffer[i][j]);
		}
	}
	st7735WriteCmd(ST7735_NOP);
}

/**
 * @brief draw line to internal buffer
 * @param coordinates
 * @param color
 * @param width
 */
void lcdDrawLineRam (uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint32_t x,y;
	uint32_t k,q;
	//udělat rovnicu přimky a pak dosazovat
	x = x2 - x1;
	y = y2 - y1;

	k = (1000*y)/x;
	q = (((y2 * x1 - y1))*1000 / (x1-1));

	//y = k*x + q
	//

	for ( ; x1 < x2 ; x1++)
	{
		y = (k * x1) + q;
		y /= 1000;
		screen_buffer[x1][y] = color;
	}
}
/*
 * @todo použit lcd drawline až bude hotovy
 */
void lcdDrawRectangleRam(uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	for ( ; x1 < x2 ; x1++)
		for (; y1 < y2 ; y1++)
		{
			//if ()
				screen_buffer[x1][y1] = color;
		}
}
#endif

uint16_t lcdColorConversion(uint16_t r, uint16_t g, uint16_t b)
{
	return b;
}

/**
 * @}
 */




/**
 * @}
 */
