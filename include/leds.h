#ifndef LEDS_H
#define LEDS_H

#define PIN_WS2812B 5 // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 4  // The number of LEDs (pixels) on WS2812B LED strip
#define RED_LED 10

enum led_name
{
    LED_COLORSIDE = 0,
    LED_DETECT_RIGHT = 1,
    LED_DETECT_CENTER = 2,
    LED_DETECT_LEFT = 3,
    LED_MAX = NUM_PIXELS,
};

/* Color names */
enum color
{
    COLOR_OFF,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_WHITE,
    COLOR_MAX,
};

void init_leds();
void set_side_blue();
void set_side_yellow();
void show_start_pos(uint8_t pami_id, uint8_t side);
void leds_tirette_wait(bool tirette, bool au_status);
void leds_start_wait(uint8_t led_no);
void leds_start_match();
void TaskRainbow(void *pvParameters);
void rainbow(int wait);

#endif /* LEDS_H */