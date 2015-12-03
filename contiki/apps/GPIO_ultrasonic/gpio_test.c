#include "contiki.h"
#include "sys/etimer.h"
#include <stdio.h>
#include "dev/leds.h"
#include "dev/ioc.h"
#include "dev/nvic.h"
#include "dev/gpio.h"
#include "sys/clock.h"
#include "rv3049.h"
#include "dev/gptimer.h"
#include "dev/smwdthrosc.h"

PROCESS(gpio_process, "gpio_process");
AUTOSTART_PROCESSES(&gpio_process);

inline uint32_t vtimer_arch_now() {
  uint32_t rv;

  /* SMWDTHROSC_ST0 latches ST[1:3] and must be read first */
  rv = REG(SMWDTHROSC_ST0);
  rv |= (REG(SMWDTHROSC_ST1) << 8);
  rv |= (REG(SMWDTHROSC_ST2) << 16);
  rv |= (REG(SMWDTHROSC_ST3) << 24);

  return rv;
}
static uint32_t start_time;

int raiseHigh = 1;
static struct etimer gpioOut;

void cb(uint8_t port, uint8_t pin){

	GPIO_CLEAR_INTERRUPT(GPIO_PORT_TO_BASE(port), GPIO_PIN_MASK(pin));
	if(port==2 && pin==0){
		start_time = vtimer_arch_now();
	}
	else{
		printf("time = %lu\n", vtimer_arch_now()-start_time);
	}
}

//Use C0 to receive interrupt
void configGPIOInterrupt(){
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_SET_INPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_DETECT_EDGE(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_DETECT_RISING(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));
	GPIO_ENABLE_INTERRUPT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(0));

	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(2));
	GPIO_SET_INPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(2));
	GPIO_DETECT_EDGE(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(2));
	GPIO_DETECT_FALLING(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(2));
	GPIO_ENABLE_INTERRUPT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(2));

	ioc_set_over(GPIO_C_NUM,0, IOC_OVERRIDE_PUE);
	ioc_set_over(GPIO_C_NUM,2, IOC_OVERRIDE_PUE);
	nvic_interrupt_enable(NVIC_INT_GPIO_PORT_C);
	gpio_register_callback(cb,GPIO_C_NUM,0);
	gpio_register_callback(cb,GPIO_C_NUM,2);
}

void configGPIOOuput(){
	GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
	GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));

}

PROCESS_THREAD(gpio_process, ev, data)
{

  PROCESS_BEGIN();
  leds_toggle(LEDS_RED);
  configGPIOInterrupt();
 // configGPIOOuput();

 // etimer_set(&gpioOut, CLOCK_SECOND);

  while(1) {

  	 PROCESS_YIELD();
  // 	 if (etimer_expired(&gpioOut)) {

  // 	 	if(raiseHigh){
  // 	 		GPIO_SET_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
  // 	 		raiseHigh = 0;
  // 	 	}
  // 	 	else{
  // 	 		 GPIO_CLR_PIN(GPIO_PORT_TO_BASE(GPIO_C_NUM), GPIO_PIN_MASK(1));
  // 	 		 raiseHigh = 1;
  // 	 	}
		// 	etimer_restart(&gpioOut);
		// }

  }

  PROCESS_END();
}

