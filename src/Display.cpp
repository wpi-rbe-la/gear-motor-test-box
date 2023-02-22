#include "Display.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void Display::init(){
    pinMode(OLED_RESET, OUTPUT);
    digitalWrite(OLED_RESET, LOW);
    delay(10);
    digitalWrite(OLED_RESET, HIGH);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

}


void Display::sendPoint(int Ix, int Iy){
    display.drawCircle(Ix*display.width()/1023, Iy*display.height()/1023, 8, SSD1306_WHITE);
}


void Display::format(){
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.cp437(true);         // Use full 256 char 'Code Page 437' font


}

void Display::dispDistEncoder(int dist){

    String str = String(dist);

    display.setCursor(20, 20);     // Start at top-left corner
    display.write("3200 counts/rev");

    display.setCursor(40, 38);
    display.setTextSize(2); 
    for(int i =0; i < str.length(); i++ ) {
    display.write(str[i]);
    }

}


void Display::update(){
    display.display();
}

void Display::clear(){
    display.clearDisplay();
}