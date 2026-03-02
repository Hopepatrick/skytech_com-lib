#include "skytech_com.h"
#include<tm4c123gh6pm.h>

SkyTech_UART uart;
SkyTech_SPI  spi;

int main()
{
    uart.init((volatile uint32_t *)GPIO_PORTC_DATA_R, 4, 5, 9600);
    spi.init((volatile uint32_t *)GPIO_PORTD_DATA_R, 0,1,2,3);

    uart.send("SkyTech Ready\n");
    uart.send(1234);

    spi.send("HELLO");

    while(1)
    {
        if(uart.available())
        {
            char c = uart.receive();
            spi.send(c);
        }
    }
}