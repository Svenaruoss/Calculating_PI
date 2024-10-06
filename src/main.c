/********************************************************************************************* */
//    PI Calculator
//    Author: Svenja Ruoss
//    Juventus Technikerschule
//    Version: 1.0.0
//    
//   
//    
//   
/********************************************************************************************* */
#include "eduboard2.h"
#include "memon.h"

#include "math.h"

#define TAG "PI_Calculator"

#define SteuerTask          "SteuerTask"
#define LeibnizTask         "LeibnizTask"   
#define OtherTask           "OtherTask"

#define UPDATETIME_MS 100

//----------------- Switch -----------------------------------------------------------------------------
#define ControllingMenu
#define ButtonON

//----------------- Global Variable --------------------------------------------------------------------
unsigned char LeibnizPi = 0;
unsigned char OtherPI   = 0;

//----------------- EventBits --------------------------------------------------------------------------
/*EventGroupHandle_t changeEventGroup     = NULL;
EventGroupHandle_t StartEventGroup      = NULL;
EventGroupHandle_t EndEventGroup        = NULL;
EventGroupHandle_t SetBackEventGroup    = NULL;*/

#define BIT_change      1 << 0
#define BIT_Start       1 << 1
#define BIT_End         1 << 2
#define BIT_SetBack     1 << 3

EventGroupHandle_t xControlleventgroup;
//----------------- Steuer-Task ------------------------------------------------------------------------

void Steuer_Task(void* param){

xControlleventgroup = xEventGroupCreate();
        if(button_get_state(SW0, true) == SHORT_PRESSED){
            xEventGroupSetBits(xControlleventgroup, BIT_Start);
            xEventGroupClearBits(xControlleventgroup, BIT_End);
        }

        if(button_get_state(SW1, true) == SHORT_PRESSED){
            xEventGroupSetBits(xControlleventgroup, BIT_End);
            xEventGroupClearBits(xControlleventgroup, BIT_Start);
        }
        if(button_get_state(SW2, true) == SHORT_PRESSED){
            xEventGroupSetBits(xControlleventgroup, BIT_SetBack);
        }
        if(button_get_state(SW3, true) == SHORT_PRESSED){
            if(xEventGroupGetBits(xControlleventgroup) & BIT_change) {
                xEventGroupClearBits(xControlleventgroup, BIT_change);
            }
            if(xEventGroupGetBits(xControlleventgroup) & !BIT_change) {
                xEventGroupSetBits(xControlleventgroup, BIT_change);
            }
        }
    vTaskDelay(500/portTICK_PERIOD_MS);
}
//----------------- Leibniz-Calclator ------------------------------------------------------------------------

void Leibniz_Calculator(void* param){
    double pi = 0.0;
    int k = 0;
    while (1) {
        EventBits_t uxBits = xEventGroupWaitBits(xControlleventgroup, BIT_Start | BIT_End | BIT_SetBack, pdTRUE, pdFALSE, portMAX_DELAY);

        if (uxBits & BIT_Start) {
            pi += (k % 2 == 0 ? 1.0 : -1.0) / (2 * k + 1);
            k++;
            printf("Leibniz π: %.10f\n", pi * 4);
            vTaskDelay(pdMS_TO_TICKS(500));
        } 
        else if (uxBits & BIT_End) {
            vTaskSuspend(NULL);
        } else if (uxBits & BIT_SetBack) {
            pi = 0.0;
            k = 0;
        }
    }
}

//----------------- ""-Calclator ------------------------------------------------------------------------
void other_Calculator(void* param){


    vTaskDelay(300/portTICK_PERIOD_MS);
}

//----------------- Task's ------------------------------------------------------------------------

/*void templateTask(void* param) {
    //Init stuff here

    for(;;) {
        // task main loop
        if(button_get_state(SW0, true) == SHORT_PRESSED) {
            led_toggle(LED0);
        }
        led_toggle(LED7);
        // delay
        vTaskDelay(UPDATETIME_MS/portTICK_PERIOD_MS);
    }
}*/

void app_main()
{
    //Initialize Eduboard2 BSP
    eduboard2_init();
    
    //Create templateTask
    xTaskCreate(Steuer_Task,            //Subroutine
                "Steuerung",            //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                9,                      //Priority
                NULL);                  //Taskhandle

    xTaskCreate(Leibniz_Calculator,     //Subroutine
                "Leibniz-Rechner",      //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                1,                      //Priority
                NULL);                  //Taskhandle

    xTaskCreate(other_Calculator,       //Subroutine
                "anderer-Rechner",      //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                1,                      //Priority
                NULL);                  //Taskhandle
}