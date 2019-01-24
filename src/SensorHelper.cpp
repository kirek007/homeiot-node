#include <DHT_U.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define DHT_PIN 2 // D2

/*
To do:
    - [Bug] Light sensor returns 0 or 65000 if no value or can't read.
*/

class SensorHelper {
    public:  
        struct SensorValue {
            bool hasValue = false;
            float value = 0;
        };
        struct SensorsState {
            bool temperatureEnabled = true;
            SensorValue temperature;
            bool humidityEnabled = true;
            SensorValue humidity;
            bool lightEnabled = false;
            SensorValue light;
        };

        SensorHelper() {}

        void init() {
            dht.begin();

            sensorsState.lightEnabled = tsl.begin();
            if (sensorsState.lightEnabled) {
                tsl.enableAutoRange(true);
                tsl.setGain(TSL2561_GAIN_16X);
            }
        }

        SensorsState getData() {
            this->sensorsState.humidity = getHumidity();
            this->sensorsState.temperature = getTemperature();
            
            if (sensorsState.lightEnabled)
                this->sensorsState.light = getLight();

            return this->sensorsState;
        }

    private:
        DHT_Unified dht = DHT_Unified(DHT_PIN, DHT22);
        Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
        SensorsState sensorsState;

    SensorValue getTemperature() {
        sensors_event_t event;  
        dht.temperature().getEvent(&event);
        SensorValue val;
        processEventValue(&val, event.temperature);
        return val;
    }

    SensorValue getHumidity() {
        sensors_event_t event;  
        dht.humidity().getEvent(&event);
        SensorValue val;
        processEventValue(&val, event.relative_humidity);
        return val;
    }

    SensorValue getLight() {
        sensors_event_t event;
        SensorValue val;
        if (tsl.getEvent(&event))
            processEventValue(&val, event.light);
        return val;
    }

    void processEventValue(SensorValue* sensorValue, float eventValue) {
        if (!isnan(eventValue)) {
            sensorValue->hasValue = true;
            sensorValue->value = eventValue;
        } else {
            sensorValue->hasValue = false;
            sensorValue->value = 0;
        }
    }

};