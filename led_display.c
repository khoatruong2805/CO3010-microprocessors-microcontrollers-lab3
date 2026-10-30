#include "main.h"
#include "led_display.h"
#define TRAFFIC_MASK (REDns_Pin | GREENns_Pin | YELLOWns_Pin | REDwe_Pin | GREENwe_Pin | YELLOWwe_Pin)
#define SEG_MASK (SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin)
#define EN_MASK (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin)
static const uint8_t font[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static const uint16_t enables[4] = {EN0_Pin,EN1_Pin,EN2_Pin,EN3_Pin};
static uint8_t digits[4], scan_index;
static uint32_t scan_at;
static uint16_t previous_lights = 0xffff;
void traffic_write(uint16_t illuminated_pins)
{
    illuminated_pins &= TRAFFIC_MASK;
    if (illuminated_pins == previous_lights) return;
    previous_lights = illuminated_pins;
    /* Active-low: switch all lamps off before selecting the new phase. */
    HAL_GPIO_WritePin(GPIOA, TRAFFIC_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, illuminated_pins & TRAFFIC_MASK, GPIO_PIN_RESET);
}
void display_init(void)
{
    previous_lights = 0xffff;
    HAL_GPIO_WritePin(GPIOB, EN_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, SEG_MASK, GPIO_PIN_SET);
    scan_index = 0;
    scan_at = HAL_GetTick();
    display_numbers(0,0);
}
void display_numbers(uint8_t first, uint8_t second)
{
    digits[0] = (first / 10U) % 10U;
    digits[1] = first % 10U;
    digits[2] = (second / 10U) % 10U;
    digits[3] = second % 10U;
}
void display_scan(void)
{
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - scan_at) < 5U) return;
    scan_at = now;
    HAL_GPIO_WritePin(GPIOB, EN_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, SEG_MASK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, (uint16_t)(font[digits[scan_index]] << 8), GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, enables[scan_index], GPIO_PIN_RESET);
    scan_index = (scan_index + 1U) % 4U;
}
