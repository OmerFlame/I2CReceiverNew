//
// LowPassFilter.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// https://embedXcode.weebly.com
//
// Project 		SPIEqualizerEmbedded
//
// Created by 	Omer Shamai, 19/06/2020 12:00
// 				Omer Shamai
//
// Copyright 	(c) Omer Shamai, 2020
// Licence		N/A
//
// See 			LowPassFilter.h and ReadMe.txt for references
//


// Library header
#include "LowPassFilter.h"

// Code

/// Initializes the low pass filter on the screen.
/// @returns Nothing.
void LowPassFilter::begin() {
    _displayHandler.setColor(0, R, G, B);
    _displayHandler.setPrintPos(_displayX, _displayY);
    
    _displayHandler.print("LPF ");
    
    freqCursorX = _displayHandler.getCursorX();
    freqCursorY = _displayHandler.getCursorY();
    //frequency = analogRead(potPin);
    
    //frequency = map(frequency, 0, 1023, long(_freqRangeMin), long(_freqRangeMax));
    //_displayHandler.print(frequency);
}

void LowPassFilter::setText(String replacementText) {
    String modifiedReplacementText = replacementText;
    
    switch (modifiedReplacementText.length()) {
        case 1:
            modifiedReplacementText = "0000" + modifiedReplacementText;
            break;
        case 2:
            modifiedReplacementText = "000" + modifiedReplacementText;
            break;
            
        case 3:
            modifiedReplacementText = "00" + modifiedReplacementText;
            break;
            
        case 4:
            modifiedReplacementText = "0" + modifiedReplacementText;
            
        default:
            
            break;
    }
    
    if (shouldReadFromMemory) {
        setMem(atol(replacementText.c_str()));
    } else {
        Serial.print("LPF SET TO: ");
        Serial.println(String(atol(replacementText.c_str())));
        
        set(atol(replacementText.c_str()));
    }
    
    _displayHandler.setColor(0, R, G, B);
    _displayHandler.setPrintPos(freqCursorX, freqCursorY);
    
    _displayHandler.print(modifiedReplacementText);
}

void LowPassFilter::set(long newFrequency) {
    frequency = newFrequency;
    calculatedResistance = freqToResistanceAntiLog(frequency);
    calculatedWiper = resistanceToWiper(50000, calculatedResistance);
}

void LowPassFilter::setMem(long newFrequency) {
    memFrequency = newFrequency;
    memCalculatedResistance = freqToResistanceAntiLog(memFrequency);
    memCalculatedWiper = resistanceToWiper(50000, memCalculatedResistance);
}

float LowPassFilter::freqToResistanceAntiLog(long frequency) {
    float resistance = (1 / (2 * PI * frequency * capFarads));
    return resistance;
}

int LowPassFilter::resistanceToWiper(long maximumResistance, long resistance) {
    double long wiper = (resistance * 1024) / maximumResistance;
    return int(wiper);
}

word LowPassFilter::wiperToInstruction(unsigned int val) {
    byte highbyte = (val >> 8) + 0x04;
    byte lowbyte = val & 0xFF;
    
    word combined = (highbyte << 8) | (lowbyte);
    return combined;
}

long LowPassFilter::get() {
    return frequency;
}

long LowPassFilter::getMem() {
    return memFrequency;
}

long LowPassFilter::minimumFrequency() {
    return long(_freqRangeMin);
}

long LowPassFilter::maximumFrequency() {
    return long(_freqRangeMax);
}

ucg_int_t LowPassFilter::frequencyX() {
    return freqCursorX;
}

ucg_int_t LowPassFilter::frequencyY() {
    return freqCursorY;
}

/*int LowPassFilter::read() {
    return analogRead(potPin);
}*/

// LOWEST FREQUENCY: 26.526
// HIGHEST FREQUENCY: 4019

// MINIMUM RESISTANCE: 330
// MAXIMUM RESISTANCE: 50000
