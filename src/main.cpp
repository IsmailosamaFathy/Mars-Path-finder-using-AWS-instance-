#include <Arduino.h>
#include "motorDriver.h"
#include "sensorDriver.h"
#include "collision.h"
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "AWS.h"

void taskOne( void * parameter);
void taskTwo( void * parameter);
void taskThree( void * parameter);

#define LED_BOARD 2 //change here the pin of the board to V2
#define configMAX_PRIORITIES     4
// this is me
mclass m;
Collision collisionSensor;
myawsclass aws;
sclass s;
int i=0;


void setup(){

  pinMode(LED_BOARD, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  
  m.SETUP();
  s.SETUP();
  aws.connectAWS();
  // aws.stayConnected();

  // m.set_speed(MotorA,Forward,255);
  // m.set_speed(MotorB,Forward,255);


  xTaskCreate(
                    taskOne,          /* Task function. */
                    "LED BLINKING",    /* String with name of task. */
                    5120,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

  // xTaskCreate(
  //                   taskTwo,            /* Task function. */
  //                   "Rover Movement",   /* String with name of task. */
  //                   4096,               /* Stack size in bytes. */
  //                   NULL,               /* Parameter passed as input of the task */
  //                   3,                  /* Priority of the task. */
  //                   NULL);              /* Task handle. */

  // xTaskCreate(
  //                   taskThree,            /* Task function. */
  //                   "Obstacle Detection", /* String with name of task. */
  //                   8192,                 /* Stack size in bytes. */
  //                   NULL,                 /* Parameter passed as input of the task */
  //                   3,                    /* Priority of the task. */
  //                   NULL);                /* Task handle. */                    
}

void loop(){

  int16_t *resultArray = s.reading();
   aws.stayConnected();
    //Serial.println("RX: " + String(rx) + ", RY: " + String(ry) + ", RA: " + String(ra) + ", TX: " + String(tx) + ", TY: " + String(ty));
   //Serial.print("Data from AWS : "+ value);
    // Serial.print("Data from AWS : "+ String(payload));
  // Print the measured values for left, center, and right segments
  // Serial.print("\t Left Sensor Reading : ");
  // Serial.print(resultArray[0]);
  // Serial.print("\t Center Sensor Reading : ");
  // Serial.print(resultArray[1]);
  // Serial.print("\t Right Sensor Reading : ");
  // Serial.println(resultArray[2]);
  // Serial.print("\t Data from AWS : ");

  // Delay before the next iteration
  delay(10);  // Adjust the delay as needed
}

void taskOne( void * parameter )
{
    for( ;; )
    { 
        //Run rover in forward direction
        //Serial.println("x coordinate");
        Serial.println("RX: " + String(rx) + ", RY: " + String(ry) + ", RA: " + String(ra) + ", TX: " + String(tx) + ", TY: " + String(ty));
        // Pause the task again for 5000ms
       if((ra <= 45) || (ra >= 315)){

        // if((ra <= 20) || (ra >= 340)){
          if ((ty - ry) > abs(rx - tx)) {
        if((ry < ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39) && (i == 0)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("1st case 0 degree - Forward");
        }
          }
        
        else {if ((rx > tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("1st case 0 degree - Right");
        }
        else if ((rx < tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("1st case 0 degree - Left");
        }}
        if( ((ry > 415) || (rx > 415)) && (i == 0)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("1st case 0 degree - Backward");
        }
        if(((ry < 39) || (rx < 39)) && (i == 0)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("1st case 0 degree - Forward");
        }
       //}
      //  else {
      //   if((ry > 415) || (rx > 415)) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("1st case 0 degree - Backward");
      //   }
      //   else if ((rx > tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("1st case 0 degree - Right   2");
      //   }
      //   else if ((rx < tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("1st case 0 degree - Left   2");
      //   }
      //   if((ry < 39) || (rx < 39) ) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("1st case 0 degree - Forward");
      //   }
      //  }
       }


       else if((ra < 135) && (ra > 45)){
        // if((ra < 110) && (ra > 70)){
          if ((tx - rx) > abs(ry - ty)) {
        if((rx < tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("2nd case 90 degree - Forward");
        }}
        else {if ((ry < ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("2nd case 90 degree - Right");
        }
        else if ((ry > ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("2nd case 90 degree - Left");
        }}
       
        if(((ry < 39) || (rx > 415)) && (i == 0)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("2nd case 0 degree - Backward");
        }
        if(((ry > 415) || (rx < 39)) && (i == 0)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("2nd case 0 degree - Forward");
        
        }
      //  }
      //  else {
      //   if( (ry > 415) || (rx > 415)) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("1st case 0 degree - Backward");
      //   }
      //   else if ((ry < ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("2nd case 90 degree - Right   2");
      //   }
      //   else if ((ry > ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("2nd case 90 degree - Left   2");
      //   }
      //   if((ry < 39) || (rx < 39) ) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("1st case 0 degree - Forward");
      //   }
      //  }
      }


       else if((ra <= 225) && (ra >= 135)){
        // if((ra <= 200) && (ra >= 160)){
          if ((ry - ty) > abs(rx - tx)) {
        if((ry > ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("3rd case 180 degree - Forward");
        }}
        else {if ((rx < tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("3rd case 180 degree - Right");
        }
        else if ((rx > tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("3rd case 180 degree - Left");
        }}
        if((ry < 39)  || (rx < 39) || (ry > 415) || (rx > 415)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("3rd case 180 degree - Backward");
        }
      //  }
      //  else {
      //   if((ry < 39)  || (rx < 39) || (ry > 415) || (rx > 415)) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("3rd case 180 degree - Backward   2");
      //   }
      //   else if ((rx < tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("3rd case 180 degree - Right   2");
      //   }
      //   else if ((rx > tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("3rd case 180 degree - Left   2");
      //   }
      //  }
       }

       else if((ra < 315) && (ra > 225)){
        // if((ra < 290) && (ra > 250)){
          if ((rx - tx) > abs(ry - ty)) {
        if((rx > tx) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("4th case 270 degree - Forward");
        }}
        else {if ((ry > ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Forward,90);
        Serial.println("4th case 270 degree - Right");
        }
        else if ((ry < ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
        vTaskDelay(10);
        m.set_speed(MotorA,Forward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("4th case 270 degree - Left");
        }}
        if((ry < 39)  || (rx < 39) || (ry > 415) || (rx > 415)) {
        vTaskDelay(10);
        m.set_speed(MotorA,Backward,90);
        m.set_speed(MotorB,Backward,90);
        Serial.println("4th case 270 degree - Backward");
        }
      //  }
      //  else {
      //    if((ry < 39)  || (rx < 39) || (ry > 415) || (rx > 415)) {
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("4th case 270 degree - Backward   2");
      //   }
      //   else if ((ry > ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Backward,90);
      //   m.set_speed(MotorB,Forward,90);
      //   Serial.println("4th case 270 degree - Right   2");
      //   }
      //   else if ((ry < ty) && (ry < 415)  && (rx < 415) && (ry > 39) && (rx > 39)){
      //   vTaskDelay(10);
      //   m.set_speed(MotorA,Forward,90);
      //   m.set_speed(MotorB,Backward,90);
      //   Serial.println("4th case 270 degree - Left   2");
      //   }
      //  }
       }

       if((tx == 405) && (ty == 293)  && (ry > 270) && (ry < 315) && (rx > 370) && (rx < 425)) {
        m.set_speed(MotorA,Backward,0);
        m.set_speed(MotorB,Backward,0);
        i = 1;
        Serial.println("Target reached");
       }

      



       


    }
    

}
 
void taskTwo( void * parameter)
{
    //create an endless loop so the task executes forever
    for( ;; )
    { {
        //Run rover in forward direction
        m.set_speed(MotorA,Forward,255);
        m.set_speed(MotorB,Forward,255); 
        Serial.println("Running Task 2");
        // Pause the task again for 5000ms
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        //Run rover in Backward direction
	      m.set_speed(MotorA,Backward,255);
        m.set_speed(MotorB,Backward,255);
        Serial.println("Running Task 2");
        // Pause the task again for 5000ms
	      vTaskDelay(5000 / portTICK_PERIOD_MS); 
      } 

    }
    Serial.println("Ending task 2"); //should not reach this point but in case...
    vTaskDelete( NULL );
}


void taskThree( void * parameter)
{
    //create an endless loop so the task executes forever
    for( ;; )
    {
      int16_t *resultArray = s.reading();
      if (resultArray[0]<240 || resultArray[1]<260 || resultArray[2]<240 ) {
        //stop the rover
        m.set_speed(MotorA,Forward,125);
        m.set_speed(MotorB,Forward,125);
        Serial.println("Running Task 3");
        //delay(10); 
      }  
  
      else if (resultArray[0]<140 || resultArray[1]<160 || resultArray[2]<140 ) {
        //stop the rover
        m.set_speed(MotorA,Backward,0);
        m.set_speed(MotorB,Forward,0); 
        Serial.println("Running Task 3");
        //delay(10); 
      }  

    }
    Serial.println("Ending task 3"); //should not reach this point but in case...
    vTaskDelete( NULL );
}
