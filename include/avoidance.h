#include <Arduino.h>

bool getObstacleFront();
bool getObstacleRear();
void init_sensors();
void TaskAvoidance(void *pvParameters);