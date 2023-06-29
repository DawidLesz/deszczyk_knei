#include <avr/io.h>
#include <util/delay.h>

#define DECODE_MODE			0x09
#define INTENSITY			0x0A
#define SCAN_LIMIT			0x0B
#define SHUTDOWN			0x0C
#define SHUTDOWN_SHUTDOWN_MODE			0
#define SHUTDOWN_NORMAL_OPERATION		1
#define DISPLAY_TEST		0x0F
#define DISPLAY_TEST_NORMAL_OPERATION	0
#define DISPLAY_TEST_DISPLAY_TEST_MODE	1

char bols[] = {0b11111111,0b10000001,0b10000001,0b10000001,0b10000001,0b10000001,0b10000001,0b11111111};

void wyslij(char address, char data);

void display_ini(){
	DDRB	|= (1<<PB2);		//SS na wyjscie
	PORTB	|= (1<<PB2);		//CS
	
	DDRB	|= (1<<PB3);		//MOSI na wyjœcie
	DDRB	&=~ (1<<PB4);		//MISO na wejscie
	DDRB	|= (1<<PB5);		//SCK na wyjscie
	SPCR |= (1<<MSTR); //MASTER SPI
	//SPCR |= (1<<SPR1); //Divider /128
	//SPCR |= (1<<SPR0);
	SPSR	|= (1<<SPI2X);
	SPCR |= (1<<SPE);			//SPI enable
	
	_delay_ms(100);
	wyslij(SHUTDOWN, SHUTDOWN_NORMAL_OPERATION);
	wyslij(DECODE_MODE, 0x00);
	wyslij(INTENSITY, 0x0F);
	wyslij(SCAN_LIMIT, 0x0F);
	wyslij(DISPLAY_TEST, DISPLAY_TEST_NORMAL_OPERATION);
}

void zerowanie(){
	for(int i = 1; i<=8; i++){
		wyslij(0x00+i, 0x00);
	}
}

void ramka(){
	wyslij(0x01, 0b11111111);
	wyslij(0x08, 0b11111111);
	
	for(int i=2; i<=7; i++){
		wyslij(0x00+i, 0b10000001);
	}
}


void wyslij_bols()
{	
	for(int i = 0; i <=7; i++)	wyslij(i+1, bols[i]);
}
		



void wyslij(char address, char data){
	
	PORTB	&=~ (1<<PB2);		//CS
	SPDR	= address;
	while(!(SPSR & (1<<SPIF)));	//czekaj na zakonczenie wysylania
	SPDR	= data;
	while(!(SPSR & (1<<SPIF)));	//czekaj na zakonczenie wysylania
	PORTB	|= (1<<PB2);		//CS

}

