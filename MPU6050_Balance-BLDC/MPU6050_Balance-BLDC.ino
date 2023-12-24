// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Servo.h>

Servo ESC;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
#define myPwm 9
int pwmValue;

void setup() {
    pinMode(myPwm, OUTPUT);
//    ESC.attach(9);
    ESC.attach(9,100,2000); // (pin, min pulse width, max pulse width in microseconds) 
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

//    My edit
//    accelgyro.setXGyroOffset(220);
//    accelgyro.setYGyroOffset(76);
//    accelgyro.setZGyroOffset(-85);
//    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
//        Serial.print("a/g:\t");
//        Serial.print(ax); Serial.print("\t");
//        Serial.print(ay); Serial.print("\t");
//        Serial.print(az); Serial.print("\t");
//        Serial.print(gx); Serial.print("\t");
//        Serial.print(gy); Serial.print("\t");
//        Serial.println(gz);
        Serial.print("ay = "); Serial.println(ay);
//        delay(100);

        // BALANCE
        int upLimit = 2500;
        int downLimit = -1000;
        pwmValue = 180;
        if (ay >= downLimit) {
          ESC.write(pwmValue);    // Send the signal to the ESC
          delay(80);
        } else if(ay >= upLimit) {
          ESC.write(64);
          delay(80);
        }
//        Serial.print("======== AY =================");
//        Serial.println(ay);

    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
