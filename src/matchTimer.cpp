#include "matchTimer.h"

int startTime;
uint8_t timeSeconds;

uint8_t getMatchTime() {
    return timeSeconds;
}

void TaskMatchTimer(void *pvParameters) {
    while (timeSeconds < 100) {
        int elapsedTime = millis() - startTime;
        timeSeconds = elapsedTime / 1000;

        Serial.println("Match time: " + String(timeSeconds) + "s");

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void startMatchTimer() {
    startTime = millis();
    timeSeconds = 0;
    xTaskCreate(TaskMatchTimer, "Task Match Timer", 2048, NULL, 1, NULL);
}