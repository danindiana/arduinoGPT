#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define MAX_ITER 150
#define WIDTH 240
#define HEIGHT 320

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  drawMandelbrot();
  while(1);  // Stop the loop after drawing the set once
}

void drawMandelbrot() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      double real = map(x, 0, WIDTH, -2.0, 1.0);
      double imag = map(y, 0, HEIGHT, -1.5, 1.5);
      int value = mandelbrot(real, imag);
      tft.drawPixel(x, y, colorMap(value));
    }
  }
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

uint16_t colorMap(int value) {
  if (value == MAX_ITER) {
    return ILI9341_BLACK;
  }
  else {
    return tft.color565(value % 32 * 8, value % 64 * 4, value % 128 * 2);
  }
}
