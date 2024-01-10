#include <avr/io.h>
#include "cube_control.h"

#define LAYER_SELECT_DDR DDRC
#define LAYER_SELECT_PORT PORTC
#define LS0 0
#define LS1 1
#define LS2 2

#define OUTPUT_ENABLE_DDR DDRB
#define OUTPUT_ENABLE_PORT PORTB
#define OE 0

#define LATCH_DDR DDRB
#define LATCH_PORT PORTB
#define LATCH 1

void cube_initialize(void)
{
  LAYER_SELECT_DDR |= (1 << LS0) | (1 << LS1) | (1 << LS2);
  OUTPUT_ENABLE_DDR |= (1 << OE);
  LATCH_DDR |= (1 << LATCH);
}

void latch_layer_data(void)
{
  LATCH_PORT |= (1 << LATCH);
  LATCH_PORT &= ~(1 << LATCH);
}

void set_active_layer(uint8_t index)
{
  LAYER_SELECT_PORT = (LAYER_SELECT_PORT & ~0b111) | (index & 0b111);
}

void enable_outputs(void)
{
  // Active low
  OUTPUT_ENABLE_PORT &= ~(1 << OE);
}

void disable_outputs(void)
{
  OUTPUT_ENABLE_PORT |= (1 << OE);
}