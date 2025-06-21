#include "common.h"
#include "diff_drive.h"
#include "strategy.h"
#include "actuators.h"

extern enum side current_side;
extern uint8_t pami_id;

void strat_superstar_yellow(){
    moveStepper(-500, 2000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-700, 1500, 500);

    /* Drop 1st mini PAMI */
    turnStepper(30, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(30, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(30, 500, 500);
    moveStepper(-315, 400,300);
}

void strat_groupie1_yellow(){
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    moveStepper(-400, 1000, 1000);
    turnStepper(45, 3000, 1000);
    moveStepper(-950, 1000, 1000);
    turnStepper(-100, 3000, 1000);

    turnStepper(-20, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    
    turnStepper(30, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    turnStepper(-10, 3000, 1000);
    moveStepper(-250, 1000, 500);
}

void strat_groupie2_yellow(){
    /* Move to last zone*/
    moveStepper(-400, 1000, 1000);
    turnStepper(45, 3000, 1000);
    moveStepper(-700, 1000, 1000);
    turnStepper(-45, 3000, 1000);
    moveStepper(-850, 1000, 1000);

    /* Face pit */
    turnStepper(-90, 3000, 1000);

    /* Drop 1st mini PAMI */
    turnStepper(-10, 3000, 1000);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(20, 3000, 1000);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Move in pit */
    turnStepper(-10, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-200, 1000, 1000);
}

void strat_groupie2_sansminiPAMI_yellow(){
    /* Move to last zone*/
    moveStepper(-400, 500, 600);
    turnStepper(18, 3000, 1000);
    moveStepper(-700, 500, 600);
    /*face the crowd*/
    turnStepper(-108, 3000, 1000);
}

void strat_superstar_blue(){
    moveStepper(-500, 2000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-700, 1500, 500);

    /* Drop 1st mini PAMI */
    turnStepper(-30, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(-30, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(-30, 500, 500);
    moveStepper(-315, 400,300);
}

void strat_groupie1_blue(){
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    moveStepper(-400, 1000, 1000);
    turnStepper(-45, 3000, 1000);
    moveStepper(-950, 1000, 1000);
    turnStepper(100, 3000, 1000);

    turnStepper(20, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    
    turnStepper(-30, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    turnStepper(10, 3000, 1000);
    moveStepper(-250, 1000, 500);
}

void strat_groupie2_blue(){

    /* Move to last zone*/
    moveStepper(-400, 6000, 1000);
    turnStepper(-45, 3000, 1000);
    moveStepper(-700, 6000, 1000);
    turnStepper(45, 3000, 1000);
    moveStepper(-850, 6000, 1000);

    /* Face pit */
    turnStepper(90, 3000, 1000);

    /* Drop 1st mini PAMI */
    turnStepper(10, 3000, 1000);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(-20, 3000, 1000);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Move in pit */
    turnStepper(10, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-200, 1000, 1000);
}

void strat_groupie2_sansminiPAMI_blue(){
    /* Move to last zone*/
    moveStepper(-400, 500, 600);
    turnStepper(-18, 3000, 1000);
    moveStepper(-700, 500, 600);
    /*face the crowd*/
    turnStepper(108, 3000, 1000);
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
            //strat_groupie2_sansminiPAMI_yellow();
    } else if(current_side == SIDE_BLUE) {
        if(pami_id == 0)
            strat_superstar_blue();
        else if(pami_id == 1)
            strat_groupie1_blue();
        else if(pami_id == 2)
            strat_groupie2_blue();
            //strat_groupie2_sansminiPAMI_blue();
    }

    stopStepper();
    disableSteppers();
    vTaskDelete(NULL);
}