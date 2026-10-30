#include "main.h"
#include "input_reading.h"
#define DEBOUNCE_MS 20U
static const uint16_t pins[NO_OF_BUTTONS] = {BT0_Pin, BT1_Pin, BT2_Pin};
static uint8_t previous[NO_OF_BUTTONS];
static volatile uint8_t stable[NO_OF_BUTTONS];
static uint32_t changed_at[NO_OF_BUTTONS];
static volatile uint32_t pressed_at[NO_OF_BUTTONS];
static volatile uint8_t events;
void input_reading_init(void)
{
    events = 0;
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        previous[i] = stable[i] = 0;
        changed_at[i] = pressed_at[i] = HAL_GetTick();
    }
}
/* Called by TIM2; timing is measured in milliseconds, not interrupt counts. */
void button_reading(void)
{
    uint32_t now = HAL_GetTick();
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        uint8_t raw = HAL_GPIO_ReadPin(GPIOB, pins[i]) == GPIO_PIN_RESET;
        if (raw != previous[i]) {
            previous[i] = raw;
            changed_at[i] = now;
        }
        if (raw != stable[i] && (uint32_t)(now - changed_at[i]) >= DEBOUNCE_MS) {
            stable[i] = raw;
            if (raw) {
                pressed_at[i] = now;
                events |= (uint8_t)(1U << i);
            }
        }
    }
}
uint8_t button_take_events(void)
{
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    uint8_t result = events;
    events = 0;
    __set_PRIMASK(mask);
    return result;
}
unsigned char is_button_pressed(uint8_t index)
{
    return index < NO_OF_BUTTONS && stable[index];
}
unsigned char is_button_pressed_1s(uint8_t index)
{
    return index < NO_OF_BUTTONS && stable[index]
        && (uint32_t)(HAL_GetTick() - pressed_at[index]) >= 1000U;
}
