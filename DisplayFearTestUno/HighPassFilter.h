///
/// @file		HighPassFilter.h
/// @brief		Library header
/// @details	<#details#>
/// @n
/// @n @b		Project SPIEqualizerEmbedded
/// @n @a		Developed with [embedXcode](https://embedXcode.weebly.com)
///
/// @author		Omer Shamai
/// @author		___ORGANIZATIONNAME___
///
/// @date		29/06/2020 2:50
/// @version	1.0
///
/// @copyright	(c) Omer Shamai, 2020
/// @copyright	N/A
///
/// @see		ReadMe.txt for references
///


// Core library for code-sense - IDE-based
// !!! Help: http://bit.ly/2AdU7cu
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#include "libpandora_types.h"
#include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#include "Arduino.h"
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef HighPassFilter____FILEEXTENSION___
#define HighPassFilter____FILEEXTENSION___

#include <Ucglib.h>

#define AD_CS 7

class Ucglib_ST7735_18x128x160_HWSPI;

class HighPassFilter {
private:
    Ucglib_ST7735_18x128x160_HWSPI& _displayHandler;
    
    float freqToResistanceAntiLog(long frequency);
    word wiperToInstruction(unsigned int val);
    int resistanceToWiper(long maximumResistance, long resistance);
    //float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
    
    //int potentiometerPositionInPotentiometerArray[2];
    
    float capFarads;
    //int potPin;
    
    bool& shouldReadFromMemory;
    
    long frequency;
    long memFrequency;
    
    int calculatedWiper;
    int memCalculatedWiper;
    
    float calculatedResistance;
    float memCalculatedResistance;
    
    ucg_int_t R;
    ucg_int_t G;
    ucg_int_t B;
    
    ucg_int_t _displayX;
    ucg_int_t _displayY;
    
    ucg_int_t freqCursorX;
    ucg_int_t freqCursorY;
    
    long _freqRangeMin;
    long _freqRangeMax;
    
public:
    HighPassFilter(Ucglib_ST7735_18x128x160_HWSPI& displayHandler, long freqRangeMin, long freqRangeMax, float capacitor, ucg_int_t displayX, ucg_int_t displayY, ucg_int_t r, ucg_int_t g, ucg_int_t b): _displayHandler(displayHandler) {
        _freqRangeMin = freqRangeMin;
        _freqRangeMax = freqRangeMax;
        //potPin = potentiometer;
        capFarads = capacitor;
        //potentiometerPositionInPotentiometerArray[2] = potentiometerPosition;
        
        //potentiometerPositionInPotentiometerArray[0] = potentiometerPosition[0];
        //potentiometerPositionInPotentiometerArray[1] = potentiometerPosition[1];
        
        
        _displayX = displayX;
        _displayY = displayY;
        
        R = r;
        G = g;
        B = b;
    };
    
    void begin();
    void setText(String replacementText);
    
    ucg_int_t frequencyX();
    ucg_int_t frequencyY();
    
    void set(long newFrequency);
    void setMem(long newFrequency);
    
    long get();
    long getMem();
    
    int read();
    
    long minimumFrequency();
    long maximumFrequency();
};

#endif // HighPassFilter____FILEEXTENSION___
