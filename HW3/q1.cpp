/*
File: q1.cpp
Triggered when a specific CAN frame is received
    Analog read PIN_PC0,
    Send the reading over CAN.
While this happens, make an LED turn on to indicate activity.
    This LED is connected to PIN_PD2.
The CAN frames are received and sent via an MCP2515 CAN controller.
    It is connected via SPI with CS on PIN_PB2.
    The crystal is 20MHz and the CAN speed is 500kbps.
*/

// include the necessary libraries
#include <Arduino.h>
#include <mcp2515.h>

// create MCP2515 object
/* todo 1 */

MCP2515 canMotor(PIN_PB2);
// define pin constants


void setup() {
    // set the pinMode on the input pin
    /* todo 1 */

    pinMode(PIN_PC0, INPUT);

    // set the pinMode on the LED pin
    /* todo 1 */

    pinMode(PIN_PD2, OUTPUT);

    // initialize the CAN controller at 500kbps
    /* todo 1 */

    canMotor.reset();
    canMotor.setBitrate(CAN_500KBPS, MCP_20MHZ);
    canMotor.setNormalMode();

}

void loop() {
    // create CAN frame objects
    // make one for receiving, another for transmitting

    struct can_frame rxFrame;
    struct can_frame txFrame;
    /* todo 2 */

    // check if a CAN frame is received
    if (/* todo 2 */ canMotor.readMessage(&rxFrame) == MCP2515::ERROR_OK) {
        // check if the received frame is of ID 0x420 and first data byte is 0x69
        if (/* todo 2 */ rxFrame.can_id == 0x420 && rxFrame.data[0] == 0x69) {
            // turn on the LED to indicate activity
            /* todo 3 */

            digitalWrite(PIN_PB2, HIGH);

            // read the analog value from the input pin and store it as a variable
            /* todo 3 */
            
            int analogValue = analogRead(PIN_PC0);

            // prepare the CAN frame to send
            txFrame.can_id = 0x690; // replace with desired send ID
            txFrame.can_dlc = 2; // data length code
            txFrame.data[0] = (analogValue >> 8) & 0xFF; // high byte
            txFrame.data[1] = analogValue & 0xFF; // low byte

            // send the CAN frame
            /* todo 3 */

            canMotor.sendMessage(&txFrame);

            // turn off the LED after sending
            /* todo 3 */

            digitalWrite(PIN_PB2, LOW);
            
        }
    }
}