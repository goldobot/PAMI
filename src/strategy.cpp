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

void strat_superstar_rush_yellow(){

    moveStepper(-1200, 2500, 1000);

    /* Drop 1st mini PAMI */
     turnStepper(30, 3000, 1000);
     vTaskDelay(100 / portTICK_PERIOD_MS);
       servo_drop_r();
    vTaskDelay(350 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(30, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(400 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(30, 3000, 1000);
    moveStepper(-315, 800, 500);
}

void strat_superstar_VRAC_yellow(){
    moveStepper(-500, 2000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-700, 1500, 500);

    /* wait and Drop 1st mini PAMI */
    vTaskDelay(400 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(1200 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    moveStepper(-650, 1500, 500);
    turnStepper(80, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(70, 500, 500);
    moveStepper(-385, 400,300);
    turnStepper(-60, 500, 500);
    moveStepper(-110, 400,300);
}

void strat_groupie1_yellow(){
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    moveStepper(-400, 1000, 1000);
    turnStepper(45, 3000, 1000);
    moveStepper(-950, 1000, 1000);
    turnStepper(-100, 3000, 1000);

    turnStepper(-25, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    
    turnStepper(35, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    turnStepper(-20, 3000, 1000);
    moveStepper(-250, 1000, 500);
}

void strat_groupie1_onStage_yellow(){
    vTaskDelay(3500 / portTICK_PERIOD_MS);

    /*position start ramp*/
    moveStepper(-100, 1000, 1000);
    turnStepper(-23, 3000, 1000);
    moveStepper(-350, 1000, 1000);
    turnStepper(23, 3000, 1000);

    /*climb ramp*/
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-710, 1500, 500);

    /*face central pit and drop*/
    turnStepper(55, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(300 / portTICK_PERIOD_MS);  
    
    /*face our side pit and drop*/
    turnStepper(35, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);

   /*move to edge*/
    moveStepper(-260, 400, 300);
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
void strat_groupie2_goArround_yellow(){
    /* Move to central of table*/
    moveStepper(-400, 1000, 1000);
    turnStepper(75, 5000, 1000);
    moveStepper(-870, 1800, 1000);
    turnStepper(-75, 5000, 1000);
    moveStepper(-775, 1800, 1000);

    /* Face pit */
    turnStepper(-90, 5000, 1000);

    /* Drop 1st mini PAMI */
    servo_drop_r();
    vTaskDelay(300 / portTICK_PERIOD_MS);
    turnStepper(90, 5000, 1000);

    /* Move to last zone*/
    moveStepper(-880, 1800, 1000);
    turnStepper(-125, 5000, 1000);
    moveStepper(-400, 1800, 1000);
 
    /* Drop 2nd mini PAMI */
    servo_drop_l();
    vTaskDelay(300 / portTICK_PERIOD_MS);

    /* Move in pit */
    turnStepper(-25, 5000, 1000);
    moveStepper(-430, 1200, 1000);
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

void strat_superstar_rush_blue(){

    moveStepper(-1200, 2500, 1000);

    /* Drop 1st mini PAMI */
     turnStepper(-30, 3000, 1000);
     vTaskDelay(100 / portTICK_PERIOD_MS);
       servo_drop_l();
    vTaskDelay(350 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    turnStepper(-30, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(400 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(-30, 3000, 1000);
    moveStepper(-315, 800, 500);
}

void strat_superstar_VRAC_blue(){
    moveStepper(-500, 2000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-700, 1500, 500);

    /* wait and Drop 1st mini PAMI */
    vTaskDelay(600 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(2200 / portTICK_PERIOD_MS);

    /* Drop 2nd mini PAMI */
    moveStepper(-650, 1500, 500);
    turnStepper(-80, 500, 500);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    /* Go to edge */
    turnStepper(-70, 500, 500);
    moveStepper(-385, 400,300);
    turnStepper(60, 500, 500);
    moveStepper(-110, 400,300);
}

void strat_groupie1_blue(){
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    moveStepper(-400, 1000, 1000);
    turnStepper(-45, 3000, 1000);
    moveStepper(-950, 1000, 1000);
    turnStepper(100, 3000, 1000);

    turnStepper(25, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    
    turnStepper(-35, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

    turnStepper(20, 3000, 1000);
    moveStepper(-250, 1000, 500);
}

void strat_groupie1_onStage_blue(){
    vTaskDelay(3500 / portTICK_PERIOD_MS);

    /*position start ramp*/
    moveStepper(-100, 1000, 1000);
    turnStepper(23, 3000, 1000);
    moveStepper(-350, 1000, 1000);
    turnStepper(-23, 3000, 1000);

    /*climb ramp*/
    vTaskDelay(100 / portTICK_PERIOD_MS);
    moveStepper(-710, 1500, 500);

    /*face central pit and drop*/
    turnStepper(-55, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_l();
    vTaskDelay(300 / portTICK_PERIOD_MS);  
    
    /*face our side pit and drop*/
    turnStepper(-35, 3000, 1000);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    servo_drop_r();
    vTaskDelay(500 / portTICK_PERIOD_MS);

   /*move to edge*/
    moveStepper(-260, 400, 300);
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

void strat_groupie2_goArround_blue(){
    /* Move to central of table*/
    moveStepper(-400, 1000, 1000);
    turnStepper(-75, 5000, 1000);
    moveStepper(-870, 1800, 1000);
    turnStepper(75, 5000, 1000);
    moveStepper(-775, 1800, 1000);

    /* Face pit */
    turnStepper(90, 5000, 1000);

    /* Drop 1st mini PAMI */
    servo_drop_l();
    vTaskDelay(300 / portTICK_PERIOD_MS);
    turnStepper(-90, 5000, 1000);

    /* Move to last zone*/
    moveStepper(-880, 1800, 1000);
    turnStepper(125, 5000, 1000);
    moveStepper(-400, 1800, 1000);
 
    /* Drop 2nd mini PAMI */
    servo_drop_r();
    vTaskDelay(300 / portTICK_PERIOD_MS);

    /* Move in pit */
    turnStepper(25, 5000, 1000);
    moveStepper(-430, 1200, 1000);
}

void TaskStrategy(void *pvParameters) {
    init_diff_drive();
    
    if(current_side == SIDE_YELLOW) {
        if(pami_id == 0)
            //strat_superstar_yellow();
            strat_superstar_rush_yellow();
            //strat_superstar_VRAC_yellow();
        else if(pami_id == 1)
            strat_groupie1_yellow();
            //strat_groupie1_onStage_yellow();
        else if(pami_id == 2)
            strat_groupie2_yellow();
            //strat_groupie2_sansminiPAMI_yellow();
            //strat_groupie2_goArround_yellow();
    } else if(current_side == SIDE_BLUE) {
        if(pami_id == 0)
            //strat_superstar_blue();
            strat_superstar_rush_blue();
            //strat_superstar_VRAC_blue();
        else if(pami_id == 1)
            strat_groupie1_blue();
            //strat_groupie1_onStage_blue();
        else if(pami_id == 2)
            strat_groupie2_blue();
            //strat_groupie2_sansminiPAMI_blue();
            //strat_groupie2_goArround_blue();
    }

    stopStepper();
    disableSteppers();
    vTaskDelete(NULL);
}