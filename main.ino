// You can also follow values on the serial monitor in arduino ide.
const int pedalPin = A0;  // Analog pin for Pedal Pin
const int pwmPin = 9;   // (For PWM)

int current_data = 0;
int previous_data = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  current_data = analogRead(pedalPin);
  if (current_data >= 0) {
    if (current_data >= previous_data) {
      //Increase the value of previous data until it reaches the value of current data.
      while (previous_data <= current_data) {
        current_data = analogRead(pedalPin);

        previous_data += 25;
        previous_data = constrain(previous_data, 10, 1030);

        int pwmValue = map(previous_data, 0, 1023, 1, 255);
        analogWrite(pwmPin, pwmValue);
        Serial.print("PWM Value: ");
        Serial.println(pwmValue);

        delay(50);
      }
    }

    else if (current_data < previous_data) {
      // Decrease the value of current data until it reaches the value of previous data.
      while (previous_data > current_data) {
        previous_data -= 15;
        current_data = analogRead(pedalPin);

        int pwmValue = map(previous_data, 0, 1023, 1, 255);
        analogWrite(pwmPin, pwmValue);
        Serial.print("PWM Value: ");
        Serial.println(pwmValue);
        delay(15);
      }
    }
  }
}
