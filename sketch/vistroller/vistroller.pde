#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte count = 0;
int ledPin = 13;

void osdPrint(const char *str) {
    byte buf[] = {0x73, 0x00, 0x00, 0x00, 0xFF};
    Serial.write(buf, sizeof(buf)); // cmd
    Serial.write(str); // string
}

void osdPrintln(const char *str) {
    osdPrint(str);
    Serial.write("\n");
}

void setup() {
    Serial.begin(115200);

    // LED onboard.
    pinMode(ledPin, OUTPUT);

    // Initialize OLCD to display debug message.
    delay(500);
    Serial.write(0x55);

    // AutoBaud
    digitalWrite(ledPin, HIGH);
    count = 100;
    while (count) {
        if (Serial.available() > 0 && 0x06 == Serial.read()) {
            // AutoBaud set.
            digitalWrite(ledPin, LOW);
            break;
        }
        delay(10);
        count--;
    }

    if (count == 0) {
        // Failed to initialize.
        return;
    }

    //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

    error = ps2x.config_gamepad(7,9,8,6, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

    if(error == 0){
        osdPrintln("Found Controller, configured successful");
        osdPrintln("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        osdPrintln("holding L1 or R1 will print out the analog stick values.");
        osdPrintln("Go to www.billporter.info for updates and to report bugs.");
    }

    else if(error == 1)
        osdPrintln("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if(error == 2)
        osdPrintln("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        osdPrintln("Controller refusing to enter Pressures mode, may not support it. ");

    //osdPrint(ps2x.Analog(1), HEX);

    type = ps2x.readType();
    switch(type) {
    case 0:
        osdPrintln("Unknown Controller type");
        break;
    case 1:
        osdPrintln("DualShock Controller Found");
        break;
    case 2:
        osdPrintln("GuitarHero Controller Found");
        break;
    }
}

void loop() {
    /* You must Read Gamepad to get new values
       Read GamePad and set vibration values
       ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
       if you don't enable the rumble, use ps2x.read_gamepad(); with no values

       you should call this at least once a second
    */



    if(error == 1) //skip loop if no controller found
        return;

    if(type == 2){ //Guitar Hero Controller
    } else { //DualShock Controller

        ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed

        if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
            osdPrintln("Start is being held");
        if(ps2x.Button(PSB_SELECT))
            osdPrintln("Select is being held");


        if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
            osdPrint("Up held this hard: ");
        }
        if(ps2x.Button(PSB_PAD_RIGHT)){
            osdPrint("Right held this hard: ");
        }
        if(ps2x.Button(PSB_PAD_LEFT)){
            osdPrint("LEFT held this hard: ");
        }
        if(ps2x.Button(PSB_PAD_DOWN)){
            osdPrint("DOWN held this hard: ");
        }


        if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
        {



            if(ps2x.Button(PSB_L3))
                osdPrintln("L3 pressed");
            if(ps2x.Button(PSB_R3))
                osdPrintln("R3 pressed");
            if(ps2x.Button(PSB_L2))
                osdPrintln("L2 pressed");
            if(ps2x.Button(PSB_R2))
                osdPrintln("R2 pressed");
            if(ps2x.Button(PSB_GREEN))
                osdPrintln("Triangle pressed");

        }


        if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
            osdPrintln("Circle just pressed");

        if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
            osdPrintln("Square just released");

        if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
            osdPrintln("X just changed");
    }


    delay(50);

}
