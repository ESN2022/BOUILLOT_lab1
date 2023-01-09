#include<system.h>
#include<altera_avalon_pio_regs.h>
#include <stdio.h>

int i=0, time=0, sw;

int main ()
{
	//IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	while(1){
		sw = IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
		switch (sw)
		{
		case 1 :
			time = 100000;
			break;
		case 2 :
			time = 75000;
			break;
		case 4 :
			time = 50000;
			break;
		case 8 :
			time = 25000;
			break;
		}
		for (i=0;i<7;i++){
			   IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,1<<i);
			   usleep(time);
		}
		
		for (i=7;i>0;i--){
			   IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,1<<i);
			   usleep(time);
			}
	}
	return 0;
}