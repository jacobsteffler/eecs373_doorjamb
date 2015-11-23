#include "contiki.h"
#include "dev/gpio.h"
#include "sys/etimer.h"

static int x = 0;
static struct etimer periodic;

/*---------------------------------------------------------------------------*/
PROCESS(gpiot_process, "GPIO_Test");
AUTOSTART_PROCESSES(&gpiot_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(gpiot_process, ev, data) {
	PROCESS_BEGIN();

	etimer_set(&periodic, CLOCK_SECOND);

	GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));

	while(1) {
		PROCESS_YIELD();

		if(etimer_expired(&periodic)) {
			if(x) {
				x = 0;
				GPIO_SET_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
			} else {
				x = 1;
				GPIO_CLR_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
			}

			etimer_restart(&periodic);
		}
	}

	PROCESS_END();
}
