#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11


#define SIZE    255
#define DELAY    20
#define HUE_MAX  6.0
#define HUE_DELTA 0.01

long rgb[3];
long rgbval;
// for reasons unknown, if value !=0, the LED doesn't light. Hmm ...
// and saturation seems to be inverted
float hue=0.0, saturation=1, value=1;

/*
chosen LED SparkFun sku: COM-09264
 has Max Luminosity (RGB): (2800, 6500, 1200)mcd
 so we normalize them all to 1200 mcd -
 R  250/600  =  107/256
 G  250/950  =   67/256
 B  250/250  =  256/256
 */
long bright[3] = { 107, 67, 256};
long k, temp_value;

int pwm1[3] = {3,5,6};
int pwm2[3] = {9,10,11};

void setup() {
  randomSeed(analogRead(4));
  for (k=0;k<3;k++){
    //pinMode(pwm1[k],OUTPUT);
    pinMode(pwm2[k],OUTPUT);
    rgb[k]=0;
    //analogWrite(pwm1[k], rgb[k] * bright[k]/256);
    analogWrite(pwm2[k], rgb[k] * bright[k]/256);
  }
  /*
  for (k=0; k<3; k++) {
    pinMode(REDPIN + k, OUTPUT);
    rgb[k]=0;
    analogWrite(REDPIN + k, rgb[k] * bright[k]/256);
  }*/
  /*
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  */
}

void loop() {
  hue += HUE_DELTA;
  if (hue > HUE_MAX) {
    hue=0.0;
  }
  rgbval=HSV_to_RGB(hue, saturation, value);
  
  rgb[0] = (rgbval & 0x00FF0000) >> 16; // there must be better ways
  rgb[1] = (rgbval & 0x0000FF00) >> 8;
  rgb[2] = rgbval & 0x000000FF;
  for (k=0; k<3; k++) { // for all three colours
    //analogWrite(REDPIN + k, rgb[k] * bright[k]/256);
    //analogWrite(pwm1[k], rgb[k] * bright[k]/256);
    //delay(1000);
    analogWrite(pwm2[k], rgb[k] * bright[k]/256);
    //delay(1000);
  }
  
  delay(DELAY);
  /*
  int r, g, b;
 
 
  // fade from violet to red
  for (b = 255; b >= 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(5);
  } 
  // fade from red to yellow
 for (g = 255; g>= 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(5);
  } 
 for (r = 255; r>= 0; r--) { 
    analogWrite(REDPIN, r);
    delay(5);
  } 
  */
}
long HSV_to_RGB( float h, float s, float v ) {
  /* modified from Alvy Ray Smith's site: http://www.alvyray.com/Papers/hsv2rgb.htm */
  // H is given on [0, 6]. S and V are given on [0, 1].
  // RGB is returned as a 24-bit long #rrggbb
  int i;
  float m, n, f;
 
  // not very elegant way of dealing with out of range: return black
  if ((s<0.0) || (s>1.0) || (v<1.0) || (v>1.0)) {
    return 0L;
  }
 
  if ((h < 0.0) || (h > 6.0)) {
    return long( v * 255 ) + long( v * 255 ) * 256 + long( v * 255 ) * 65536;
  }
  i = floor(h);
  f = h - i;
  if ( !(i&1) ) {
    f = 1 - f; // if i is even
  }
  m = v * (1 - s);
  n = v * (1 - s * f);
  switch (i) {
  case 6:
  case 0: 
    return long(v * 255 ) * 65536 + long( n * 255 ) * 256 + long( m * 255);
  case 1: 
    return long(n * 255 ) * 65536 + long( v * 255 ) * 256 + long( m * 255);
  case 2: 
    return long(m * 255 ) * 65536 + long( v * 255 ) * 256 + long( n * 255);
  case 3: 
    return long(m * 255 ) * 65536 + long( n * 255 ) * 256 + long( v * 255);
  case 4: 
    return long(n * 255 ) * 65536 + long( m * 255 ) * 256 + long( v * 255);
  case 5: 
    return long(v * 255 ) * 65536 + long( m * 255 ) * 256 + long( n * 255);
  }
} 
