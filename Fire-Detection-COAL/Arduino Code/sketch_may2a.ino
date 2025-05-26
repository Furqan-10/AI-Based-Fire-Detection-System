#define THERMISTORPIN A0

void setup() {
  Serial.begin(9600);
  pinMode(THERMISTORPIN, INPUT);
}

void loop() {
  int rawValue = analogRead(THERMISTORPIN);
  
  // Shortened Steinhart-Hart formula (1 line)
 float temperature = 1.0 / (log(1023.0 / rawValue - 1) * -0.000253 + 0.003354) - 273.15;
  
  Serial.println(temperature, 1);
  delay(4000);
}