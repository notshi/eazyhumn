#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"


#define I2C_PORT i2c1
#define DEV_SDA_PIN     (6)
#define DEV_SCL_PIN     (7)
#define DEV_LED_PIN     (25)

bool reserved_addr(uint8_t addr) {
  return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void i2c_scan(){
  printf("\nI2C Bus Scan \n");
	printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
	for (int addr = 0; addr < (1 << 7); ++addr) {
			if (addr % 16 == 0) {					printf("%02x ", addr);			}
			int ret;
			uint8_t rxdata;
			if (reserved_addr(addr))
					ret = PICO_ERROR_GENERIC;
			else
					ret = i2c_read_blocking(I2C_PORT, addr, &rxdata, 1, false);

			printf(ret < 0 ? "." : "@");
			printf(addr % 16 == 15 ? "\n" : "  ");
	}
}


int main() {
    stdio_init_all();
    sleep_ms(1000);

    gpio_init(DEV_LED_PIN);
    gpio_set_dir(DEV_LED_PIN, GPIO_OUT);

    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(DEV_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(DEV_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(DEV_SDA_PIN);
    gpio_pull_up(DEV_SCL_PIN);
    bi_decl(bi_2pins_with_func(DEV_SDA_PIN, DEV_SCL_PIN, GPIO_FUNC_I2C));
    i2c_scan();
    int idx=0;
    while (true)
    {
        gpio_put(DEV_LED_PIN, (idx&1) ? 1 : 0); // flash led/screen
        idx++;
        printf("%d Hello again, old world!\n",idx);
        sleep_ms(1000);
    }
}

