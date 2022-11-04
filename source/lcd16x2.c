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

#include <lcd16x2.h>

unsigned char BitNum;
/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
typedef struct {
	uint16_t ancholinea;
	uint16_t cantidadlineas;
	uint16_t anchocaracter;
	uint16_t alturacaracter;
	uint8_t x;
	uint8_t y;
} lcd_t;

/*==================[definiciones de datos externos]=========================*/

static lcd_t lcd;



/*****************************************************************
 *****  LCD initialization routine  (4 bit/8bit interface defined)  ****
 *****************************************************************/

void lcd16x2Init(uint16_t ancholinea,uint16_t cantidadlineas,
		uint16_t anchocaracter,uint16_t alturacaracter)
{
	lcd.ancholinea=ancholinea;
	lcd.cantidadlineas=cantidadlineas;
	lcd.anchocaracter=anchocaracter;
	lcd.alturacaracter=alturacaracter;
	lcd.x=0;
	lcd.y=0;


	// Configure LCD for 8-bit mode
	lcd16x2PinSet( GPIO_PORTPIN_0_27, GPIO_Nivel_bajo);     // RW = 0
	lcd16x2PinSet(  GPIO_PORTPIN_0_26,GPIO_Nivel_bajo);     // RS = 0
	lcd16x2PinSet( GPIO_PORTPIN_0_28, GPIO_Nivel_bajo);     // EN = 0

	lcd16X2Command(D5|D4 );
	delayMs(25);                    // Wait

	lcd16X2Command(D5|D4 );
	delayMs(25);                   // Wait

	lcd16X2Command(D5|D4 );
	delayMs(25);

	// Initialize LCD
	//Se informa el tipo de interfaz que se va a usar, 4 o 8 bits(D4=1 8bits). La
	//cantidad de líneas (D3=1 2 lineas). La fuente de caracter 5x8 dots o 5x10 (D2=1)dots.
	lcd16X2Command( D5|D4|D3|D2);                 // Command 0x0E for display on, cursor on
	delayMs(25);

	lcd16X2Clear();                                // Command for clear LCD

	//Configura el estado ON/OFF del display (D2=1 enciende display), el estado del cursor (D1 =1 avtiva cursor)
	//el parpadeo del caracter en la posición del cursor(D0=1 parpadea caracter).
	lcd16X2Command(D3|D2|D1|D0);                   // Command 0x06 for Shift cursor right
	delayMs(10);                                   // Wait

	delayMs(10);
}


void lcd16x2PinSet( gpio_portpin_en pin,gpio_nivel_logico status){

	gpioOutputWrite(GPIO ,GPIO_PORT_0,pin,status);

}

void lcd16x2EnablePulse( void ){

	lcd16x2PinSet( GPIO_PORTPIN_0_28,GPIO_Nivel_alto);       // EN = 1 for H-to-L pulse
	delayMs(1);   // Wait to make EN wider //lcdDelay_us(1);
	lcd16x2PinSet( GPIO_PORTPIN_0_28, GPIO_Nivel_bajo);      // EN = 0 for H-to-L pulse
	delayMs(1);
}

void lcd16X2Command( uint32_t cmd ){

	gpioMultOutputOff(GPIO,GPIO_PORT_0,OFFD0D7);
	delayMs(1);       // Wait
	gpioMultOutputOn(GPIO,GPIO_PORT_0,cmd);
	lcd16x2PinSet( GPIO_PORTPIN_0_26, GPIO_Nivel_bajo );   // RS = 0 for command
	lcd16x2PinSet(  GPIO_PORTPIN_0_27,GPIO_Nivel_bajo );   // RW = 0 for write
	lcd16x2EnablePulse();
	delayMs(1);       // Wait
	//lcd16x2EnablePulse();
	gpioMultOutputOff(GPIO,GPIO_PORT_0,OFFD0D7);

}

void lcd16x2Data( uint32_t data ){

	data=data<<16;                   //Es porque quiero manejar desde el pin 16 (D0)  al pin 23 (D7)
	lcd16x2PinSet( GPIO_PORTPIN_0_26, GPIO_Nivel_alto );   // RS = 1 for command
	lcd16x2PinSet(  GPIO_PORTPIN_0_27,GPIO_Nivel_bajo );   // RW = 0 for write
	gpioMultOutputOff(GPIO,GPIO_PORT_0,OFFD0D7);
	delayMs(1);       // Wait
	gpioMultOutputOn(GPIO,GPIO_PORT_0,data);

	lcd16x2EnablePulse();
	delayMs(1);       // Wait

}

// FUNCION MANDA TODO EL TEXTO no controa el final del display
void lcd16x2SendStringRaw( char* str ){
	uint8_t i = 0;
	while( str[i] != 0 ) {
		lcd16x2Data( str[i] );
		i++;
	}
}

void lcd16X2Clear( void ){
	lcd16X2Command( CLEAR );                   // Command 0x01 for clear LCD
	delayMs(5);                               // Wait
}

void lcd16x2GoToXY(uint8_t x,uint8_t y){

   if( x >= lcd.ancholinea || y >= lcd.cantidadlineas ) {
      return;
   }
   uint32_t firstCharAdress[] = { 0x800000, 0xC00000, 0x940000, 0xD40000 };   // See table 12-5
   //lcdCommand( firstCharAdress[ y - 1 ] + x - 1 );         // Start in {x,y} = {1,1}
   lcd16X2Command( firstCharAdress[y] + x );                 // Start in {x,y} = {0,0}
   delayMs(1);      // Wait
   lcd.x = x;
   lcd.y = y;
}

void lcd16x2SendEnter(void)
{
   // Si llego abajo no hace nada
   if( lcd.y >= lcd.cantidadlineas ) {
      return;
   } else {
      lcd.x = 0;
      lcd.y++;
      lcd16x2GoToXY( lcd.x, lcd.y );
   }
}

void lcd16x2SendChar( char character )
{

   if( character == '\r' ) {        // Ignore '\r'
   } else if( character == '\n' ) { // Mando enter
      lcd16x2SendEnter();
   } else {
      // Si se extiende en ancho mando enter
      if( lcd.x >= lcd.ancholinea ) {
         lcd16x2SendEnter();
         lcd.x=0;
      }
      // Mando el caracter
      lcd16x2Data( character );
      lcd.x++;
   }
}


void lcd16x2SendString( char* str )
{
   uint32_t i = 0;
   lcd.y=0;
   lcd.x=0;
   while( str[i] != 0 ) {
      lcd16x2SendChar( str[i] );
      i++;
   }
}


/**************************************
 *****    Send a command to LCD     ****
 ***************************************/
void PutCommand(int Command)
{


}

/**************************************************
 *****    Write a string on LCD visible part    ****
 ***************************************************/
void WriteInitial(unsigned char LineOfCharacters[LCD_LINE_VISIBLE])
{

}

/**************************************************
 *****    Write a string on LCD total line      ****
 ***************************************************/
void WriteAll(unsigned char lineOfCharacters[LCD_LINE_LENGHT])
{/*
	unsigned char i=0;

	PutCommand(LINE1_HOME); // Ci riporta a scrivere all'inizio della memoria del Display
	DelayUs(100);
	while(lineOfCharacters[i] && i<LCD_LINE_LENGHT)
	{
		WriteAscii(lineOfCharacters[i]);
		i++;
	}*/
}

/**************************************
 *****   Write a character on LCD   ****
 ***************************************/
void WriteAscii(unsigned char symbol)
{


}


/**************************************
 *****     Write a byte on LCD      ****
 ***************************************/
void WriteByte(unsigned char rs, int data_to_LCD)
{

}


/*************************************************************
 *****    Write in line after current position on LCD     ****
 **************************************************************/
void WriteAfter(unsigned char LineOfCharacters[LCD_LINE_LENGHT])
{/*
	unsigned char i=0;

	while(LineOfCharacters[i] && i<LCD_LINE_LENGHT)
	{
		WriteAscii(LineOfCharacters[i]);
		i++;
	}*/
}


/**************************************
 *****     Write 2 digit on LCD     ****
 ***************************************/
void Write_2digitsval(unsigned int dummyVal)
{/*
	WriteAscii(NUM_TO_CODE(dummyVal/10));
	dummyVal %= 10;
	WriteAscii(NUM_TO_CODE(dummyVal));*/
}

/**************************************
 *****     Write n digit on LCD     ****
 ***************************************/
void Write_ndigitsval_space(unsigned int dummyVal, unsigned char ndigits)
{/*
	int ten_base=1, digit, leading_zeroes_flag = 1;

	while(--ndigits)
		ten_base*=10;

	while(ten_base)
	{
		digit = dummyVal/ten_base;
		if(digit)
			leading_zeroes_flag = 0;
		WriteAscii(leading_zeroes_flag&&(ten_base>1)? ' ': NUM_TO_CODE(digit));
		dummyVal %= ten_base;
		ten_base/=10;
	}*/
}

void Write_ndigitsval(unsigned int dummyVal, unsigned char ndigits)
{/*
	unsigned char digit,i;
	unsigned int TestVal=1;

	for (i=1;i<ndigits;i++)
			{TestVal*=10;}

	while(dummyVal<TestVal){TestVal/=10; ndigits--;}

	for (i=1;i<ndigits;i++)
		{PutCommand(CURSOR_MOVE_SHIFT_RIGHT);}

	PutCommand(ENTRY_MODE_DEC_NO_SHIFT);

	while(dummyVal)
	{
		digit = dummyVal%10;
		dummyVal /=10;
		WriteAscii(NUM_TO_CODE(digit));
	}

	PutCommand(ENTRY_MODE_INC_NO_SHIFT);

	for (i=0;i<(ndigits+1);i++)
			{PutCommand(CURSOR_MOVE_SHIFT_RIGHT);}
 */
}

/************************************************
 *****     Write HexaDecimal digit on LCD     ****
 ************************************************/
void Write_HDval(unsigned int dummyVal)
{/*
	unsigned char HDchar[4] = {0, 0, 0, 0};; // 4 è il massimo di byte che ci servono per
	// una variabile a 32 bit
	unsigned char i=4, p1=0;
	unsigned char Nibbolo; //:-)

	WriteAfter((uint8_t*) "0x");

	while (i)
			{HDchar[i-1]= (dummyVal%16 & 0x0F); // spostiamo nel Nibble Alto
			dummyVal/=16;
			HDchar[i-1] = (HDchar[i-1]) << 4;
			HDchar[i-1] |= (dummyVal%16);
			dummyVal/=16;
			i--;}

	while (4-i)
			{
			Nibbolo = HDchar[i] & 0x0F;
			if(Nibbolo<10) {if(Nibbolo>0) p1=1; if(p1) {WriteAscii(NUM_TO_CODE(Nibbolo)); } }
			else WriteAscii(0x37 + Nibbolo);
			Nibbolo = HDchar[i] & 0xF0;
			Nibbolo = Nibbolo >> 4;
			if(Nibbolo<10) {if(Nibbolo>0) p1=1; if(p1) {WriteAscii(NUM_TO_CODE(Nibbolo)); }  }
			else WriteAscii(0x37 + Nibbolo);
			i++;
			}*/
}


void Write_HDval2(unsigned int dummyVal)
{/*
	unsigned int TestVal = 0xFFFFFFF; // 7 nibble è la prima condizione per diminuire le cifre da scrivere
	unsigned char i=0, n_N=8;
	unsigned char Nibbolo; //:-)

	WriteAfter((uint8_t*) "0x");

	while (dummyVal < TestVal) {
	TestVal /= 16;
	n_N--; }

	for (i=1;i<n_N;i++)	{PutCommand(CURSOR_MOVE_SHIFT_RIGHT);}

	PutCommand(ENTRY_MODE_DEC_NO_SHIFT);

	while(dummyVal)
	{
		Nibbolo = dummyVal % 16;
		dummyVal /= 16;
		if(Nibbolo<10) WriteAscii(NUM_TO_CODE(Nibbolo));
		else WriteAscii(0x37 + Nibbolo);
	}

	PutCommand(ENTRY_MODE_INC_NO_SHIFT);

	for (i=0;i<(n_N+1);i++)
			{PutCommand(CURSOR_MOVE_SHIFT_RIGHT);}*/
}

/****************************************************
 *****     Shows the right side of RAM characters ****
 *****************************************************/

void DisplayLeft(unsigned char nplaces)
{/*
	uint8_t i=0;

	delayMs(1);
	while(i<nplaces)
		{
		lcd16X2Command(DISPLAY_MOVE_SHIFT_LEFT);		// Mostra altri caratteri
		i++;
		}*/
}

/****************************************************
 *****     Shows the left side of RAM characters ****
 *****************************************************/

void DisplayRight(unsigned char nplaces)
{/*
	uint8_t i=0;

	DelayMs(1);
	while(i<nplaces)
		{
		PutCommand(DISPLAY_MOVE_SHIFT_RIGHT);		// Mostra altri caratteri
		i++;
		}*/
}

/*==================[fin del archivo]========================================*/
// EOF
