#include "contiki.h"
#include "spi-arch.h"
#include "spi.h"
#include "dev/ssi.h"
#include "sys/etimer.h"

#include "rv3049.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(spi_test_process, "SPI_Test");
AUTOSTART_PROCESSES(&spi_test_process);
static struct etimer periodic_timer_spi;
rv3049_time_t rtctime;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(spi_test_process, ev, data) {
	PROCESS_BEGIN();
	etimer_set(&periodic_timer_spi, CLOCK_SECOND/1000);
	spix_cs_init(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));//select: pin: B3
	SPI_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
	//spi_init();
  	spix_set_mode(SPI_CONF_DEFAULT_INSTANCE, SSI_CR0_FRF_MOTOROLA, 1, SSI_CR0_SPH, 8);
  	SPI_CS_SET(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
	//SPIX_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
	while(1){
		PROCESS_YIELD();
		if (etimer_expired(&periodic_timer_spi)) {
			unsigned int i;
			printf("!!!!!!!!!!!!!!!!!!!!!!!\n");
			SPI_WRITE(0xF0);
			SPI_FLUSH();
			SPI_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
			SPI_CS_SET(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
			etimer_restart(&periodic_timer_spi);
		}
	}
	//etimer_set(&periodic_timer_rtc, CLOCK_SECOND*5);
	
	//while(1) {
	//	if (etimer_expired(&periodic_timer_rtc)) {
	//		rv3049_read_time(&rtctime);
	//		printf("%d:%d:%d\n",rtctime.hours,rtctime.minutes,rtctime.seconds);
	//		etimer_restart(&periodic_timer_rtc);
		
			/*Read*/
			//spix_set_mode(GPIO_PORT_TO_BASE(0), SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 16);
			//SPIX_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));
			/* Send the READ command and the address to the FRAM */
		  	//SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(current_address, FM25L04B_READ_COMMAND));//??
		  	//SPI_WRITE(current_address & 0xFF);//??
			//SPI_FLUSH();
			//SPI_READ();
			//SPIX_CS_SET(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(3));

			/*Write*/
	//		spix_set_mode(GPIO_PORT_TO_BASE(0), SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 16);
	//		SPIX_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(4));
			/* Send the WRITE ENABLE command to allow writing to the FRAM */
			//SPI_WRITE(FM25L04B_WRITE_ENABLE_COMMAND);
			//SPIX_CS_SET(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(4));
  			//SPIX_CS_CLR(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(4));
			/* Send the WRITE command and the address to the FRAM */
  			//SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(address, FM25L04B_WRITE_COMMAND));
  			//SPI_WRITE(address & 0xFF);
			/* Send the data to write */
	//		SPI_WRITE(0xF0F0);
	//		SPI_FLUSH();
			//SPI_WRITE(rtctime.year);//2015 = 0x07DF = 0000 0111 1101 1111
	//		SPIX_CS_SET(GPIO_PORT_TO_BASE(GPIO_B_NUM), GPIO_PIN_MASK(4));
	//	}
	//}
	PROCESS_END();
}
