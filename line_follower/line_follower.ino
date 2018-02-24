int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;

void setup() 
{
  // Motors
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  // IR sensors
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);

  // Serial.begin(9600);
}

void loop() 
{
  // 0 i/p for white
  // 1 i/p for black
  read_ir();
  /* 
  Serial.println("a = ");
  Serial.print(a);
  Serial.println("b = ");
  Serial.print(b);
  Serial.println("c = ");
  Serial.print(c);
  Serial.println("d = ");
  Serial.print(d);
  Serial.println("e = ");
  Serial.print(e);
  Serial.println("f = ");
  Serial.print(f);
  */
  if ((a == 1 && b == 1 && c == 0 && d == 0 && e == 1 && f == 1) || (a == 1 && b == 0 && c == 0 && d == 0 && e == 0 && f == 1))
  {
    forward(100);
    read_ir();
  }
  else if ((a == 0 || b == 0) && d == 1 && e == 1 && f == 1)
  {
    left(100);
    read_ir();
  }
  else if (a == 1 && b == 1 && d == 1 && (e == 0 || f == 0))
  {
    right(100);
    read_ir();
  }
  else if (a == 1 && b == 1 && c == 1 && d == 1 && e == 1 && f == 1)
  {
    reverse(100);
    read_ir();
  }
  else
  {
    stop_motors();
    read_ir();
  }
}

void forward(int spd)
{
  analogWrite(2, spd);
  analogWrite(3, 0);
  analogWrite(4, spd);
  analogWrite(5, 0);
}

void reverse(int spd)
{
  analogWrite(2, 0);
  analogWrite(3, spd);
  analogWrite(4, 0);
  analogWrite(5, spd);
}

void left(int spd)
{
  analogWrite(2, 0);
  analogWrite(3, spd);
  analogWrite(4, spd);
  analogWrite(5, 0);
}

void right(int spd)
{
  analogWrite(2, spd);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, spd);
}

void stop_motors()
{
  analogWrite(2, 0);
  analogWrite(3, 0);
  analogWrite(4, 0);
  analogWrite(5, 0);
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

