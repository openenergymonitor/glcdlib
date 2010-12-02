/*
$Id$

glcdremote Remote LCD library!

*/

#include <WProgram.h>

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#define BLACK					0
#define WHITE					1

#define LCDWIDTH				128
#define LCDHEIGHT				64
#define LCDUNUSEDSTARTBYTES 4

#define CMD_DISPLAY_OFF			0xAE		//  1
#define CMD_DISPLAY_ON			0xAF		//  1

#define CMD_SET_DISP_START_LINE	0x40		//  2
#define CMD_SET_PAGE			0xB0		//  3

#define CMD_SET_COLUMN_UPPER	0x10		//  4
#define CMD_SET_COLUMN_LOWER	0x00		//  4

#define CMD_SET_ADC_NORMAL		0xA0		//  8
#define CMD_SET_ADC_REVERSE		0xA1		//  8

#define CMD_SET_DISP_NORMAL		0xA6		//  9
#define CMD_SET_DISP_REVERSE	0xA7		//  9

#define CMD_SET_ALLPTS_NORMAL	0xA4		// 10
#define CMD_SET_ALLPTS_ON		0xA5		// 10
#define CMD_SET_BIAS_9			0xA2		// 11
#define CMD_SET_BIAS_7			0xA3		// 11

#define CMD_RMW					0xE0		// 12
#define CMD_RMW_CLEAR			0xEE		// 13
#define CMD_INTERNAL_RESET		0xE2		// 14
#define CMD_SET_COM_NORMAL		0xC0		// 15
#define CMD_SET_COM_REVERSE		0xC8		// 15
#define CMD_SET_POWER_CONTROL	0x2F		// 16
#define CMD_SET_RESISTOR_RATIO  0x24		// 17
#define CMD_SET_VOLUME_FIRST	0x81		// 18
#define CMD_SET_VOLUME_SECOND	0x00		// 18
#define CMD_SET_STATIC_OFF		0xAC		// 19
#define CMD_SET_STATIC_ON		0xAD		// 19
#define CMD_SET_STATIC_REG		0x00		// 19
//#define CMD_SET_BOOSTER_FIRST	0xF8		// 
//#define CMD_SET_BOOSTER_234		0x00		// 20
//#define CMD_SET_BOOSTER_5		0x01		// 20
//#define CMD_SET_BOOSTER_6		0x03		// 20
#define CMD_NOP					0xE3		// 22
#define CMD_TEST				0xF0		// 23

class glcdremote {
 public:
  glcdremote(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS) :sid(SID), sclk(SCLK), a0(A0), rst(RST), cs(CS) {}
  glcdremote(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST)            :sid(SID), sclk(SCLK), a0(A0), rst(RST), cs(-1) {}

  void st7565_init(void);
  void st7565_command(uint8_t c);
  void st7565_data(uint8_t c);
  void st7565_set_brightness(uint8_t val);
  void clear_display(void);
  void clear_white();
  void clear();
  void display();

  void setpixel   (uint8_t x , uint8_t y   , uint8_t color);
  void fillcircle (uint8_t x0, uint8_t y0  , uint8_t r , uint8_t color);
  void drawcircle (uint8_t x0, uint8_t y0  , uint8_t r , uint8_t color);
  void drawrect   (uint8_t x , uint8_t y   , uint8_t w , uint8_t h , uint8_t color);
  void fillrect   (uint8_t x , uint8_t y   , uint8_t w , uint8_t h , uint8_t color);
  void drawline   (uint8_t x0, uint8_t y0  , uint8_t x1, uint8_t y1, uint8_t color);
  void drawchar   (uint8_t x , uint8_t line, char c );
  void drawstring (uint8_t x , uint8_t line, char *c);
	void drawtriangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t colour);
	void filltriangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t colour);
	void updatedisplayarea(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t reset);
	void setupdatearea(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1, uint8_t allowreduction);
		
  void drawbitmap (uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
  
 	void drawcharx(uint8_t x, uint8_t y, char c);
  void drawstringx(uint8_t x , uint8_t line, char *c);

  byte RemoteLCDhostID;

 	private:
  int8_t sid, sclk, a0, rst, cs;
	void sendlcdmessage(byte *message, byte length);  
};