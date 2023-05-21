#define MAX_ITER 300

const char characters[] = ".-+*#";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 64; x++) {
      double real = map((double)x, 0.0, 64.0, -2.0, 1.0);
      double imag = map((double)y, 0.0, 32.0, -1.0, 1.0);
      int value = mandelbrot(real, imag);
      int index = (int) map((double)value, 0.0, (double)MAX_ITER, 0.0, (double)(sizeof(characters) - 1));
      Serial.print(characters[index]);
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
