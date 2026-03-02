#ifndef SKYTECH_COM_H
#define SKYTECH_COM_H

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

class SkyTech_SPI
{
private:
    volatile uint32_t* gpio_port;
    uint8_t cs_pin;
    uint8_t miso_pin;
    uint8_t mosi_pin;
    uint8_t sck_pin;

public:
    SkyTech_SPI();

    bool init(volatile uint32_t* port,
              uint8_t cs,
              uint8_t miso,
              uint8_t mosi,
              uint8_t sck);

    // Polymorphic Send
    void send(uint8_t data);
    void send(char data);
    void send(int data);
    void send(const char* str);

    uint8_t receive();
    bool available();
};


class SkyTech_UART
{
private:
    volatile uint32_t* gpio_port;
    uint8_t tx_pin;
    uint8_t rx_pin;
    uint32_t baudrate;

public:
    SkyTech_UART();

    bool init(volatile uint32_t* port,
              uint8_t tx,
              uint8_t rx,
              uint32_t baud);

    // Polymorphic Send
    void send(uint8_t data);
    void send(char data);
    void send(int data);
    void send(const char* str);

    uint8_t receive();
    bool available();
};

#endif