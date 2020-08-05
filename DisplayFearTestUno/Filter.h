//
// File			Filter.h
// Header
//
// Details		<#details#>
//
// Project		 SPIEqualizerEmbedded
// Developed with embedXcode
// https://embedXcode.weebly.com
//
// Author		Omer Shamai
// 				Omer Shamai
//
// Date			15/06/2020 11:55
// Version		<#version#>
//
// Copyright	(c) Omer Shamai, 2020
// Licence    <#licence#>
//
// See			ReadMe.txt for references
//


// Core library for code-sense - IDE-based
// !!! Help: http://bit.ly/2AdU7cu
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
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
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE


#ifndef Filter____FILEEXTENSION___
#define Filter____FILEEXTENSION___

class Ucglib_ST7735_18x128x160_HWSPI;

class Filter {
private:
    Ucglib_ST7735_18x128x160_HWSPI& _displayHandler;
    int _filterPositionInFilterArray;
    
    word wiperToInstruction(unsigned int val);
    float freqToResistanceAntiLog(long frequency);
    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
    double travelToResistanceLog(float travel);
    int resistanceToWiper(long maximumResistance, long resistance);
    
    bool& shouldReadFromMemory;
    
    float _capFarads;
    
    int _textColorR;
    int _textColorG;
    int _textColorB;
    
    ucg_int_t _displayX;
    ucg_int_t _displayY;
    
    ucg_int_t freqCursorX;
    ucg_int_t freqCursorY;
    
    ucg_int_t dbCursorX;
    ucg_int_t dbCursorY;
    
    ucg_int_t qCursorX;
    ucg_int_t qCursorY;
    
    long _freqRangeMin;
    long _freqRangeMax;
    
    long freqVal = 0;
    float freqResistance;
    int freqWiper;
    int lastFreqWiper;
    
    float dbVal = 0.0;
    int dbWiper;
    String dbStr;
    int lastDBWiper;
    
    int qVal = 0;
    float qTravel;
    double qResistance;
    int qWiper;
    int lastQWiper;
    String qStr;
    
    long memFreqVal = 0;
    float memFreqResistance;
    int memFreqWiper;
    
    float memDbVal = 0;
    int memDbWiper;
    //String memDbStr;
    
    int memQVal = 0;
    float memQTravel;
    double memQResistance;
    int memQWiper;
    
public:
    Filter(Ucglib_ST7735_18x128x160_HWSPI& displayHandler, bool &memoryBool, ucg_int_t displayX, ucg_int_t displayY, float capFarads, long freqRangeMin, long freqRangeMax, int filterPositionInFilterArray, int textColorR, int textColorG, int textColorB): _displayHandler(displayHandler), shouldReadFromMemory(memoryBool) {
        _displayX = displayX;
        _displayY = displayY;
        _capFarads = capFarads;
        _freqRangeMin = freqRangeMin;
        _freqRangeMax = freqRangeMax;
        _filterPositionInFilterArray = filterPositionInFilterArray;
        _textColorR = textColorR;
        _textColorG = textColorG;
        _textColorB = textColorB;
    }
    
    
    void begin();
    void setTextFrequency(char replacementText[]);
    void setTextDB(char replacementText[]);
    void setTextQ(char replacementText[]);
    
    long getFrequency();
    float getDB();
    int getQ();
    
    void setFrequency(long frequency);
    void setDB(float db);
    void setQ(int q);
    
    void updateFromMemory();
    void updateFromPots();
    
    //bool getReadStatus();
    
    void setMemFrequency(long frequency);
    void setMemDB(float db);
    void setMemQ(int q);
    
    long getMemFrequency();
    float getMemDB();
    int getMemQ();
    
    int frequencyReading();
    int dbReading();
    int qReading();
    
    long maximumFrequency();
    long minimumFrequency();
    
    ucg_int_t frequencyX();
    ucg_int_t frequencyY();
    
    ucg_int_t dbX();
    ucg_int_t dbY();
    
    ucg_int_t qX();
    ucg_int_t qY();
};

#endif // Filter____FILEEXTENSION___
