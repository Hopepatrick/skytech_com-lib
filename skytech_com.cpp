#include "skytech_com.h"


// ================= SPI IMPLEMENTATION =================

SkyTech_SPI::SkyTech_SPI()
{
}

bool SkyTech_SPI::init(volatile uint32_t* port,
                       uint8_t cs,
                       uint8_t miso,
                       uint8_t mosi,
                       uint8_t sck)
{
    gpio_port = port;
    cs_pin = cs;
    miso_pin = miso;
    mosi_pin = mosi;
    sck_pin = sck;

    // Enable SSI1 and GPIOD clock
    SYSCTL_RCGCSSI_R  |= (1 << 1);
    SYSCTL_RCGCGPIO_R |= (1 << 3);
    while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0);

    SSI1_CR1_R &= ~0x02;   // Disable SSI

    // Default mapping PD0–PD3
    GPIO_PORTD_AFSEL_R |= 0x0F;
    GPIO_PORTD_PCTL_R  &= ~0x0000FFFF;
    GPIO_PORTD_PCTL_R  |=  0x00002222;
    GPIO_PORTD_DEN_R   |= 0x0F;
    GPIO_PORTD_AMSEL_R &= ~0x0F;

    SSI1_CR1_R = 0x00000000;  // Master
    SSI1_CC_R  = 0x0;
    SSI1_CPSR_R = 16;         // 1 MHz
    SSI1_CR0_R = 0x07;        // 8-bit

    SSI1_CR1_R |= 0x02;       // Enable

    return true;
}

void SkyTech_SPI::send(uint8_t data)
{
    while (SSI1_SR_R & (1 << 1));
    SSI1_DR_R = data;
}

void SkyTech_SPI::send(char data)
{
    send((uint8_t)data);
}

void SkyTech_SPI::send(int data)
{
    send((uint8_t)data);
}

void SkyTech_SPI::send(const char* str)
{
    while (*str)
    {
        send(*str++);
    }
}

uint8_t SkyTech_SPI::receive()
{
    while (SSI1_SR_R & (1 << 2));
    return (uint8_t)(SSI1_DR_R & 0xFF);
}

bool SkyTech_SPI::available()
{
    return !(SSI1_SR_R & (1 << 2));
}



// ================= UART IMPLEMENTATION =================

SkyTech_UART::SkyTech_UART()
{
}

bool SkyTech_UART::init(volatile uint32_t* port,
                        uint8_t tx,
                        uint8_t rx,
                        uint32_t baud)
{
    gpio_port = port;
    tx_pin = tx;
    rx_pin = rx;
    baudrate = baud;

    uint32_t uart_clk = 16000000;
    uint32_t int_div  = uart_clk / (16 * baudrate);
    uint32_t frac_div = ((uart_clk % (16 * baudrate)) * 64 + (baudrate / 2)) / baudrate;

    SYSCTL_RCGCUART_R |= (1 << 1);
    SYSCTL_RCGCGPIO_R |= (1 << 2);
    while ((SYSCTL_PRGPIO_R & (1 << 2)) == 0);

    UART1_CTL_R &= ~0x01;

    UART1_IBRD_R = int_div;
    UART1_FBRD_R = frac_div;
    UART1_LCRH_R = (0x3 << 5);

    UART1_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);

    GPIO_PORTC_AFSEL_R |= (1 << 4) | (1 << 5);
    GPIO_PORTC_PCTL_R  &= ~0x00FF0000;
    GPIO_PORTC_PCTL_R  |=  0x00220000;
    GPIO_PORTC_DEN_R   |= (1 << 4) | (1 << 5);
    GPIO_PORTC_AMSEL_R &= ~((1 << 4) | (1 << 5));

    return true;
}

void SkyTech_UART::send(uint8_t data)
{
    while (UART1_FR_R & (1 << 5));
    UART1_DR_R = data;
}

void SkyTech_UART::send(char data)
{
    send((uint8_t)data);
}

void SkyTech_UART::send(int data)
{
    char buffer[12];
    int i = 0;

    if (data == 0)
    {
        send('0');
        return;
    }

    while (data > 0)
    {
        buffer[i++] = (data % 10) + '0';
        data /= 10;
    }

    while (i--)
    {
        send(buffer[i]);
    }
}

void SkyTech_UART::send(const char* str)
{
    while (*str)
    {
        send(*str++);
    }
}

uint8_t SkyTech_UART::receive()
{
    while (UART1_FR_R & (1 << 4));
    return (uint8_t)(UART1_DR_R & 0xFF);
}

bool SkyTech_UART::available()
{
    return !(UART1_FR_R & (1 << 4));
}