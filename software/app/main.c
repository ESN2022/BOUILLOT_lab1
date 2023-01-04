#include<system.h>
#include<altera_avalon_pio_regs.h>
#include <stdio.h>

int i=0, time=0, sw=0;

int main ()
{
	//IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	while(1){
		switch sw{
		case 0 :
			time = 100000;
			break;
		case 1 :
			time = 75000;
			break;
		case 2 :
			time = 50000;
			break;
		case 3 :
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