/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"

#define LED_IO_MUX     PERIPHS_IO_MUX_GPIO2_U
#define LED_IO_NUM     2
#define LEDIO_FUNC     FUNC_GPIO2

static os_timer_t gpio_sw_timer;

void ICACHE_FLASH_ATTR gpio_sw_timer_cb(void *arg)
{
	static uint8 sw;

	GPIO_OUTPUT_SET( LED_IO_NUM, sw );

	sw ^= 1;
}

/**
 * @brief Initializes the user application and sets up a timer to blink the LED.
 *
 */
void ICACHE_FLASH_ATTR user_init(void)
{
	PIN_FUNC_SELECT( LED_IO_MUX, LEDIO_FUNC );
	gpio_output_set( 0, LED_IO_NUM, LED_IO_NUM, 0 );

    os_timer_disarm( &gpio_sw_timer );
	os_timer_setfn( &gpio_sw_timer, gpio_sw_timer_cb, NULL );
	os_timer_arm( &gpio_sw_timer, 500, 1 );
}

