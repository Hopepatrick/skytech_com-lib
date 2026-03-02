# SkyTech Communication Library (TM4C123GH6PM)

A lightweight C++ communication library for the TM4C123GH6PM (Tiva C Series) microcontroller.

Developed by Patrick NDAYIKUNDA / SkyTech Electronics to provide a simple, reusable, and object-oriented interface for UART and SPI communication using direct register-level programming.

---

## Features

- Object-Oriented C++ design
- Register-level control (No TivaWare required)
- UART communication support
- SPI (SSI) communication support
- Polymorphic send functions:
  - Characters
  - Strings
  - Integers
  - Bytes
- Receive functions
- Data availability checking
- Clean separation between header and implementation
---

## Supported Microcontroller

- TM4C123GH6PM (Tiva C Series)
- 16 MHz default system clock

---

## Project Structure
/SkyTech-Com
│
├── skytech_com.h
├── skytech_com.cpp
└── example_main.cpp
