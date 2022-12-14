/* ###################################################################
 **	Filename: HD44780.c
 **  Project:
 **	Processor: LPC845brk
 **	Compiler: gcc version 4.1.1
 **	Date: /10/2022
 **	Name: Sebastian Herrera
 **	Abstract:
 **		HD44780.c source file (user routines)
 ** 	Modified:
 ** 			InitLCD() function: initializing by instruction procedure
 ** ###################################################################*/
#ifndef __LCD16X2_H
#define __LCD16X2_H
/* MODULE LCD16X2 */

//#include "LPC8xx.h"
//#include "Delay.h"
#include "fsl_gpio.h"
#include "digital.h"
#include "LPC845.h"
#include "delay.h"


// Pin  Funcion en el display
#define ENABLE 0x10000000 //-> 28 Enable
#define RW     0x08000000 //-> 27 RW
#define RS     0x04000000 //-> 26 RS
// 0x02000000 -> 25
// 0x01000000 -> 24
#define D7     0x00800000 //-> 23 D7
#define D6     0x00400000 // ->22 D6
#define D5     0x00200000 // ->21 D5
#define D4     0x00100000 // ->20 D4
#define D3     0x00080000 // ->19 D3
#define D2     0x00040000 // ->18 D2
#define D1     0x00020000  //->17 D1
#define D0     0x00010000  //->16  D0
#define CLEAR  0x00010000  //-> cLEAR
#define OFFD0D7 0x00FF0000  // con esta macro puedo poner en '0' desde D0 a D7



#define D44B   0x2    // DB4 para inicializacion con 4 pines esta conectado al pin 38 ->PIO_01
#define D54B   0x40   // DB5 para inicializacion con 4 pines esta conectado al pin 33 ->PIO_06
#define D64B   0x8000 // DB6 para inicializacion con 4 pines esta conectado al pin 28 ->PIO_15
#define D74B   0x4000 // DB7 para inicializacion con 4 pines esta conectado al pin 27 ->PIO_14


#define LCD_LINE_LENGHT 80
#define LCD_LINE_VISIBLE 16

//++++  Display COMMANDS and INSTRUCTIONS (see tab. 6 HD44780 AppNote)  +++++++++++++++++++++++
#define DISPLAY_CLEAR				0x001000 //	Clears display and set DDRAM address 0
#define RETURN_HOME					0x02 //	DDRAM address 0, cursor origin position

#define ENTRY_MODE_DEC_NO_SHIFT		0x04 //00000100: Entry mode decrement, no display shift
#define ENTRY_MODE_DEC_SHIFT		0x05 //00000101: Entry mode decrement, display shift
#define ENTRY_MODE_INC_NO_SHIFT		0x0060000 //00000110: Entry mode increment, no display shift
#define ENTRY_MODE_INC_SHIFT		0x07 //00000111: Entry mode increment, display shift

#define DISP_OFF_CUR_OFF_BLINK_OFF	0x008000 //00001000: Display off, cursor off, blinking off
#define DISP_OFF_CUR_OFF_BLINK_ON	0x09 //00001001: Display off, cursor off, blinking on
#define DISP_OFF_CUR_ON_BLINK_OFF	0x0A //00001010: Display off, cursor on, blinking off
#define DISP_OFF_CUR_ON_BLINK_ON	0x0B //00001011: Display off, cursor on, blinking on
#define DISP_ON_CUR_OFF_BLINK_OFF	0x0C //00001100: Display on, cursor off, blinking off
#define DISP_ON_CUR_OFF_BLINK_ON	0x0D //00001101: Display on, cursor off, blinking on
#define DISP_ON_CUR_ON_BLINK_OFF	0x0E //00001110: Display on, cursor on, blinking off
#define DISP_ON_CUR_ON_BLINK_ON		0x00F0000 //00001111: Display on, cursor on, blinking on
	
#define CURSOR_MOVE_SHIFT_LEFT		0x10 //00010000: Cursor move, shift to the left
#define CURSOR_MOVE_SHIFT_RIGHT		0x14 //00010100: Cursor move, shift to the right
#define DISPLAY_MOVE_SHIFT_LEFT		0x18 //00011000: Display move, shift to the left
#define DISPLAY_MOVE_SHIFT_RIGHT	0x1C //00011100: Display move, shift to the right

#define FOUR_BIT_ONE_LINE_5x8		0x20 //00100000: 4 bit, 1 line, 5x8 font size
#define FOUR_BIT_ONE_LINE_5x10		0x24 //00101000: 4 bit, 1 line, 5x10 font size
#define FOUR_BIT_TWO_LINE_5x8		0x28 //00101000: 4 bit, 2 line, 5x8 font size
#define FOUR_BIT_TWO_LINE_5x10		0x2C //00101100: 4 bit, 2 line, 5x10 font size
#define EIGHT_BIT_ONE_LINE_5x8		0x30 //00110000: 8 bit, 1 line, 5x8 font size
#define EIGHT_BIT_ONE_LINE_5x10		0x34 //00110100: 8 bit, 1 line, 5x10 font size
#define EIGHT_BIT_TWO_LINE_5x8		0x38 //00111000: 8 bit, 2 line, 5x8 font size
#define EIGHT_BIT_TWO_LINE_5x10		0x3C //00111100: 8 bit, 2 line, 5x10 font size
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define CGRAM_ADDRESS(addr)		(addr = addr|0x40)		 // CGRAM addressing
#define E_SET_CGRAM_ADDR        0x0040000

#define LINE1_HOME		0x0080		 // DDRAM addressing
#define LINE2_HOME		0xC0		 // DDRAM addressing

//++++  Functions  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define NUM_TO_CODE(num)		(num+0x30)			 // 0-9 ROM codes
#define CODE_TO_NUM(code)		(code-0x30)          // 0-9 ROM num

void WriteByte(unsigned char rs, int data_to_LCD);


void lcd16x2Init(uint16_t ancholinea, uint16_t cantidadlineas,uint16_t anchocaracter,uint16_t alturacaracter);
//Inicializacion con 4 bits

void lcd16x2Init4b(uint16_t ancholinea,uint16_t cantidadlineas,uint16_t anchocaracter,uint16_t alturacaracter);

//Escribe un nivel alto o bajo en el Pin del micro
void lcd16x2PinSet( gpio_portpin_en pin,gpio_nivel_logico status);

//Habilita el Pin EN y lo desabilita
void lcd16x2EnablePulse( void );


void lcd16X2Command( uint32_t cmd );
void lcd16X2Clear( void );
void lcd16x2Data( uint32_t data );
void lcd16x2SendStringRaw( char* str );
void lcd16x2GoToXY(uint8_t x,uint8_t y);
void lcd16x2SendEnter(void);
void lcd16x2SendChar( char character );
void lcd16x2SendString( char* str );

void lcd16x2CreateChar( uint8_t charnum, const char* chardata );



//void InitLCD_8b_2L(void); // Use only with 5V separate supply or Charge Pump
void WriteAscii(unsigned char symbol);
void PutCommand(int Command);
void GoToLine(unsigned char line);
void DisplayLeft(unsigned char nplaces);
void DisplayRight(unsigned char nplaces);

void WriteInitial(unsigned char LineOfCharacters[LCD_LINE_VISIBLE]);
void WriteAfter(unsigned char LineOfCharacters[LCD_LINE_LENGHT]);
void WriteAll(unsigned char lineOfCharacters[LCD_LINE_LENGHT]);
void Write_ndigitsval(unsigned int dummyVal, unsigned char ndigits);
void Write_ndigitsval_space(unsigned int dummyVal, unsigned char ndigits);
void Write_2digitsval(unsigned int dummyVal);
void Write_HDval(unsigned int dummyVal);
void Write_HDval2(unsigned int dummyVal);

/* END HD44780 */
#endif /* __HD44780_H*/
