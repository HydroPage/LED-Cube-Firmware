/*
 * Final LED cube firmare
 * main.c
 * 
 * Author: Alejandro Laverde
 * Last modified: 1/4/2024
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "peripherals.h"
#include "cube_control.h"

// 0.0% error at 16MHz according to datasheet
#define BAUD_RATE 250000

#define MATRIX_SIZE 64
#define NUM_LAYERS 8
#define NUM_ROWS 8

/*
 * A marking on a corner of the base of the cube should 
 * indicate the bottom-left corner. This should be 
 * layer 0, row 0, column 0 of the cube
 * (or array 0, byte 0, bit 0 of the data matrix)
 */
uint8_t matrix[NUM_LAYERS][NUM_ROWS];

/*
 * Serial receive interrupt.
 * Every incoming byte gets written to the matrix the
 * moment it arrives. This means no V-Sync, but it should
 * be too fast to matter.
 * 
 * Note that all math is in powers of 2, so the compiler
 * should make this extremely efficient.
 */
ISR(USART_RX_vect)
{
  static uint8_t index = 0;
  
  uint8_t layer = index / NUM_LAYERS;
  uint8_t row = index % NUM_ROWS;
  matrix[layer][row] = UDR0;

  // Cycle from 0 to MATRIX_SIZE - 1
  index = (index + 1) % MATRIX_SIZE;
}

int main(void)
{
  spi_initialize();
  serial_initialize(BAUD_RATE);
  cube_initialize();
  sei();

  while(1)
  {
    // NOTE: The last shift register in the chain = layer 0
    // because layer 0 is pushed first each pass
    for (uint8_t layer = 0; layer < NUM_LAYERS; layer++)
    {
      spi_send_bytes(matrix[layer], NUM_ROWS);

      disable_outputs();
      set_active_layer(layer);
      latch_layer_data();
      enable_outputs();
    }
  }
}