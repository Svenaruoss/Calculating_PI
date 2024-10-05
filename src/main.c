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

//----------------- Global Variable --------------------------------------------------------------------
unsigned char LeibnizPi = 0;
unsigned char OtherPI   = 0;

//----------------- EventBits --------------------------------------------------------------------------
EventGroupHandle_t SwitchEventGroup = NULL;
EventGroupHandle_t StartEventGroup = NULL;
EventGroupHandle_t EndEventGroup = NULL;
EventGroupHandle_t SetBackEventGroup = NULL;
//----------------- Steuer-Task ------------------------------------------------------------------------

void Steuer_Task(void* param){

}
//----------------- Leibniz-Calclator ------------------------------------------------------------------------

void Leibniz_Calculator(void* param){

}

//----------------- ""-Calclator ------------------------------------------------------------------------
void other_Calculator(void* param){

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