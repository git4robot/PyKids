const int IN1 = 6, IN2 = 9, IN3 = 11, IN4 = 10;
const int enable12 = 5 , enable34 = 8;
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enable12, OUTPUT);
  pinMode(enable34, OUTPUT);
  digitalWrite(enable12, HIGH);
  digitalWrite(enable34, HIGH);
}

void loop()
{
  clockwise();
  delay(3000);
  anticlockwise();
  delay(3000);
  brake();
  delay(3000);
}
// Input state to rotate 2 motors CW
void clockwise()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// Input state to rotate 2 motors CCW
void anticlockwise()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
//Motor Brake
void brake()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
