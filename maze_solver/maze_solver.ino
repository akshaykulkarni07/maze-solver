int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;

int spd1 = 160;
double prev_err = 0, integral = 0, derivative = 0;
double kp = 5, ki = 0, kd = 0;
double tm = 0, prev_tm = 0;


void setup()
{
  // Motors
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  
  // Serial.begin(9600);
  forward(spd1);
}

void loop() 
{
  read_ir();
  // 0 i/p for white
  // 1 i/p for black
  // straight lines
  if (a == 0 && b == 1 && c == 1 && d == 1 && e == 1 && f == 0)
  {
    forward(spd1);
    read_ir();
  }
  // curved right turns
  else if (a == 0 && b == 1 && c == 1 && d == 1 && e == 0 && f == 0)
  {
    right(spd1);
    read_ir();
  }
  // curved left turns
  else if (a == 0 && b == 0 && c == 1 && d == 1 && e == 1 && f == 0)
  {
    left(spd1);
    read_ir();
  }
  // otherwise stop
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

void right(int spd)
{
  analogWrite(2, 0);
  analogWrite(3, spd);
  analogWrite(4, spd);
  analogWrite(5, 0);
}

void left(int spd)
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

void motor_pid_control()
{
    while (a == 0 || f == 0)
    {
      read_ir();
      /* float err = ((-4 * a) + (-2 * b) + (2 * e) + (4 * f))/4;
    
      // measure time;
      tm = micros();
      // calculate dt for use in integral and derivative terms
      double dt = tm - prev_tm;
      // calculate the integral of error
      integral = integral + (err * dt);
      // calculate the derivative of error
      derivative = (err - prev_err) / dt;
      double output = (kp * err) + (ki * integral) + (kd * derivative);
      prev_err = err;
      Serial.println(output);
      /*if(output < 0)
      {
         
      }*/
    }
        
}


