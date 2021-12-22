#define MY_DEBUG
#define MY_RADIO_RFM95
#define MY_DEBUG_VERBOSE_RFM95
#define MY_RFM95_RST_PIN 4
#define MY_RFM95_CS_PIN 8
#define MY_RFM95_IRQ_PIN 7
#define MY_RFM95_IRQ_NUM digitalPinToInterrupt(7)
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)

#define MY_NODE_ID 84

#include <MySensors.h>
#include <Arduino.h>


uint32_t SLEEP_TIME = 30000; // Sleep time between reports (in milliseconds)

#define CHILD_ID_LIGHT 0
#define LIGHT_SENSOR_ANALOG_PIN 0

MyMessage msg(CHILD_ID_LIGHT, V_LIGHT_LEVEL);
int lastLightLevel;
// EMF

int aVal=0;
int VL=0;




void presentation()
{
    // Send the sketch version information to the gateway and Controller
    sendSketchInfo("EMF Sensor", "1.0");

    // Register all sensors to gateway (they will be created as child devices)
    present(CHILD_ID_LIGHT, S_LIGHT_LEVEL);
}

void loop()
{
    aVal=analogRead(LIGHT_SENSOR_ANALOG_PIN);
   // if (aVal > 1 ) {
        VL=map(aVal,1,100,1,255);
        Serial.println(VL);
        send(msg.set(VL));
  //  } 

    

    // Sleep until interrupt comes in on motion sensor. Send update every two minute.
   //sleep(SLEEP_TIME);
}
