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
#define BIT_TEST5       1 << 4
#define BIT_TEST6       1 << 5
#define BIT_TEST7       1 << 6
#define BIT_TEST8       1 << 7
#define ALL_BITS        0xFF
EventGroupHandle_t Controlleventgroup = NULL;
//----------------- Steuer-Task ------------------------------------------------------------------------

void Steuer_Task(void* param){

Controlleventgroup = xEventGroupCreate();
        if(button_get_state(SW0, true) == SHORT_PRESSED){
            xEventGroupSetBits(Controlleventgroup, BIT_Start);
            xEventGroupClearBits(Controlleventgroup, BIT_End);
        }

        if(button_get_state(SW1, true) == SHORT_PRESSED){
            xEventGroupSetBits(Controlleventgroup, BIT_End);
            xEventGroupClearBits(Controlleventgroup, BIT_Start);
        }
        if(button_get_state(SW2, true) == SHORT_PRESSED){
            xEventGroupSetBits(Controlleventgroup, BIT_SetBack);
        }
        if(button_get_state(SW3, true) == SHORT_PRESSED){
            if(xEventGroupGetBits(Controlleventgroup) & BIT_change) {
                xEventGroupClearBits(Controlleventgroup, BIT_change);
            }
            if(xEventGroupGetBits(Controlleventgroup) & !BIT_change) {
                xEventGroupSetBits(Controlleventgroup, BIT_change);
            }
        }
    vTaskDelay(500/portTICK_PERIOD_MS);
}
//----------------- Leibniz-Calclator ------------------------------------------------------------------------

void Leibniz_Calculator(void* param){

    
    vTaskDelay(300/portTICK_PERIOD_MS);
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