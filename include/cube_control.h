#ifndef CUBE_CONTROL_H_
#define CUBE_CONTROL_H_


// Initialize the cube control module
void cube_initialize(void);

// Display the current data in the shift registers
void latch_layer_data(void);

// Index from 0 to 7, layer 0 is the bottom
void set_active_layer(uint8_t index);

void enable_outputs(void);

void disable_outputs(void);


#endif