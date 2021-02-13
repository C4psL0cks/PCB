#include <PID_v1.h>

// REALY
#define IN1_ON_OFF        5
#define IN2_FONT_BACK     4
#define IN3_SELECTER      3
#define IN4_PWM_SPEED     2

// SPEED / BREAK
#define PWM_SPEED         11
#define SN_BREAK          13

// STEERING
#define PWM_STEERING      6
#define IN2_STEERING      7
#define IN1_STEERING      8

// BREAK
#define PWM_BREAK         9
#define IN2_BREAK         10
#define IN1_BREAK         11

// SETTING
#define LOWER_LEFT_RIGHT  1000
#define UPPER_LEFT_RIGHT  1900

//(1003,1490)
#define LOWER_BREAK       1010
#define UPPER_BREAK       1490

//(1019,1974)
#define LOWER_SPEED       1020
#define UPPER_SPEED       1970

//(995,1989)
#define LOWER_ON_OFF      1000
#define UPPER_ON_OFF      1980

//(995,1989)
#define LOWER_FRONT_BACK  1000
#define UPPER_FRONT_BACK  1980

// ENCODER
#define EN_BROW           23
#define EN_RED            25
#define EN_ORANGE         27
#define EN_YELLOW         29
#define EN_BLUE           31
#define EN_PURPLE         33
#define EN_GREY           37
#define EN_WHITE_BROW     39
#define EN_WHITE_RED      41
#define EN_WHITE_ORANGE   43
#define EN_WHITE_YELLOW   45
#define EN_WHITE_BLUE     47
#define EN_WHITE_PURPLE   49


double Setpoint, Feedback, Output, Kp = 5, Ki = 0, Kd = 0;
int SUM, EN0 = 0, EN1 = 0, EN2 = 0, EN3 = 0, EN4 = 0, EN5 = 0, EN6 = 0, EN7 = 0, EN8 = 0, EN9 = 0, EN10 = 0, EN11 = 0, EN12 = 0;
PID myPID(&Feedback, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// REMOTE
int CH1_LEFT_RIGHT, CH2_BREAK, CH3_SPEED, CH5_ON_OFF, CH6_FRONT_BACK;

void setup() {

  Serial.begin(115200);

  // REALY
  pinMode(IN1_ON_OFF, OUTPUT);
  pinMode(IN2_FONT_BACK, OUTPUT);
  pinMode(IN3_SELECTER, OUTPUT);
  pinMode(IN4_PWM_SPEED, OUTPUT);

  // SPEED / BREAK
  pinMode(PWM_SPEED, OUTPUT);
  pinMode(SN_BREAK, INPUT);

  // STEERING
  pinMode(PWM_STEERING, OUTPUT);
  pinMode(IN2_STEERING, OUTPUT);
  pinMode(IN1_STEERING, OUTPUT);

  // BREAK
  pinMode(PWM_BREAK, OUTPUT);
  pinMode(IN2_BREAK, OUTPUT);
  pinMode(IN1_BREAK, OUTPUT);

  // REMOTE
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);

  // ENCODER
  pinMode(EN_BROW, INPUT_PULLUP);
  pinMode(EN_RED, INPUT_PULLUP);
  pinMode(EN_ORANGE, INPUT_PULLUP);
  pinMode(EN_YELLOW, INPUT_PULLUP);
  pinMode(EN_BLUE, INPUT_PULLUP);
  pinMode(EN_PURPLE, INPUT_PULLUP);
  pinMode(EN_GREY, INPUT_PULLUP);
  pinMode(EN_WHITE_BROW, INPUT_PULLUP);
  pinMode(EN_WHITE_RED, INPUT_PULLUP);
  pinMode(EN_WHITE_ORANGE, INPUT_PULLUP);
  pinMode(EN_WHITE_YELLOW, INPUT_PULLUP);
  pinMode(EN_WHITE_BLUE, INPUT_PULLUP);
  pinMode(EN_WHITE_PURPLE, INPUT_PULLUP);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-150, 150);

}

void loop() {

  CH1_LEFT_RIGHT = pulseIn(A8, HIGH, 250000); // left 1039 / center 1515 / right 1989
  CH2_BREAK = pulseIn(A9, HIGH, 250000); // center 1496 / down 1004
  CH3_SPEED = pulseIn(A10, HIGH, 250000); // down 1018 / up 1971
  CH5_ON_OFF = pulseIn(A11, HIGH, 250000); // on 995 / off 1989
  CH6_FRONT_BACK = pulseIn(A12, HIGH, 250000); // f 995 b 1989

  //  Serial.println("-------------------------------");
  //  Serial.println("CH1_LEFT_RIGHT: " + String(CH1_LEFT_RIGHT));
  //  Serial.println("CH2_BREAK: " + String(CH2_BREAK));
  //  Serial.println("CH3_SPEED: " + String(CH3_SPEED));
  //  Serial.println("CH5_ON_OFF: " + String(CH5_ON_OFF));
  //  Serial.println("CH6_FRONT_BACK: " + String(CH6_FRONT_BACK));
  //  Serial.println("-------------------------------");

  // L / R
  CH1_LEFT_RIGHT = constrain(CH1_LEFT_RIGHT, LOWER_LEFT_RIGHT , UPPER_LEFT_RIGHT);
  //  Serial.println("CH1_LEFT_RIGHT: " + String(CH1_LEFT_RIGHT));
  CH1_LEFT_RIGHT = map(CH1_LEFT_RIGHT, LOWER_LEFT_RIGHT , UPPER_LEFT_RIGHT, 80, 980);

  // BREAK
  CH2_BREAK = constrain(CH2_BREAK, LOWER_BREAK , UPPER_BREAK);
  //  Serial.println("CH2_BREAK: " + String(CH2_BREAK));
  Serial.println(digitalRead(SN_BREAK)); // defualt 0 run 1

  //PWM   IN1   IN2  การทำงานมอเตอร์ (มอเตอร์)
  //0 (Low) x x มอเตอร์หยุดหมุนโดยอาศัยแรงเฉื่อย (Slow Stop)
  //1(High) 0 0 มอเตอร์หยุดหมุนแบบรวดเร็ว (Fast Stop or Break)
  //1(High) 0 1 มอเตอร์หมุนทางซ้าย
  //1(High) 1 0 มอเตอร์หมุนทางขวา
  //1(High) 1 1 มอเตอร์หยุดหมุนแบบรวดเร็ว (Fast Stop or Break

  if (CH2_BREAK > 1200 && digitalRead(SN_BREAK) == 0) {
    Serial.println("Normal");
    analogWrite(PWM_BREAK, 0);
    digitalWrite(IN1_BREAK , LOW);
    digitalWrite(IN2_BREAK , LOW);
  }
  // หมุนดึง
  if (CH2_BREAK < 1200) {
    Serial.println("RUN");
    analogWrite(PWM_BREAK, map(CH2_BREAK, 1200, 1000, 0, 120));
    digitalWrite(IN1_BREAK , LOW);
    digitalWrite(IN2_BREAK , HIGH);
  }
  // หมุนปล่อย
  if (CH2_BREAK > 1200 && digitalRead(SN_BREAK) == 1) {
    Serial.println("STOP BREAK");
    analogWrite(PWM_BREAK, 80);
    digitalWrite(IN1_BREAK , HIGH);
    digitalWrite(IN2_BREAK , LOW);
  }

  // SPEED
  CH3_SPEED = constrain(CH3_SPEED, LOWER_SPEED , UPPER_SPEED);
  //  Serial.println("CH3_SPEED: " + String(CH3_SPEED));
  CH3_SPEED = map(CH3_SPEED, LOWER_SPEED , UPPER_SPEED, 0, 255);
  analogWrite(PWM_SPEED, CH3_SPEED);

  // ON / OFF
  CH5_ON_OFF = constrain(CH5_ON_OFF, LOWER_ON_OFF , UPPER_ON_OFF);
  //  Serial.println("CH5_ON_OFF: " + String(CH5_ON_OFF));
  CH5_ON_OFF = map(CH5_ON_OFF, LOWER_ON_OFF , UPPER_ON_OFF, 0, 1);
  digitalWrite(IN1_ON_OFF, CH5_ON_OFF);
  digitalWrite(IN3_SELECTER, HIGH);

  // FRONT / BACK
  CH6_FRONT_BACK = constrain(CH6_FRONT_BACK, LOWER_FRONT_BACK , UPPER_FRONT_BACK);
  //  Serial.println("CH6_FRONT_BACK: " + String(CH6_FRONT_BACK));
  CH6_FRONT_BACK = map(CH6_FRONT_BACK, LOWER_FRONT_BACK , UPPER_FRONT_BACK, 0, 1);
  digitalWrite(IN2_FONT_BACK, CH6_FRONT_BACK);

  Serial.println(CH1_LEFT_RIGHT);
  Serial.println(CH2_BREAK);
  Serial.println(CH3_SPEED);
  Serial.println(CH5_ON_OFF);
  Serial.println(CH6_FRONT_BACK);

  EN0 = digitalRead(EN_BROW)           * 1;
  EN1 = digitalRead(EN_RED)            * 2;
  EN2 = digitalRead(EN_ORANGE)         * 4;
  EN3 = digitalRead(EN_YELLOW)         * 8;
  EN4 = digitalRead(EN_BLUE)           * 10;
  EN5 = digitalRead(EN_PURPLE)         * 20;
  EN6 = digitalRead(EN_GREY)           * 40;
  EN7 = digitalRead(EN_WHITE_BROW)     * 80;
  EN8 = digitalRead(EN_WHITE_RED)      * 100;
  EN9 = digitalRead(EN_WHITE_ORANGE)   * 200;
  EN10 = digitalRead(EN_WHITE_YELLOW)  * 400;
  EN11 = digitalRead(EN_WHITE_BLUE)    * 800;
  EN12 = digitalRead(EN_WHITE_PURPLE)  * 1000;

  SUM = EN0 + EN1 + EN2 + EN3 + EN4 + EN5 + EN6 + EN7 + EN8 + EN9 + EN10 + EN11 + EN12;
  Feedback = SUM % 1000;
  double error = Setpoint - Feedback;

  Serial.println(error);

  delay(300);

}
