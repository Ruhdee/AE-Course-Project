#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int right_button = 3;
const int select_button = 2;
const int OhmMeter = A0;
const int CapacitancMeter = A1;
const int VoltMeter = A2;
const int Ammeter = A3;
const int R3 = 6;
const int R2 = 5;
const int R1 = 4;
const int ChargePin = 13;
const int DischargePin = 11;
boolean is_select = false;
int navigator = 0;
int flag = 0;
float R = 0.00;
float V = 0.00;
float I = 0.00;
float C = 0.00;
boolean nano = false;
boolean kilo = false;
boolean mili = false;

void calculate_resistor() {
  float v_ref = 4.94;
  float r1 = 0.00;
  float r_ref1 = 215.00;
  float adc_value1 = 0.00;
  float voltage1 = 0.00;
  float r2 = 0.00;
  float r_ref2 = 968.00;
  float adc_value2 = 0.00;
  float voltage2 = 0.00;
  float r3 = 0.00;
  float r_ref3 = 9630.00;
  float adc_value3 = 0.00;
  float voltage3 = 0.00;
  pinMode(R1, OUTPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  digitalWrite(R1, HIGH);
  for (int i = 0; i < 20; i++) {

    adc_value1 = adc_value1 + analogRead(OhmMeter);
    delay(3);
  }
  adc_value1 = adc_value1 / 20;

  if (adc_value1 < 1022.90)

  {

    voltage1 = ((adc_value1 * v_ref) / 1024);

    r1 = (voltage1 * r_ref1) / (v_ref - voltage1);
  }



  pinMode(R1, INPUT);

  pinMode(R2, OUTPUT);

  pinMode(R3, INPUT);

  digitalWrite(R2, HIGH);

  for (int i = 0; i < 20; i++)

  {

    adc_value2 = adc_value2 + analogRead(OhmMeter);

    delay(3);
  }

  adc_value2 = adc_value2 / 20;

  if (adc_value2 < 1022.90)

  {

    voltage2 = ((adc_value2 * v_ref) / 1024);

    r2 = (voltage2 * r_ref2) / (v_ref - voltage2);
  }



  pinMode(R1, INPUT);

  pinMode(R2, INPUT);

  pinMode(R3, OUTPUT);

  digitalWrite(R3, HIGH);

  for (int i = 0; i < 20; i++)

  {

    adc_value3 = adc_value3 + analogRead(OhmMeter);

    delay(3);
  }

  adc_value3 = adc_value3 / 20;

  if (adc_value3 < 1022.90)

  {

    voltage3 = ((adc_value3 * v_ref) / 1024);

    r3 = (voltage3 * r_ref3) / (v_ref - voltage3);
  }



  r1 = r1 / 1000;

  r2 = r2 / 1000;

  r3 = r3 / 1000;


  // if (r1 > 10 && r1 < 500) {
  //   R = r1;  // 215Ω is accurate in this range
  // } else if (r2 >= 500 && r2 < 2500) {
  //   R = r2;  // 968Ω is best here
  // } else if (r3 >= 2500 && r3 < 100000) {
  //   R = r3;  // 9630Ω for high resistance
  // } else {
  //   R = 0.00;  // Out of range or error
  // }


  if (r1 < 0.5 && r2 < 2.5 && r3 < 100) R = r1 ;

  else if (r1 > 0.5 && r2 < 2.5 && r3 < 100) R = r2;

  else if (r1 > 0.5 && r2 > 2.5 && r3 < 100) R = r3;

  else R = 0.00;



  if (R < 1)

  {

    R = R * 1000;

    kilo = false;

  }

  else

  {

    kilo = true;
  }
}



void calculate_capacitance() {

  unsigned long start_time;

  unsigned long elapsed_time;

  float microFarads;

  float nanoFarads;

  float r_ref = 9720.00;



  digitalWrite(ChargePin, HIGH);

  start_time = millis();



  while (analogRead(CapacitancMeter) < 647) {}



  elapsed_time = millis() - start_time;



  microFarads = ((float)elapsed_time / r_ref) * 1000;

  if (microFarads > 1)

  {

    C = microFarads;

    nano = false;

  }

  else

  {

    nanoFarads = microFarads * 1000.0;

    C = nanoFarads;

    nano = true;
  }





  digitalWrite(ChargePin, LOW);

  pinMode(DischargePin, OUTPUT);

  digitalWrite(DischargePin, LOW);

  while (analogRead(CapacitancMeter) > 0) {}

  pinMode(DischargePin, INPUT);
}



void calculate_voltage() {

  float R1 = 2170.00;

  float R2 = 973.00;

  float v_ref = 4.94;

  float resistor_ratio = 0.00;

  float adc_value = 0.00;

  float voltage = 0.00;



  resistor_ratio = (R2 / (R1 + R2));

  for (int i = 0; i < 20; i++)

  {

    adc_value = adc_value + analogRead(VoltMeter);

    delay(3);
  }

  adc_value = adc_value / 20;

  voltage = ((adc_value * v_ref) / 1023);



  V = voltage / resistor_ratio;
}



void calculate_current() {

  int sensitivity = 185;

  int adc_value = 0;

  float v_ref = 4.94;

  float voltage = 0.00;

  float pure_voltage = 0.00;

  float offset_voltage = 2.47;



  for (int i = 0; i < 40; i++)

  {

    adc_value = adc_value + analogRead(Ammeter);

    delay(2);
  }

  adc_value = adc_value / 40;

  voltage = ((adc_value * v_ref) / 1024);

  pure_voltage = voltage - offset_voltage;

  pure_voltage = pure_voltage * 1000;

  I = pure_voltage / sensitivity;



  if (I < 1)

  {

    I = I * 1000;

    mili = true;

  }

  else

  {

    mili = false;
  }
}
void setup() {

  Serial.begin(9600);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(select_button, INPUT_PULLUP);
  pinMode(ChargePin, OUTPUT);
  digitalWrite(ChargePin, LOW);

  lcd.init();
  lcd.backlight();
}
void loop() {
  static bool rightPressed = false;
  static bool selectPressed = false;

  if (digitalRead(right_button) == LOW && !rightPressed && !is_select) {
    rightPressed = true;
    navigator++;
    if (navigator > 3) navigator = 0;
  }

  if (digitalRead(right_button) == HIGH && rightPressed) {
    rightPressed = false;
  }

  if (digitalRead(select_button) == LOW && !selectPressed) {
    selectPressed = true;
    is_select = !is_select;  // Toggle mode
  }

  if (digitalRead(select_button) == HIGH && selectPressed) {
    selectPressed = false;
  }

  if (is_select) {
    lcd.clear();
    switch (navigator) {
      case 0:  // Resistor
        calculate_resistor();
        lcd.setCursor(0, 0);
        lcd.print("Resistor:");
        lcd.setCursor(0, 1);
        lcd.print(R);
        if (kilo) lcd.print("k Ohm");
        else lcd.print(" Ohm");
        break;

      case 1:  // Voltage
        calculate_voltage();
        lcd.setCursor(0, 0);
        lcd.print("Voltage:");
        lcd.setCursor(0, 1);
        lcd.print(V);
        lcd.print(" V");
        break;

      case 2:  // Current
        calculate_current();
        lcd.setCursor(0, 0);
        lcd.print("Current:");
        lcd.setCursor(0, 1);
        lcd.print(I);
        if (mili) lcd.print(" mA");
        else lcd.print(" A");
        break;

      case 3:  // Capacitance
        calculate_capacitance();
        lcd.setCursor(0, 0);
        lcd.print("Capacitance:");
        lcd.setCursor(0, 1);
        lcd.print(C);
        if (nano) lcd.print(" nF");
        else lcd.print(" uF");
        break;
    }

    delay(1000);  // Refresh rate in select mode
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (navigator) {
      case 0: lcd.print("> Resistor"); break;
      case 1: lcd.print("> Voltage"); break;
      case 2: lcd.print("> Current"); break;
      case 3: lcd.print("> Capacitor"); break;
    }
    delay(250);
  }
}
