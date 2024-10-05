/********************************************************************************************* */
//    Eduboard2 ESP32-S3 Template with BSP
//    Author: Martin Burger
//    Juventus Technikerschule
//    Version: 1.0.0
//    
//    This is the ideal starting point for a new Project. BSP for most of the Eduboard2
//    Hardware is included under components/eduboard2.
//    Hardware support can be activated/deactivated in components/eduboard2/eduboard2_config.h
/********************************************************************************************* */
#include "eduboard2.h"
#include "memon.h"

#include "math.h"

#define TAG "TEMPLATE"

#define UPDATETIME_MS 100

//----------------- Steur-Task ------------------------------------------------------------------------

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
    xTaskCreate(Steuer_Task,    //Subroutine
                "ui",                   //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                9,                      //Priority
                NULL);                  //Taskhandle

    xTaskCreate(Leibniz_Calculator,    //Subroutine
                "ui",                   //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                1,                      //Priority
                NULL);                  //Taskhandle

    xTaskCreate(other_Calculator,    //Subroutine
                "ui",                   //Name
                2*2048,                 //Stacksize
                NULL,                   //Parameters
                1,                      //Priority
                NULL);                  //Taskhandle
}