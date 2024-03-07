const int lm35_pin = A1;  /* LM35 O/P pin */
// Fan = 11
// Humidifier = 6

void setup() {
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  float temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);  
  temp_val = (temp_adc_val * 4.88); 
  temp_val = (temp_val/10); 
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  if (temp_val < 10)  {
    Serial.print("Thanda\n");
    digitalWrite(6, LOW);
    digitalWrite(11, LOW);
    }
  else{
     Serial.print("Shei Gorom\n");
     digitalWrite(6, HIGH);
     digitalWrite(11, HIGH);
    }
  delay(1000);
}
