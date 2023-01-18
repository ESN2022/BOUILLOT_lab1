#include<system.h>
#include<altera_avalon_pio_regs.h>
#include <stdio.h>
#include <sys/alt_irq.h>

int i=0, time=10000, sw, start;

/*Définition de la routine d'interruption*/

static void switch_interrupts ()
{
	sw = IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
	switch (sw)
		{
		case 0 :
			time = 10000;
			break;
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
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0xf);
}

static void button_interrupts()
{
	sw = 0;
	
	if (IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE) == 0x0)
	{
		i=0;
		for (i=0;i<7;i++){
				IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,1<<i);
				usleep(time);
			}
			for (i=7;i>=0;i--){
				IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,1<<i);
				usleep(time);
			}
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x0);
	}
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x1);
}


int main ()
{
	
	/* Les 4 switchs vont pouvoir générer l'interruption */
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0xf);

	/*Initialisation du registre edge capture*/
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0xf);
	
	/* Definition du registre d'interruption */
	alt_ic_isr_register(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ,(void*) switch_interrupts,NULL, 0x0);
	
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x1);
	alt_ic_isr_register(PIO_2_IRQ_INTERRUPT_CONTROLLER_ID,PIO_2_IRQ,(void*) button_interrupts,NULL, 0x0);
	alt_printf("hello");
	
	while(1){}

	return 0;
	
}

