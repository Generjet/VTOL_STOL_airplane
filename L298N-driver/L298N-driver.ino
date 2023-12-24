int myPwm = 9;
int in1 = 8;
int in2 = 7;
int in3 = 6;
int in4 = 5;
int potValue = 0;
void setup() {
  // put your setup code here, to run once:
    pinMode(myPwm, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    
}

void loop() {
  // put your main code here, to run repeatedly:
    potValue = analogRead(A0);
//    potValue = map(potValue, 0, 1023,0,255);
    analogWrite(myPwm, 255); // Send PWM signal to L298N Enable pin
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(400);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(300);

}
