#include "avoidance.h"
#include "matchTimer.h"

/* Sensors */
#define USW1 15
#define USW2 2
#define CAPTOR1 41
#define CAPTOR2 21

bool obstacleFrontLeft = false;
bool obstacleFrontRight = false;

bool obstacleRearLeft = false;
bool obstacleRearRight = false;

bool getObstacleFront() {
    return obstacleFrontLeft || obstacleFrontRight;
}

bool getObstacleFrontLeft() {
    return obstacleFrontLeft;
}

bool getObstacleFrontRight() {
    return obstacleFrontRight;
}

bool getObstacleRear() {
    return obstacleRearLeft || obstacleRearRight;
}

bool getObstacleRearLeft() {
    return obstacleRearLeft;
}

bool getObstacleRearRight() {
    return obstacleRearRight;
}

void init_sensors() {
    pinMode(USW1, INPUT);
    pinMode(USW2, INPUT);
    pinMode(CAPTOR1, INPUT);
    pinMode(CAPTOR2, INPUT);
}

void TaskAvoidance(void *pvParameters) {
    init_sensors();
    
    while (getMatchTime() < matchTotalDuration) {
        // Check bumper sensors
        if (digitalRead(USW1) == LOW)
            obstacleFrontLeft = true;
        else
            obstacleFrontLeft = false;

        if (digitalRead(USW2) == LOW)
            obstacleFrontRight = true;
        else
            obstacleFrontRight = false;

        // Check captors
        if (digitalRead(CAPTOR1) == LOW)
            obstacleRearLeft = true;
        else
            obstacleRearLeft = false;

        if (digitalRead(CAPTOR1) == LOW)
            obstacleRearRight = true;
        else 
            obstacleRearRight = false;

        vTaskDelay(10);
    }

    vTaskDelete(NULL);
}