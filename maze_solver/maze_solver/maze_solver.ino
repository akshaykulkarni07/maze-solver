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
  // any intersection where left turn is possible
  if (a == 1 && b == 1 && c == 1 && d == 1)
  {
    sharp_turn_left();
  }
  // intersection where left turn is impossible
  else if (a == 0 && b == 0 && c == 1 && d == 1 && e == 1 && f == 1)
  {
    // go a little forward to check whether forward or right
    forward(150);
    delay(250);
    read_ir();
    // if forward is possible, then go forward
    if (c == 1 && d == 1)
    {
      forward(150);
    }
    // otherwise take right turn
    else
    {
      right(150);
      delay(500);
    }
  }
  // reached dead end, take U-turn
  else if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0)
  {
    u_turn();
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
  long int err = (-4 * a) + (-3 * b) + (3 * e) + (4 * f);

  // if err is positive, means line is under right side sensors
  if (err > 0)
  {
    // map and constrain the error to a range of 0 to 255
    // so that it can be applied to motor
    err = map(err, 0, 8, 0, 255);
    err = constrain(err, 0, 255);
    // go left
    analogWrite(6, err);
    analogWrite(7, 0);
    analogWrite(8, 0);
    analogWrite(9, 0);
  }
  // if negative, line under left side sensors
  else if (err < 0)
  {
    // map and constrain the error to a range of 0 to 255
    // so that it can be applied to motor
    err = -err;
    err = map(err, 0, 8, 0, 255);
    err = constrain(err, 0, 255);
    // go right
    analogWrite(6, 0);
    analogWrite(7, 0);
    analogWrite(8, err);
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
  delay(500);
}

void sharp_turn_right()
{
  forward(150);
  delay(300);
  right(150);
  delay(500);
}

void u_turn()
{
  forward(150);
  delay(300);
  while (a == 0)
  {
    left(150);
    read_ir();
  }
  // delay(1100);
}

