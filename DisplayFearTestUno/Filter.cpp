//
// Filter.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// https://embedXcode.weebly.com
//
// Project 		SPIEqualizerEmbedded
//
// Created by 	Omer Shamai, 15/06/2020 11:56
// 				Omer Shamai
//
// Copyright 	(c) Omer Shamai, 2020
// Licence		N/A
//
// See 			Filter.h and ReadMe.txt for references
//


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

// Code
#include <Ucglib.h>
#include "Filter.h"

class Ucglib_ST7735_18x128x160_HWSPI;

void Filter::begin() {
    _displayHandler.setColor(0, _textColorR, _textColorG, _textColorB);
    _displayHandler.setPrintPos(_displayX, _displayY);
    _displayHandler.print("FRQ ");
    
    freqCursorX = _displayHandler.getCursorX();
    
    _displayHandler.setPrintPos(freqCursorX, _displayHandler.getCursorY() + 1);
    freqCursorY = _displayHandler.getCursorY();
    
    //freqVal = analogRead(_freqPot);
    //freqWiper = (int)freqVal;
    
    //freqVal = map(freqWiper, 0, 1023, _freqRangeMin, _freqRangeMax);
    //freqResistance = freqToResistanceAntiLog(freqVal);
    
    //_displayHandler.print(freqVal);
    //lastFreqWiper = freqWiper;
    
    _displayHandler.setPrintPos(_displayX, _displayHandler.getCursorY() + 14);
    
    dbCursorX = _displayHandler.getCursorX();
    dbCursorY = _displayHandler.getCursorY();
    
    //dbVal = analogRead(_dbPot);
    //dbWiper = (int)dbVal;
    
    //dbVal = mapFloat(dbWiper, 0.0, 1023.0, -10.0, 10.0);
    //dbStr = dbVal > 0.0 ? "+" + String(dbVal) : String(dbVal);
    
    //dbStr.remove(dbStr.length() - 1);
    
    /*if (dbStr == "+10.0") {
        dbStr = "+10";
    }
    if (dbStr == "-10.0") {
        dbStr = "-10";
    }
    if (dbStr == "+0.0" || dbStr == "-0.0") {
        dbStr = "+0.0";
    }*/
    
    //_displayHandler.print(dbStr);
    
    /*if (dbStr.length() == 1) {
        _displayHandler.print("   ");
    }
    if (dbStr.length() == 2) {
        _displayHandler.print("  ");
    }
    if (dbStr.length() == 3) {
        _displayHandler.print(" ");
    }*/
    
    _displayHandler.print("    db ");
    //lastDBWiper = dbWiper;
    
    _displayHandler.print("Q ");
    qCursorX = _displayHandler.getCursorX();
    qCursorY = _displayHandler.getCursorY();
    
    //qVal = analogRead(_qPot);
    //qTravel = mapFloat(qVal, 0.0, 1023.0, 0.0, 1.0);
    //qResistance = 5000 * travelToResistanceLog(qTravel);
    //qWiper = resistanceToWiper(50000, qResistance);
    //qVal = (int)map(qVal, 0, 1023, 0, 100);
    
    //qStr = String(qVal);
    /*if (qStr.length() == 1) {
        qStr = "00" + qStr;
    }
    if (qStr.length() == 2) {
        qStr = "0" + qStr;
    }*/
    
    //_displayHandler.print(qStr);
    //lastQWiper = qWiper;
}

/*bool Filter::getReadStatus() {
    return shouldReadFromMemory;
}*/

/*int Filter::frequencyReading() {
    return analogRead(_freqPot);
}

int Filter::dbReading() {
    return analogRead(_dbPot);
}

int Filter::qReading() {
    return analogRead(_qPot);
}*/
// 5614
// 809
float Filter::freqToResistanceAntiLog(long frequency) {
    float resistance = (1 / (2 * PI * frequency * _capFarads));
    return resistance;
}

double Filter::travelToResistanceLog(float travel) {
    double b = 1 / 0.15 - 1;
    b = b * b;
    double a = 1 / (b - 1);
    
    double resistance = (a * pow(b, travel)) - a;
    return resistance;
}

int Filter::resistanceToWiper(long maximumResistance, long resistance) {
    double long wiper = (resistance * 1023) / maximumResistance;
    return int(wiper);
}

ucg_int_t Filter::frequencyX() {
    return freqCursorX;
}

ucg_int_t Filter::frequencyY() {
    return freqCursorY;
}

ucg_int_t Filter::dbX() {
    return dbCursorX;
}

ucg_int_t Filter::dbY() {
    return dbCursorY;
}

ucg_int_t Filter::qX() {
    return qCursorX;
}

ucg_int_t Filter::qY() {
    return qCursorY;
}


void Filter::setTextFrequency(char replacementText[]) {
    _displayHandler.setPrintPos(freqCursorX, freqCursorY);
    _displayHandler.setColor(0, _textColorR, _textColorG, _textColorB);
    
    //_displayHandler.print(replacementText);
    for (int i = 1; i < sizeof(replacementText); i++) {
        _displayHandler.print(replacementText[i]);
    }
    
    
    /*switch (sizeof(modifiedReplacementText)) {
        case 1:
            //modifiedReplacementText = "00" + modifiedReplacementText;
            char temp[20] = "00";
            strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
            memmove(modifiedReplacementText, temp, sizeof(temp));
            break;
    
        case 2:
            //modifiedReplacementText = "0" + modifiedReplacementText;
            char temp[20] = "0";
            strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
            memmove(modifiedReplacementText, temp, sizeof(temp));
            break;
    
        default:
            if (String(_freqRangeMax).length() - sizeof(modifiedReplacementText) == 1) {
                Serial.print("Frequency: ");
                Serial.println(modifiedReplacementText);
                //modifiedReplacementText = "0" + modifiedReplacementText;
                char temp[sizeof(modifiedReplacementText)] = "0";
                strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
                memmove(modifiedReplacementText, temp, sizeof(temp));
            } else if (String(_freqRangeMax).length() - sizeof(modifiedReplacementText) == 2) {
                //modifiedReplacementText[] = "00" + modifiedReplacementText;
                char temp[sizeof(modifiedReplacementText)] = "00";
                strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
                memmove(modifiedReplacementText, temp, sizeof(temp));
            }
            break;
    }*/
    
    if (shouldReadFromMemory) {
        setMemFrequency(atol(replacementText));
    } else {
        setFrequency(atol(replacementText));
    }
    
    //_displayHandler.print(modifiedReplacementText);
}

void Filter::setTextDB(char replacementText[]) {
    //char modifiedReplacementText[20];
    
    //int length = strlen(replacementText);
    
    /*for (int i = 0; i < length; i++) {
        
    }*/
    
    //strncpy(modifiedReplacementText, replacementText, sizeof(replacementText));
    
    _displayHandler.setPrintPos(dbCursorX, dbCursorY);
    _displayHandler.setColor(0, _textColorR, _textColorG, _textColorB);
    
    //modifiedReplacementText.remove(replacementText.length() - 1);
    
    //modifiedReplacementText[sizeof(modifiedReplacementText) - 1] = 0x00;
    
    /*if (atof(modifiedReplacementText) > 0) {
        //modifiedReplacementText[] = "+" + modifiedReplacementText;
        char temp[sizeof(modifiedReplacementText)] = "+";
        strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
        memmove(modifiedReplacementText, temp, sizeof(temp));
    }*/
    
    /*if (modifiedReplacementText == "+10.0") {
        modifiedReplacementText = "+10";
    }
    if (modifiedReplacementText == "-10.0") {
        modifiedReplacementText = "-10";
    }
    if (modifiedReplacementText == "+0.0" || modifiedReplacementText == "-0.0") {
        modifiedReplacementText = "+0.0";
    }*/
    
    if (shouldReadFromMemory) {
        setMemDB(atof(replacementText));
    } else {
        setDB(atof(replacementText));
    }
    
    _displayHandler.print(replacementText);
    
    /*if (sizeof(modifiedReplacementText) == 1) {
        _displayHandler.print("   ");
    }
    if (sizeof(modifiedReplacementText) == 2) {
        _displayHandler.print("  ");
    }
    if (sizeof(modifiedReplacementText) == 3) {
        _displayHandler.print(" ");
    }*/
}

void Filter::setTextQ(char replacementText[]) {
    //char modifiedReplacementText[23];
    
    //strncpy(modifiedReplacementText, replacementText, sizeof(replacementText));
    
    _displayHandler.setPrintPos(qCursorX, qCursorY);
    _displayHandler.setColor(0, _textColorR, _textColorG, _textColorB);
    
    /*switch (sizeof(modifiedReplacementText)) {
        case 1:
            //modifiedReplacementText[] = "00" + modifiedReplacementText;
            char temp[sizeof(modifiedReplacementText)] = "00";
            strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
            memmove(modifiedReplacementText, temp, sizeof(temp));
            break;
            
        case 2:
            //modifiedReplacementText[] = "0" + modifiedReplacementText;
            char temp[sizeof(modifiedReplacementText)] = "0";
            strncat(temp, modifiedReplacementText, sizeof(modifiedReplacementText));
            memmove(modifiedReplacementText, temp, sizeof(temp));
            break;
            
        default:
            break;
    }*/
    
    if (shouldReadFromMemory) {
        setMemQ(atoi(replacementText));
    } else {
        setQ(atoi(replacementText));
    }
    
    _displayHandler.print(replacementText);
}

void Filter::setFrequency(long frequency) {
    freqVal = frequency;
    freqResistance = freqToResistanceAntiLog(freqVal);
    lastFreqWiper = freqWiper;
    freqWiper = map(freqVal, _freqRangeMin, _freqRangeMax, 0, 1023);
}

void Filter::setDB(float db) {
    dbVal = db;
    lastDBWiper = dbWiper;
    dbWiper = (int)mapFloat(db, -10.0, 10.0, 0.0, 1023.0);
}

void Filter::setQ(int q) {
    qVal = q;
    qTravel = mapFloat(qVal, 0.0, 100.0, 0.0, 1.0);
    qResistance = 5000 * travelToResistanceLog(qTravel);
    lastQWiper = qWiper;
    qWiper = resistanceToWiper(20000, qResistance);
}

// MARK: - Memory Property Setters



/// Sets the frequency value in the memory segment.
/// @param frequency The frequency to be set.
/// @warning The function automatically calculates and assigns the resistance and wiper to their respective variables in the memory segment. See @c freqToResistanceAntiLog() for more details.
/// @returns Nothing.
void Filter::setMemFrequency(long frequency) {
    memFreqVal = frequency;
    memFreqResistance = freqToResistanceAntiLog(freqVal);
    memFreqWiper = (int)map(freqVal, _freqRangeMin, _freqRangeMax, 0, 1023);
}


/// Sets the DB value in the memory segment.
/// @param db The DB to be set.
/// @warning The function automatically calculates and assigns the wiper to its respective variable in the memory segment. See @c mapFloat() for more details.
/// @returns Nothing.
void Filter::setMemDB(float db) {
    memDbVal = db;
    memDbWiper = (int)mapFloat(db, -10.0, 10.0, 0.0, 1023.0);
}


/// Sets the Q value in the memory segment.
/// @param q The Q to be set.
/// @warning The function automatically calculates and assigns the wiper, travel and resistance to their respective variables in the memory segment. See @c mapFloat() and @c travelToResistanceLog() for more details.
/// @returns Nothing.
void Filter::setMemQ(int q) {
    memQVal = q;
    memQWiper = (int)map(q, 0, 100, 0, 1023);
    memQTravel = mapFloat(q, 0.0, 100.0, 0.0, 1.0);
    memQResistance = 5000 * travelToResistanceLog(memQTravel);
}

// MARK: - Normal Property Getters
long Filter::getFrequency() { return freqVal; };
float Filter::getDB() { return dbVal; };
int Filter::getQ() { return qVal; };
long Filter::maximumFrequency() { return _freqRangeMax; };
long Filter::minimumFrequency() { return _freqRangeMin; };
// MARK: - Memory Property Getters
long Filter::getMemFrequency() { return memFreqVal; };
float Filter::getMemDB() { return memDbVal; };
int Filter::getMemQ() { return memQVal; };

// MARK: - Utilities
float Filter::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
