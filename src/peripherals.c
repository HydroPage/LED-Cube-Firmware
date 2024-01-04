#include <avr/io.h>
#include "peripherals.h"


// SPI /////////////////////////////////////////////////////////////////////

#define SS_DDR DDRB
#define MOSI_DDR DDRB
#define SCK_DDR DDRB

#define SPI_SS 2
#define SPI_MOSI 3
#define SPI_SCK 5

void spi_initialize()
{
  // Outputs on MOSI, SCK and SS
  // (SS must be output for SPI master mode)
  MOSI_DDR |= (1 << SPI_MOSI);
  SCK_DDR |= (1 << SPI_SCK);
  SS_DDR |= (1 << SPI_SS);

  // Enable SPI, master
  SPCR |= (1 << SPE) | (1 << MSTR);

  // frequency F_CPU/2
  SPSR |= (1 << SPI2X);
}

void spi_send_byte(uint8_t byte)
{
  SPDR = byte;

  // According to Arduino source, this no-op can give up to 
  // 10% more speed at fast SPI speeds
  asm volatile("nop");

  // Wait for the interrupt-flag bit in the status register
  // (transmission complete)
  while (!(SPSR & (1 << SPIF)));
}

void spi_send_bytes(uint8_t *bytes, uint16_t length)
{
  for (uint16_t i = 0; i < length; i++)
    spi_send_byte(bytes[i]);
}


// UART ////////////////////////////////////////////////////////////////////

void serial_initialize(uint32_t baud)
{
  // Async receive-only, enable RX interrupt
  UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);

  // Formula from datasheet
  UBRR0 = (F_CPU / (16 * baud)) - 1;
}