#include "main.h"
#include "input_processing.h"
#include "input_reading.h"
#include "led_display.h"

TrafficStatus traffic;
static uint32_t second_at, blink_at, repeat_at;
static uint8_t blink_on, repeating;
static uint8_t count_ns, count_we;

static void start_auto(uint32_t now)
{
    for (uint8_t i = 0; i < 3; ++i) {
        traffic.active[i] = traffic.configured[i];
    }
    traffic.config_valid = 1;
    traffic.phase = 0;
    count_ns = traffic.active[2];
    count_we = traffic.active[0];
    second_at = now;
}

void input_processing_init(void)
{
    traffic.mode = 1;
    traffic.configured[0] = traffic.active[0] = 5;
    traffic.configured[1] = traffic.active[1] = 2;
    traffic.configured[2] = traffic.active[2] = 3;
    traffic.editing = 5;
    repeating = 0;
    blink_on = 1;
    blink_at = repeat_at = HAL_GetTick();
    start_auto(HAL_GetTick());
}

static void increase_editing(void)
{
    traffic.editing = traffic.editing == 99 ? 1 : traffic.editing + 1;
}

void fsm_for_input_processing(void)
{
    uint32_t now = HAL_GetTick();
    uint8_t events = button_take_events();

    if (events & (1U << BUTTON_MODE)) {
        traffic.mode = traffic.mode == 4 ? 1 : traffic.mode + 1;
        repeating = 0;
        blink_at = now;
        blink_on = 1;
        if (traffic.mode == 1) start_auto(now);
        else traffic.editing = traffic.configured[traffic.mode - 2];
        events = 0;
    }

    if (traffic.mode == 1) {
        while ((uint32_t)(now - second_at) >= 1000U) {
            second_at += 1000U;
            if (count_ns > 0) count_ns--;
            if (count_we > 0) count_we--;
            switch (traffic.phase) {
            case 0:
                if (count_ns == 0) {
                    traffic.phase = 1;
                    count_ns = traffic.active[1];
                }
                break;

            case 1:
                if (count_ns == 0) {
                    if (count_we > 0) {
                        count_ns = count_we;
                    } else {
                        traffic.phase = 2;
                        count_ns = traffic.active[0];
                        count_we = traffic.active[2];
                    }
                }
                break;

            case 2:
                if (count_we == 0) {
                    traffic.phase = 3;
                    count_we = traffic.active[1];
                }
                break;

            case 3:
                if (count_we == 0) {
                    if (count_ns > 0) {
                        count_we = count_ns;
                    } else {
                        traffic.phase = 0;
                        count_ns = traffic.active[2];
                        count_we = traffic.active[0];
                    }
                }
                break;
            }
        }
        if (traffic.phase == 0) {
            traffic_write(GREENns_Pin | REDwe_Pin);
        } else if (traffic.phase == 1) {
            if (count_ns == count_we && count_we > 0) {
                traffic_write(REDns_Pin | REDwe_Pin);
            } else {
                traffic_write(YELLOWns_Pin | REDwe_Pin);
            }
        } else if (traffic.phase == 2) {
            traffic_write(REDns_Pin | GREENwe_Pin);
        } else {
            if (count_we == count_ns && count_ns > 0) {
                traffic_write(REDns_Pin | REDwe_Pin);
            } else {
                traffic_write(REDns_Pin | YELLOWwe_Pin);
            }
        }
        display_numbers(count_ns, count_we);
        return;
    }

    if (events & (1U << BUTTON_UP)) {
        increase_editing();
        repeating = 0;
    }
    if (!is_button_pressed(BUTTON_UP)) repeating = 0;
    else if (is_button_pressed_1s(BUTTON_UP)) {
        if (!repeating) { repeating = 1; repeat_at = now; }
        else if ((uint32_t)(now - repeat_at) >= 500U) {
            repeat_at += 500U;
            increase_editing();
        }
    }

    if (events & (1U << BUTTON_SET)) {
        traffic.configured[traffic.mode - 2] = traffic.editing;
        traffic.config_valid = 1;
    }

    while ((uint32_t)(now - blink_at) >= 250U) {
        blink_at += 250U;
        blink_on = !blink_on;
    }
    uint16_t lights = traffic.mode == 2 ? REDns_Pin | REDwe_Pin
        : traffic.mode == 3 ? YELLOWns_Pin | YELLOWwe_Pin : GREENns_Pin | GREENwe_Pin;
    traffic_write(blink_on ? lights : 0);
    display_numbers(traffic.editing, traffic.mode);
}
