#include <Arduino.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "esp_task_wdt.h"

#include "actuators.h"
#include "avoidance.h"
#include "common.h"
#include "diff_drive.h"
#include "leds.h"
#include "matchTimer.h"
#include "strategy.h"

/* Time before start (85 for real match)*/
#if 0
  #define WAIT_TIME 85
#else
  #define WAIT_TIME 5 // For testing purposes, set to 5 seconds
#endif

#if 0
  #define DURATION 14
#else
  #define DURATION 10
#endif

#define AU_STATUS 1
#define TIRETTE 9
#define COLOR_BTN 4

/* PAMI identification */
#define ID1 7
#define ID2 6

/* Sensors */
#define USW1 15
#define USW2 2
#define USW3 13
#define CAPTOR1 41
#define CAPTOR2 21

/* Motors */
#define M1_STEP 48
#define M1_DIR 16
#define M2_STEP 38
#define M2_DIR 39

/* Buzzer */
#define BUZZER 14

#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

enum side current_side = SIDE_UNKNOWN;

uint8_t pami_id = 0;

/* Used to stop button task to disable side change after pulling tirette */
bool waitForStart = true;

void switchSide() {
  if (current_side == SIDE_YELLOW) {
    current_side = SIDE_BLUE;
    set_side_blue();
  } else {
    current_side = SIDE_YELLOW;
    set_side_yellow();
  }
  show_start_pos(pami_id, current_side);
}

/* Function to read ID pins and display start pos */
void init_pami() {
  pinMode(ID1, INPUT_PULLUP);
  pinMode(ID2, INPUT_PULLUP);

  if(digitalRead(ID1) == HIGH && digitalRead(ID2) == HIGH) {
    pami_id = 0; // Not implemented
  } else if(digitalRead(ID1) == LOW && digitalRead(ID2) == HIGH) {
    pami_id = 0; // SUPERSTAR
  } else if(digitalRead(ID1) == LOW && digitalRead(ID2) == HIGH) {
    pami_id = 1; // PAMI ID 2
  } else if(digitalRead(ID1) == LOW && digitalRead(ID2) == LOW) {
    pami_id = 2; // PAMI ID 3
  }

  show_start_pos(pami_id, current_side);
}

/* Task Checking button to change color */
void TaskButton(void *pvParameters) {
  uint8_t currentState;
  uint8_t lastState = HIGH;
  while (waitForStart == true) {
    currentState = digitalRead(COLOR_BTN);
    if (currentState != lastState) {
      if (currentState == LOW) { // Button pressed
        Serial.println("Change side");
        switchSide();
      }
      lastState = currentState;
    }
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void waitTirette() {
    /* Wait for tirette insertion */
    while (digitalRead(TIRETTE) == HIGH) {
      vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    Serial.println("Tirette present");
    leds_pull_wait();
    /* Wait for tirette pull */
    vTaskDelay (500 / portTICK_PERIOD_MS);
    while (digitalRead(TIRETTE) == LOW) {
      vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    Serial.println("Tirette pulled, starting match");
    waitForStart = false;
    leds_start_wait();
}

/* function to wait start time */
void waitStart() {
  while (getMatchTime() < WAIT_TIME) {
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
  /* Add 500ms just in case to avoid jumpstart */
  vTaskDelay(500 / portTICK_PERIOD_MS);
}

/* function to wait start time */
void waitMatchEnd() {
  while (getMatchTime() < WAIT_TIME + DURATION) {
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(TIRETTE, INPUT);
  pinMode(COLOR_BTN, INPUT_PULLUP);

  init_leds();
  init_servos();
  init_pami();
  init_sensors();
  servo_drop();

  /* Task to check color button */
  vTaskDelay (500 / portTICK_PERIOD_MS);
  xTaskCreate(TaskButton, "Task Button", 4096, NULL, 1, NULL);
  
  waitTirette();

  startMatchTimer();

  waitStart();
  
  /* Start Match */
  Serial.println("GO GO GO !!!");
  servo_lift();
  leds_start_match();

  // TODO : Lift mini PAMIs
  /* Task to check sensor for collision avoidance */
  xTaskCreate(TaskAvoidance, "Task Avoidance", 4096, NULL, 1, NULL);
  /* Task to move the PAMI*/
  xTaskCreatePinnedToCore(TaskStrategy, "Task Strategy" ,4096,NULL,2, NULL, 0);


  waitMatchEnd();
  /* stop movement */
  disableSteppers();

  /* Party time */
  xTaskCreate(TaskRainbow, "Task Rainbow", 4096, NULL, 1, NULL);
}

void loop() {
  servo_lift();
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  servo_drop();
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}