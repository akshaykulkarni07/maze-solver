int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;

int spd1 = 160;

void setup()
{
  // Motors
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  // 0 i/p for white
  // 1 i/p for black
  read_ir();

  Serial.print("a = ");
  Serial.println(a);
  Serial.print("b = ");
  Serial.println(b);
  Serial.print("c = ");
  Serial.println(c);
  Serial.print("d = ");
  Serial.println(d);
  Serial.print("e = ");
  Serial.println(e);
  Serial.print("f = ");
  Serial.println(f);
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
  a = analogRead(A8);
  b = analogRead(A9);
  c = analogRead(A10);
  d = analogRead(A11);
  e = analogRead(A12);
  f = analogRead(A13);
}

