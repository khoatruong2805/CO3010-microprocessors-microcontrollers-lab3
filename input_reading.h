#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include <stdint.h>
#define NO_OF_BUTTONS 3U
#define BUTTON_MODE 0U
#define BUTTON_UP 1U
#define BUTTON_SET 2U
void input_reading_init(void);
void button_reading(void);
uint8_t button_take_events(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);
#endif
