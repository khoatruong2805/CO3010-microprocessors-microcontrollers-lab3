#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_
#include <stdint.h>
typedef struct {
    uint8_t mode, phase, remaining;
    uint8_t configured[3]; /* red, yellow, green confirmed with SET */
    uint8_t active[3];     /* last valid set used in AUTO */
    uint8_t editing, config_valid;
} TrafficStatus;
extern TrafficStatus traffic;
void input_processing_init(void);
void fsm_for_input_processing(void);
#endif
