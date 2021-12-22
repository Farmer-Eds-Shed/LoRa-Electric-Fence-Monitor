#define MY_DEBUG
#define MY_RADIO_RFM95
#define MY_DEBUG_VERBOSE_RFM95
#define MY_RFM95_RST_PIN 4
#define MY_RFM95_CS_PIN 8
#define MY_RFM95_IRQ_PIN 7
#define MY_RFM95_IRQ_NUM digitalPinToInterrupt(7)
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)

#define MY_NODE_ID 83

#include <MySensors.h>


uint32_t SLEEP_TIME = 120000; // Sleep time between reports (in milliseconds)
#define DIGITAL_INPUT_SENSOR 3   // The digital input you attached your motion sensor.  (Only 2 and 3 generates interrupt!)
#define CHILD_ID 1   // Id of the sensor child

// Initialize motion message
MyMessage msg(CHILD_ID, V_TRIPPED);

void setup()
{
    pinMode(DIGITAL_INPUT_SENSOR, INPUT);      // sets the motion sensor digital pin as input
}

void presentation()
{
    // Send the sketch version information to the gateway and Controller
    sendSketchInfo("Motion Sensor", "1.0");

    // Register all sensors to gw (they will be created as child devices)
    present(CHILD_ID, S_MOTION);
}

void loop()
{

    int i =10;
    while (i > 0) {
      // Read digital motion value
      bool tripped = digitalRead(DIGITAL_INPUT_SENSOR) == HIGH;
      i--;
      Serial.println(tripped);
      send(msg.set(tripped?"1":"0"));  // Send tripped value to gw
      sleep(digitalPinToInterrupt(DIGITAL_INPUT_SENSOR), CHANGE, SLEEP_TIME);
    }
    

    // Sleep until interrupt comes in on motion sensor. Send update every two minute.
   sleep(SLEEP_TIME);
}
