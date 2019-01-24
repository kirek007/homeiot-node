#include <Arduino.h>
#include <LowPower.h>
#include "SensorHelper.cpp"
#include "LcdHelper.cpp"
#include "RadioHelper.cpp"


SensorHelper sensors;
LcdHelper lcd;

void logger(String msg) {
    Serial.println(msg);
}

void setup() {
    Serial.begin(9600);
    
    lcd.init();    
    lcd.writeToLCD("Loading...",LcdHelper::LineNumber::LINE_2,true, LcdHelper::FontSize::FONT_BIG);
    sensors.init();

    delay(1000);
}

String getLineForSensor(SensorHelper::SensorValue sensorValue, String sensorNameText, String noValString) {
    String str;
    str =  String();
    str += sensorNameText;
    str += ": ";
    str +=  sensorValue.hasValue ? String(sensorValue.value) : noValString;    
    return str;
}

void loop() {

    SensorHelper::SensorsState sensorsData;
    sensorsData = sensors.getData();

    lcd.writeToLCD(getLineForSensor(sensorsData.light, "Light", "NA"), LcdHelper::LineNumber::LINE_2, true);
    lcd.writeToLCD(getLineForSensor(sensorsData.temperature, "Temp", "NA"), LcdHelper::LineNumber::LINE_3, false);
    lcd.writeToLCD(getLineForSensor(sensorsData.humidity, "Hum", "NA"), LcdHelper::LineNumber::LINE_4, false);

    delay(1000);
    // LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);    
}