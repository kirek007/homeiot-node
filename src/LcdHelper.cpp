#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


class LcdHelper {
    public:
        enum LineNumber {
            LINE_1 = 0,
            LINE_2 = 1,
            LINE_3 = 2,
            LINE_4 = 3,  
        };

        enum FontSize {
            FONT_SMALL = 1,
            FONT_BIG = 2
        };
        LcdHelper(){}
       
        void init(bool crashIfFailure=false){
            isEnabled = true;
            if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
                isEnabled = false;
                Serial.println(F("SSD1306 allocation failed"));
                if (crashIfFailure) for(;;); 
            }
        };

        void writeToLCD(String msg, LineNumber line, bool cleanScreen, FontSize fontSize=FontSize::FONT_SMALL){
            if (!isEnabled) return;

            if (cleanScreen) 
                display.clearDisplay();
            
            display.setTextSize(fontSize); 
            display.setTextColor(WHITE);
            display.setTextWrap(false);
            display.setCursor(0, line*8);
            display.println(msg);
            display.display();  
        }
    private:
        bool isEnabled = false; 
        Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);



};