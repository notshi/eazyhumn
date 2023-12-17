#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"


#define I2C_PORT i2c1
#define DEV_SDA_PIN     (6)
#define DEV_SCL_PIN     (7)
#define DEV_LED_PIN     (25)

void i2c_scan(){
  printf("\nI2C Bus Scan : ");
	for( int addr = 0x08 ; addr < 0x78 ; ++addr )
    {
        int ret=-1;
        uint8_t rxdata[4];
        if(! ( addr>=0x40 && addr<=0x41 ) ) // this device bulshit
        {
            ret = i2c_read_blocking(I2C_PORT, addr, rxdata, 1, false);
        }
        if(ret<0)
        {
            printf(".");
        }
        else
        {
            printf(".%02X" , addr);
        }
	}
  printf("\n");
}


int main() {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false); // disable windows bullshit
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

        uint8_t rxdata[4];
        rxdata[0]=0x00;
        i2c_write_blocking(I2C_PORT, 0x41, rxdata+0, 1, false);
        i2c_read_blocking(I2C_PORT, 0x41, rxdata+0, 4, false);

        printf("%d : ",idx);
        printf("%02x %02x %02x %02x\n",rxdata[0],rxdata[1],rxdata[2],rxdata[3]);

        rxdata[0]=0x70+(3*((idx>>3)&7));
        rxdata[1]=0xFF*((idx&1)?1:0);
        rxdata[2]=0xFF*((idx&2)?1:0);
        rxdata[3]=0xFF*((idx&4)?1:0);
        i2c_write_blocking(I2C_PORT, 0x41, rxdata+0, 4, false);

        sleep_ms(100);
    }
}

