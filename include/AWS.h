/**
 * @file
 * 
 * ESP32 AWS Library
 * 
 * Functions to get the crawler coordinates from the Camera over AWS IoT
 * 
 * Authors: Vipul Deshpande, Jaime Burbano
 */

#ifndef aws_h
#define aws_h

#include <MQTTClient.h>
extern String value;
extern int rx; // Declare x as extern
extern int ry; // Declare y as extern
extern int ra; // Declare y as extern
extern int tx; // Declare x as extern
extern int ty; // Declare y as extern


void messageHandler(String, String);
class myawsclass {
  public:
    myawsclass();

    void connectAWS();                            /* Initialize and connect to AWS */
    void publishMessage(int16_t sensorValue);     /* Publish the values of the sensors */
    void stayConnected();                         /* Maintain the connection */
};

extern myawsclass awsobject;

#endif