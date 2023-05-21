#define MAX_ITER 1000

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 32; x++) {
      double real = map(x, 0, 32, -2.0, 1.0);
      double imag = map(y, 0, 16, -1.0, 1.0);
      int value = mandelbrot(real, imag);
      Serial.print(value == MAX_ITER ? '#' : ' ');
    }
    Serial.println();
  }
}

void loop() {
  // do nothing
}

int mandelbrot(double real, double imag) {
  double r = 0.0, i = 0.0;
  int iter = 0;
  while (r*r + i*i < 4.0 && iter < MAX_ITER) {
    double temp = r*r - i*i + real;
    i = 2*r*i + imag;
    r = temp;
    iter++;
  }
  return iter;
}

double map(double value, double inMin, double inMax, double outMin, double outMax) {
  return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
