#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_
#include <stdint.h>
void display_init(void);
void display_numbers(uint8_t first, uint8_t second);
void display_scan(void);
void traffic_write(uint16_t illuminated_pins);
#endif
