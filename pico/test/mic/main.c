#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#define DEV_LED_PIN     (25)

#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)

int main() {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false); // disable windows bullshit
    sleep_ms(1000);

    adc_init();
    adc_gpio_init( ADC_PIN);
    adc_select_input( ADC_NUM);

    int adc_raw;
    int idx=0;
    while (true)
    {
        gpio_put(DEV_LED_PIN, (idx&1) ? 1 : 0); // flash led/screen
        idx++;

        adc_raw = adc_read(); // raw voltage from ADC
        printf("%03x : %*s\n", adc_raw  , adc_raw>>5 , "*");
        sleep_ms(1);
    }
}

