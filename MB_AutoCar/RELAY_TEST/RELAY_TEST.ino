#define IN1_ON_OFF        5
#define IN2_FONT_BACK     4
#define IN3_SELECTER      3
#define IN4_PWM_SPEED     2

void setup() {

  Serial.begin(115200);
  pinMode(IN1_ON_OFF, OUTPUT);
  pinMode(IN2_FONT_BACK, OUTPUT);
  pinMode(IN3_SELECTER, OUTPUT);
  pinMode(IN4_PWM_SPEED, OUTPUT);
  digitalWrite(IN1_ON_OFF, HIGH);
  digitalWrite(IN2_FONT_BACK, HIGH);
  digitalWrite(IN3_SELECTER, HIGH);
  digitalWrite(IN4_PWM_SPEED, HIGH);
  delay(1000);
  digitalWrite(IN1_ON_OFF, LOW);
  digitalWrite(IN2_FONT_BACK, LOW);
  digitalWrite(IN3_SELECTER, LOW);
  digitalWrite(IN4_PWM_SPEED, LOW);

}

void loop() {

  digitalWrite(IN1_ON_OFF, HIGH);
  delay(1000);
  digitalWrite(IN2_FONT_BACK, HIGH);
  delay(1000);
  digitalWrite(IN3_SELECTER, HIGH);
  delay(1000);
  digitalWrite(IN4_PWM_SPEED, HIGH);
  delay(1000);
  digitalWrite(IN1_ON_OFF, LOW);
  delay(1000);
  digitalWrite(IN2_FONT_BACK, LOW);
  delay(1000);
  digitalWrite(IN3_SELECTER, LOW);
  delay(1000);
  digitalWrite(IN4_PWM_SPEED, LOW);
  delay(1000);

}
