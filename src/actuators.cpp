#include <Servo.h>
#include "actuators.h"

/* Servos */
#define SERVO1 17
#define SERVO2 18
#define SERVO3 40
#define SERVO4 42

/* Buzzer */
#define BUZZER 14

Servo servos = Servo();
Pwm pwm = Pwm();

void init_servos() {
    servos.attach(SERVO1);
    servos.attach(SERVO2);
    servos.attach(SERVO3);
    servos.attach(SERVO4);
}

void servo_lift() {
    servos.write(SERVO4, 30);
}

void servo_drop() {
    servos.write(SERVO4, 150);
}

