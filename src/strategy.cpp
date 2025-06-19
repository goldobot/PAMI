#include "common.h"
#include "diff_drive.h"
#include "strategy.h"
#include "actuators.h"

extern enum side current_side;
extern uint8_t pami_id;

void strat_superstar_yellow(){
    moveStepper(500, 1000, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(700, 1000, 500);
    turnStepper(-90, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-320, 600,300);
}

void strat_groupie1_yellow(){

}

void strat_groupie2_yellow(){

}

void strat_superstar_blue(){
    moveStepper(500, 1000, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(700, 1000, 500);
    turnStepper(90, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-320, 600,300);
}

void strat_groupie1_blue(){

}

void strat_groupie2_blue(){

}

void TaskStrategy(void *pvParameters) {
    init_diff_drive();
    
    if(current_side == SIDE_YELLOW) {
        if(pami_id == 0)
            strat_superstar_yellow();
        else if(pami_id == 1)
            strat_groupie1_yellow();
        else if(pami_id == 2)
            strat_groupie2_yellow();
    } else if(current_side == SIDE_BLUE) {
        if(pami_id == 0)
            strat_superstar_blue();
        else if(pami_id == 1)
            strat_groupie1_blue();
        else if(pami_id == 2)
            strat_groupie2_blue();
    }

    stopStepper();
    disableSteppers();
    vTaskDelete(NULL);
}