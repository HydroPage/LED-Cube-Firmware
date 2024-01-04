#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_


// SPI /////////////////////////////////////////////////////////////////////

void spi_initialize(void);

void spi_send_byte(uint8_t);

void spi_send_bytes(uint8_t *bytes, uint16_t length);


// UART ////////////////////////////////////////////////////////////////////

void serial_initialize(uint32_t baud);


#endif