#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "OS.h"

unsigned int *result;

int main(void) {

    InitOscillator();
    InitIO();

    InitTimer1();
    InitTimer23();
    InitTimer4();

    InitPWM();
    InitADC1();


    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;
    
    //AcquireTelemetreVerite();
    //PWMSetSpeed(20,MOTEUR_DROITE);

    while (1) {

         if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int *result = ADCGetResult();
            float volts = ((float) result[4])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result[3])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche2 = 34 / volts - 5;
            volts = ((float) result[2])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result[1])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result[0])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit2 = 34 / volts - 5;


            if (robotState.distanceTelemetreDroit2< 30){
                LED_ORANGE = 1;
            } else {
                LED_ORANGE = 0;
            }
            if (robotState.distanceTelemetreCentre < 30) {
                LED_BLEUE = 1;
            } else {
                LED_BLEUE = 0;
            }
            if (robotState.distanceTelemetreGauche2< 30) {
                LED_BLANCHE = 1;
            } else {
                LED_BLANCHE = 0;
            }
        }
     }
}
