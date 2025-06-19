#include <Adafruit_NeoPixel.h>
#include "common.h"
#include "leds.h"

#define PIN_WS2812B 5 // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 4  // The number of LEDs (pixels) on WS2812B LED strip
#define RED_LED 10

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

/* Name of LEDs on the board*/
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

struct led_color
{
    uint8_t r; // red
    uint8_t g; // green
    uint8_t b; // blue
};

/* Stores current colors for the WS2812B */
struct led_color led_colors[LED_MAX];

struct led_color color_table[COLOR_MAX] = {
    {0, 0, 0},   // COLOR_OFF
    {64, 0, 0},  // COLOR_RED
    {0, 64, 0},  // COLOR_GREEN
    {0, 0, 64},  // COLOR_BLUE
    {64, 64, 0}, // COLOR_YELLOW
    {0, 64, 64}, // COLOR_CYAN
    {64, 0, 64}, // COLOR_MAGENTA
    {64, 64, 64} // COLOR_WHITE
};

void leds_update()
{
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    {
        ws2812b.setPixelColor(pixel, ws2812b.Color(led_colors[pixel].r,
                                                   led_colors[pixel].g,
                                                   led_colors[pixel].b));
    }
    ws2812b.show();
}

void init_leds()
{
    ws2812b.begin();
    ws2812b.clear();
    for (int pixel = 0; pixel < LED_MAX; pixel++)
    {
        led_colors[pixel].r = 0;
        led_colors[pixel].g = 0;
        led_colors[pixel].b = 0;
    }
    leds_update();
}

void set_side_blue()
{
    led_colors[LED_COLORSIDE].r = color_table[COLOR_BLUE].r;
    led_colors[LED_COLORSIDE].g = color_table[COLOR_BLUE].g;
    led_colors[LED_COLORSIDE].b = color_table[COLOR_BLUE].b;
    leds_update();
}

void set_side_yellow()
{
    led_colors[LED_COLORSIDE].r = color_table[COLOR_YELLOW].r;
    led_colors[LED_COLORSIDE].g = color_table[COLOR_YELLOW].g;
    led_colors[LED_COLORSIDE].b = color_table[COLOR_YELLOW].b;
    leds_update();
}

void show_start_pos(uint8_t pami_id, uint8_t side)
{
    led_colors[LED_DETECT_LEFT].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_LEFT].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_LEFT].b = color_table[COLOR_WHITE].b;

    led_colors[LED_DETECT_CENTER].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_CENTER].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_CENTER].b = color_table[COLOR_WHITE].b;

    led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_WHITE].b;

    if (side == SIDE_UNKNOWN)
        return;
    else if (side == SIDE_YELLOW)
    {
        switch (pami_id)
        {
        case 0:
            led_colors[LED_DETECT_LEFT].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_LEFT].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_LEFT].b = color_table[COLOR_RED].b;
            break;
        case 1:
            led_colors[LED_DETECT_CENTER].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_CENTER].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_CENTER].b = color_table[COLOR_RED].b;
            break;
        case 2:
            led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_RED].b;
            break;
        }
    }
    else if (side == SIDE_BLUE)
    {
        switch (pami_id)
        {
        case 0:
            led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_RED].b;
            break;
        case 1:
            led_colors[LED_DETECT_CENTER].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_CENTER].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_CENTER].b = color_table[COLOR_RED].b;
            break;
        case 2:
            led_colors[LED_DETECT_LEFT].r = color_table[COLOR_RED].r;
            led_colors[LED_DETECT_LEFT].g = color_table[COLOR_RED].g;
            led_colors[LED_DETECT_LEFT].b = color_table[COLOR_RED].b;
            break;
        }
    }
    leds_update();
}

/* All LEDs yellow*/
void leds_pull_wait()
{
    led_colors[LED_DETECT_LEFT].r = color_table[COLOR_YELLOW].r;
    led_colors[LED_DETECT_LEFT].g = color_table[COLOR_YELLOW].g;
    led_colors[LED_DETECT_LEFT].b = color_table[COLOR_YELLOW].b;

    led_colors[LED_DETECT_CENTER].r = color_table[COLOR_YELLOW].r;
    led_colors[LED_DETECT_CENTER].g = color_table[COLOR_YELLOW].g;
    led_colors[LED_DETECT_CENTER].b = color_table[COLOR_YELLOW].b;

    led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_YELLOW].r;
    led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_YELLOW].g;
    led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_YELLOW].b;

    leds_update();
}

/* All LEDs red*/
void leds_start_wait()
{
    led_colors[LED_DETECT_LEFT].r = color_table[COLOR_RED].r;
    led_colors[LED_DETECT_LEFT].g = color_table[COLOR_RED].g;
    led_colors[LED_DETECT_LEFT].b = color_table[COLOR_RED].b;

    led_colors[LED_DETECT_CENTER].r = color_table[COLOR_RED].r;
    led_colors[LED_DETECT_CENTER].g = color_table[COLOR_RED].g;
    led_colors[LED_DETECT_CENTER].b = color_table[COLOR_RED].b;

    led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_RED].r;
    led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_RED].g;
    led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_RED].b;

    leds_update();
}

/* All LEDs white*/
void leds_start_match()
{
    led_colors[LED_DETECT_LEFT].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_LEFT].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_LEFT].b = color_table[COLOR_WHITE].b;

    led_colors[LED_DETECT_CENTER].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_CENTER].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_CENTER].b = color_table[COLOR_WHITE].b;

    led_colors[LED_DETECT_RIGHT].r = color_table[COLOR_WHITE].r;
    led_colors[LED_DETECT_RIGHT].g = color_table[COLOR_WHITE].g;
    led_colors[LED_DETECT_RIGHT].b = color_table[COLOR_WHITE].b;

    leds_update();
}

void TaskRainbow(void *pvParameters)
{
    rainbow(10); // Call the rainbow function with a delay of 10 ms
    vTaskDelete(NULL); // Delete the task after completion
}

/* Party time*/
void rainbow(int wait)
{
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
        for (int i = 0; i < ws2812b.numPixels(); i++)
        {
            int pixelHue = firstPixelHue + (i * 65536L / ws2812b.numPixels());
            ws2812b.setPixelColor(i, ws2812b.gamma32(ws2812b.ColorHSV(pixelHue)));
        }
        ws2812b.show();
        vTaskDelay(wait / portTICK_PERIOD_MS);
    }
}
