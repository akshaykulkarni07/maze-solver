int a;
int b;
int c;
int d;
int e;
int f;

void setup() 
{
  // put your setup code here, to run once:
  // Motors
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // IR sensors
  // 0 i/p for white
  // 1 i/p for black
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
}

void loop()
{
  read_ir();
  // sharp left turn
  if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0)
  {
    stop_motors();
  }
  // sharp right turn
  else if (a == 1 && b == 1 && c == 0 && d == 0 && e == 0 && f == 0)
  {
    sharp_turn_right();
  }
  // reached dead end, take U-turn
  else if (a == 0 && b == 0 && c == 0 && d == 0)
  {
    sharp_turn_left();
  }
  // otherwise follow straight or curved path using proportional control
  else
  {
    motor_p_control();  
  }
}

void read_ir()
{
  // read IR input
  a = digitalRead(22);
  b = digitalRead(23);
  c = digitalRead(24);
  d = digitalRead(25);
  e = digitalRead(26);
  f = digitalRead(27);
}

void left(int spd)
{
  analogWrite(6, 0);
  analogWrite(7, spd);
  analogWrite(8, spd);
  analogWrite(9, 0);
}

void right(int spd)
{
  analogWrite(6, spd);
  analogWrite(7, 0);
  analogWrite(8, 0);
  analogWrite(9, spd);
}

void forward(int spd)
{
  analogWrite(6, spd);
  analogWrite(7, 0);
  analogWrite(8, spd);
  analogWrite(9, 0);
}

void stop_motors()
{
  analogWrite(6, 0);
  analogWrite(7, 0);
  analogWrite(8, 0);
  analogWrite(9, 0);
}

void motor_p_control()
{
  read_ir();
  // calculate proportional control error using weights as typed
  long int err = (-4 * a) + (-2 * b) + (2 * e) + (4 * f);

  // if err is positive, means line is under left side sensors
  if (err > 0)
  {
    // map and constrain the error to a range of 0 to 255
    // so that it can be applied to motor
    err = map(err, 0, 7, 0, 255);
    err = constrain(err, 0, 255);
    // go left
    analogWrite(6, 0);
    analogWrite(7, 0);
    analogWrite(8, err);
    analogWrite(9, 0);
  }
  // if negative, line under right side sensors
  else if (err < 0)
  {
    // map and constrain the error to a range of 0 to 255
    // so that it can be applied to motor
    err = -err;
    err = map(err, 0, 7, 0, 255);
    err = constrain(err, 0, 255);
    // go right
    analogWrite(6, err);
    analogWrite(7, 0);
    analogWrite(8, 0);
    analogWrite(9, 0);
  }
  // if zero, line is under central sensors
  else if (err == 0)
  {
    // go straight
    analogWrite(6, 150);
    analogWrite(7, 0);
    analogWrite(8, 150);
    analogWrite(9, 0);
  }
}

void sharp_turn_left()
{
  forward(150);
  delay(300);
  left(150);
  delay(550);
}

void sharp_turn_right()
{
  forward(150);
  delay(300);
  right(150);
  delay(550);
}

void u_turn()
{
  forward(150);
  delay(300);
  while (a == 0)
  {
    left(200);
    read_ir();
  }
  // delay(1100);
}

