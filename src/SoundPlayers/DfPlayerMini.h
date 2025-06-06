#pragma once

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include "SoundPlayerInterface.h"
#include "../../Config.h"

class DfPlayerMini : public SoundPlayerInterface
{
    public:
        void init() override
        {
            Serial2.begin(9600);
        
            if (!player.begin(Serial2, true, false)) {
                #ifdef DEBUG
                    Serial.println(F("Unable to begin:"));
                    Serial.println(F("1.Please recheck the connection!"));
                    Serial.println(F("2.Please insert the SD card!"));
                #endif
            }
        
            #ifdef DEBUG
                Serial.println(F("DFPlayer Mini online."));
            #endif
            
            player.setTimeOut(500);
            player.volume(volumeLevel);
            player.stop();
        }
        void playFile(uint8_t fileNumber) override
        {
            player.play(fileNumber);
        }
        void loop()
        {
            if (millis() - loopTimer > loopTimeout) {
                loopTimer = millis();
                player.next();
            }
        }
    private:
        DFRobotDFPlayerMini player;
        uint8_t volumeLevel = 30;
        uint16_t loopTimeout = 15000;
        uint32_t loopTimer = 0;
};