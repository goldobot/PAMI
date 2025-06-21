#include "matchTimer.h"

int startTime;
int timeSeconds;

int getMatchTime() {
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

void startMatchTimer(int timeOffset) {
    startTime = millis() + timeOffset;
    timeSeconds = 0;
    xTaskCreate(TaskMatchTimer, "Task Match Timer", 2048, NULL, 1, NULL);
}
