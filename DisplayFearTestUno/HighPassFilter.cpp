//
// HighPassFilter.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// https://embedXcode.weebly.com
//
// Project 		SPIEqualizerEmbedded
//
// Created by 	Omer Shamai, 29/06/2020 2:50
// 				___ORGANIZATIONNAME___
//
// Copyright 	(c) Omer Shamai, 2020
// Licence		N/A
//
// See 			HighPassFilter.h and ReadMe.txt for references
//


// Library header
#include "HighPassFilter.h"

// Code
void HighPassFilter::begin() {
    _displayHandler.setColor(0, R, G, B);
    _displayHandler.setPrintPos(_displayX, _displayY);
    
    _displayHandler.print("HPF ");
    
    freqCursorX = _displayHandler.getCursorX();
    freqCursorY = _displayHandler.getCursorY();
    //frequency = analogRead(potPin);
    
    //frequency = map(frequency, 0, 1023, long(_freqRangeMin), long(_freqRangeMax));
    //_displayHandler.print(frequency);
}

void HighPassFilter::setText(String replacementText) {
    String modifiedReplacementText = replacementText;
    
    switch (modifiedReplacementText.length()) {
        case 2:
            modifiedReplacementText = "00" + modifiedReplacementText;
            break;
            
        case 3:
            modifiedReplacementText = "0" + modifiedReplacementText;
            break;
            
        default:
            break;
    }
    
    if (shouldReadFromMemory) {
        setMem(atol(replacementText.c_str()));
    } else {
        //Serial.print("LPF SET TO: ");
        //Serial.println(String(atol(replacementText.c_str())));
        
        set(atol(replacementText.c_str()));
    }
    
    _displayHandler.setColor(0, R, G, B);
    _displayHandler.setPrintPos(freqCursorX, freqCursorY);
    
    _displayHandler.print(modifiedReplacementText);
}

void HighPassFilter::set(long newFrequency) {
    frequency = newFrequency;
    calculatedResistance = freqToResistanceAntiLog(frequency);
    calculatedWiper = resistanceToWiper(50000, calculatedResistance);
}

void HighPassFilter::setMem(long newFrequency) {
    memFrequency = newFrequency;
    memCalculatedResistance = freqToResistanceAntiLog(memFrequency);
    memCalculatedWiper = resistanceToWiper(50000, memCalculatedResistance);
}

float HighPassFilter::freqToResistanceAntiLog(long frequency) {
    float resistance = (1 / (2 * PI * frequency * capFarads));
    return resistance;
}

int HighPassFilter::resistanceToWiper(long maximumResistance, long resistance) {
    double long wiper = (resistance * 1024) / maximumResistance;
    return int(wiper);
}

long HighPassFilter::get() {
    return frequency;
}

long HighPassFilter::getMem() {
    return memFrequency;
}

long HighPassFilter::minimumFrequency() {
    return long(_freqRangeMin);
}

long HighPassFilter::maximumFrequency() {
    return long(_freqRangeMax);
}

ucg_int_t HighPassFilter::frequencyX() {
    return freqCursorX;
}

ucg_int_t HighPassFilter::frequencyY() {
    return freqCursorY;
}

/*int HighPassFilter::read() {
    return analogRead(potPin);
}*/
