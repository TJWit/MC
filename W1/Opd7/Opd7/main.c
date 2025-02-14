/*
 * Opd7.c
 *
 * Created: 9-2-2024 13:31:47
 * Author : Kersjan14
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

enum states {
	Start,
	S1,
	S2,
	S3,
	End
};


int main(void)
{
	DDRE = 0x1F;
	enum states state = Start;
	
	
    while (1) 
    {
		wait(1000);
		
		switch (state)
		{
			case Start:
				PORTE = 0x01;
				switch (PIND)
				{
					case 1<<5:
						state = S2;
						break;
					case 1<<6:
						state = S1;
						break;
				}
				break;
			case S1:
				PORTE = 0x02;
				switch (PIND)
				{
					case 1<<5:
					state = S2;
					break;
					case 1<<7:
					state = Start;
					break;
				}
				break;
			case S2:
				PORTE = 0x04;
				switch (PIND)
				{
					case 1<<5:
						state = S3;
						break;
					case 1<<6:
						state = S1;
						break;
					case 1<<7:
						state = Start;
						break;
				}
				break;
			case S3:
				PORTE = 0x08;
				switch (PIND)
				{
					case 1<<5:
						state = End;
						break;
					case 1<<6:
						state = End;
						break;
					case 1<<7:
						state = Start;
						break;
				}
				break;
			case End:
				PORTE = 0x10;
				switch (PIND)
				{
					case 1<<7:
						state = Start;
						break;
				}
				break;
		}
		
    }
}

