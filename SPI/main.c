/*
 * SPI.c
 *
 * Created: 01.06.2023 14:46:20
 * Author : Komputer_4
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "displaySquare.h"

char holder;

char dp[] = {0, 0, 0, 0,  0b01100111,  0b00001110, 0b01001111, 0b00110111};
	



int main(void)
{
	display_ini();
	zerowanie();
// 	_delay_ms(5000);
// 	ramka();
// 	_delay_ms(1000);
// 	zerowanie();







	
	
    /* Replace with your application code */
    while (1) 
    {	
		for(int w = 6; w>0; w--)
		{
			
			for(int k = 1; k<=6; k++)
			{
				for(int i =1; i<=6; i++)
				{
					bols[i] |= (1<<k);
					wyslij_bols();
				
					_delay_ms(30);
					if(i<w) bols[i] &=~(1<<k);
					wyslij_bols();
				}
				/*bols[7-k] = 0b11111111;*/
			}
		}
		
		
// 		for(int i=0; i<8; i++) 	wyslij(0x01+i, dp[i]);
// 		
// 		char tmp = dp[0];		
// 		for (int i=1; i<8; i++)		dp[i-1] = dp[i];
// 		dp[7] = tmp;
// 		
// 		_delay_ms(200);
		
// 		wyslij(0x08, 0xFF);
// 		
// 		_delay_ms(1000);
// 		wyslij(0x08, 0x00);
		/*
		int numerek = 0b00000001;
		
		for (int i = 1; i <= 8; i++)
		{
			wyslij(numerek);
			_delay_ms(100);
			numerek	|=(numerek<<1);
		}

		for (int i = 0; i <= 7; i++)
		{
			wyslij(numerek);
			_delay_ms(100);
			numerek	=(numerek<<1);
			
		}	
		*/

    }
}

