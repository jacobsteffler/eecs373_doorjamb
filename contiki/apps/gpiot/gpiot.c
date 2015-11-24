#include "contiki.h"
#include "dev/gpio.h"
#include "sys/etimer.h"

static int x = 0;
/* static struct etimer periodic; */

void gp_int(uint8_t port, uint8_t pin) {
	if(x) {
		x = 0;
		GPIO_SET_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
	} else {
		x = 1;
		GPIO_CLR_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
	}
}

/*---------------------------------------------------------------------------*/
PROCESS(gpiot_process, "GPIO_Test");
AUTOSTART_PROCESSES(&gpiot_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(gpiot_process, ev, data) {
	PROCESS_BEGIN();

	GPIO_SET_INPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));

	GPIO_ENABLE_INTERRUPT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_TRIGGER_BOTH_EDGES(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));

	GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));

	gpio_register_callback(gp_int, GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));

	while(1) {
		PROCESS_YIELD();
	}

	PROCESS_END();
}
