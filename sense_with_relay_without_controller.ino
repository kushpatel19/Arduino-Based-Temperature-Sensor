// Group-A3

// Imp note:
// If sensor temp > base_temp then turn on the peltier and vice versa
// If relay on peltier on, if relay off peltier off.
// We shall control the relay using 0,1 from the aurdino.


// variables and definitions

//Important parameter, set to match environment
int baselineTemp = 10;
float celsius = 0;
float fahrenheit = 0;
#define thermistorPin A0
#define relay 10
// int relay=13;



void setup()
{
  pinMode(A0, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  // pinMode(2, OUTPUT);
  // pinMode(3, OUTPUT);
  // pinMode(4, OUTPUT);
}

void loop()
{
  // set threshold temperature to activate LEDs
  // Serial.println(digitalRead(3));
  baselineTemp = 10;
  // measure temperature in Celsius
  // celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  celsius = (1-analogRead(thermistorPin)*5/1024.0)*100;
   // convert to Fahrenheit
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  if (celsius < baselineTemp) {
      // digitalWrite(2, LOW);
      // digitalWrite(3, LOW);
      // digitalWrite(4, LOW);
      digitalWrite(relay, 1);
    }
  
  if (celsius >= baselineTemp) {
      // digitalWrite(2, HIGH);
      // digitalWrite(3, LOW);
      // digitalWrite(4, LOW);
      digitalWrite(relay, 0);
    }

  delay(1000); // Wait for 1000 millisecond(s)
}
