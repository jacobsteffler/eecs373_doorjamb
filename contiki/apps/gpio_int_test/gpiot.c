#include "contiki.h"
#include "dev/gpio.c"
#include "dev/nvic.h"
#include "dev/ioc.h"
#include "dev/leds.h"
#include "sys/timer.h"
#include "sys/etimer.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* static struct etimer periodic; */
static struct etimer periodic_timer_gpio;

void gp_int() {
	etimer_set(&periodic_timer_gpio, CLOCK_SECOND/10);
	unsigned int i;
	for(i = 0;i<100000000;i++)
	leds_toggle(LEDS_BLUE);
	printf("@@@@@@@@@@@@@@\n");
	etimer_restart(&periodic_timer_gpio);
}

/*---------------------------------------------------------------------------*/
PROCESS(gpiot_process, "GPIO_Test");
AUTOSTART_PROCESSES(&gpiot_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(gpiot_process, ev, data) {
	PROCESS_BEGIN();
	etimer_set(&periodic_timer_gpio, CLOCK_SECOND/10);
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_SET_INPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));//input: pin: C0
	GPIO_DETECT_EDGE(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_TRIGGER_SINGLE_EDGE(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_DETECT_RISING(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_ENABLE_INTERRUPT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	ioc_set_over(GPIO_C_NUM, 0, IOC_OVERRIDE_PUE);
	nvic_interrupt_enable(NVIC_INT_GPIO_PORT_C);
	gpio_register_callback(gp_int,GPIO_C_NUM, 0);
	while(1) {
		PROCESS_YIELD();
		leds_toggle(LEDS_RED);
		etimer_restart(&periodic_timer_gpio);
	}
	PROCESS_END();
}
