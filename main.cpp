#include "vex.h"

using namespace vex;

brain Brain;
controller Controller1 = controller(primary);

motor LeftFront  = motor(PORT2, ratio18_1, false);
motor LeftRear   = motor(PORT3, ratio18_1, false);
motor RightFront = motor(PORT4, ratio18_1, true);
motor RightRear  = motor(PORT5, ratio18_1, true);

int main() {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(1, 1, "VEX Override 2026/27 Tank Drive");

    int driveSpeed = 50;
    bool dpadPressed = false;

    while (true) {
        if (Controller1.ButtonRight.pressing()) {
            if (!dpadPressed) {
                driveSpeed += 10;
                if (driveSpeed > 100) driveSpeed = 100;
                dpadPressed = true;
            }
        }
        else if (Controller1.ButtonLeft.pressing()) {
            if (!dpadPressed) {
                driveSpeed -= 10;
                if (driveSpeed < 0) driveSpeed = 0;
                dpadPressed = true;
            }
        }
        else {
            dpadPressed = false;
        }

        int leftStick  = Controller1.Axis3.position(percent);
        int rightStick = Controller1.Axis2.position(percent);

        int leftPower  = (leftStick  * driveSpeed) / 100;
        int rightPower = (rightStick * driveSpeed) / 100;

        LeftFront.spin(fwd, leftPower,  pct);
        LeftRear.spin(fwd,  leftPower,  pct);
        RightFront.spin(fwd, rightPower, pct);
        RightRear.spin(fwd,  rightPower, pct);

        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("Speed: %d%%  L:%d  R:%d", driveSpeed, leftPower, rightPower);

        wait(20, msec);
    }
}