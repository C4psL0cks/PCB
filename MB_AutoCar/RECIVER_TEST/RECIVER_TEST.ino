double Setpoint;
int CH1, CH2, CH3, CH4;

void setup() {

  Serial.begin(115200);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);

}

void loop() {

  Setpoint = pulseIn(A8, HIGH, 250000);
  CH1 = pulseIn(A9, HIGH, 250000);
  CH2 = pulseIn(A10, HIGH, 250000);
  CH3 = pulseIn(A11, HIGH, 250000);
  CH4 = pulseIn(A12, HIGH, 250000);

  Serial.println(Setpoint);
  Serial.println(CH1);
  Serial.println(CH2);
  Serial.println(CH3);
  Serial.println(CH4);

}
