// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#define PIN        23 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 1 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

String payload;

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup() 
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int x,y,z;
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  while(Serial.available() > 0)
    {
      payload = Serial.readString();
  
  
      x = getValue(payload,',',0).toInt();
      y = getValue(payload,',',1).toInt();
      z = getValue(payload,',',2).toInt();
      Serial.print("x ");
      Serial.println(x);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    //pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(x, y, z));
    pixels.show();
    }
    
   }
}
