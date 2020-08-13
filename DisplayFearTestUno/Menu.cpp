//
// Menu.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// https://embedXcode.weebly.com
//
// Project         SPIEqualizerEmbedded
//
// Created by     Omer Shamai, 15/06/2020 11:58
//                 Omer Shamai
//
// Copyright     (c) Omer Shamai, 2020
// Licence        N/A
//
// See             Menu.h and ReadMe.txt for references
//


// Library header
#include <Arduino.h>
#include <Ucglib.h>
#include "Menu.h"
#include <Wire.h>
//#include <SD.h>
//#include <SPI.h>

class Ucglib_ST7735_18x128x160_HWSPI;

void MenuController::show() {
    
  
    if(!shouldShowController) {
        resetFunc();
    } else {
        Wire.end();
        //TWCR = 0;
        _displayHandler.clearScreen();
        _displayHandler.setFont(ucg_font_inb16_mr);
    
        _displayHandler.setPrintPos(0, 0);

        _displayHandler.print("MENU");

        _displayHandler.setPrintPos(0, 30);
        _displayHandler.print("SAVE   ");

        _asteriskMainSaveX = _displayHandler.getCursorX();
        _asteriskMainSaveY = _displayHandler.getCursorY();

        //_displayHandler.print("*");

        _displayHandler.setPrintPos(0, _asteriskMainSaveY + 17);

        _displayHandler.print("LOAD   ");

        _asteriskMainLoadX = _displayHandler.getCursorX();
        _asteriskMainLoadY = _displayHandler.getCursorY();

        shouldShowController = true;

        while (shouldShowController)
        {
            if (_currentSelectionMain == 0) {
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print("*");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print(" ");
            } else {
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print(" ");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print("*");
            }

            // CHECK BUTTON PRESS
            if (digitalRead(MENU_BTN) == LOW) {
                shouldShowController = false;
                *_parentMenuBool = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
            }

            if (digitalRead(SET_BTN) == LOW && _currentSelectionMain == 0) {
                //Wire.begin(4);
                //delay(500);
                saveMenu();
            }

            if (digitalRead(SET_BTN) == LOW && _currentSelectionMain == 1) {
                //loadMenu();
                //Wire.begin(4);
                comByte = 0x20;
                datByte = 0x00;
                //Wire.end();
                
                delay(10);
                
                comByte = 0x00;
                datByte = 0x00;
                //TWCR = 0;
                //load(0);
            }

            if (digitalRead(UP_BTN) == LOW && _currentSelectionMain == 0) {
                _currentSelectionMain = 1;
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print(" ");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print("*");
                delay(100);
            }

            if (digitalRead(UP_BTN) == LOW && _currentSelectionMain == 1) {
                _currentSelectionMain = 0;
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print("*");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print(" ");
                delay(100);
            }

            if (digitalRead(DOWN_BTN) == LOW && _currentSelectionMain == 0) {
                _currentSelectionMain = 1;
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print(" ");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print("*");
                delay(100);
            }

            if (digitalRead(DOWN_BTN) == LOW && _currentSelectionMain == 1) {
                _currentSelectionMain = 0;
                _displayHandler.setPrintPos(_asteriskMainSaveX, _asteriskMainSaveY);
                _displayHandler.print("*");

                _displayHandler.setPrintPos(_asteriskMainLoadX, _asteriskMainLoadY);
                _displayHandler.print(" ");
                delay(100);
            }
    }}
}

void MenuController::saveMenu() {
    _displayHandler.clearScreen();
    _displayHandler.setPrintPos(34, 0);
    _displayHandler.print("SAVE");

    /*_displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 17);
    _displayHandler.print("1");

    _exclSaveX1 = _displayHandler.getCursorX();
    _exclSaveY1 = _displayHandler.getCursorY();

    _displayHandler.print("   ");

    _asterSaveX1 = _displayHandler.getCursorX();
    _asterSaveY1 = _displayHandler.getCursorY();

    _displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 16);
    _displayHandler.print("2");

    _exclSaveX2 = _displayHandler.getCursorX();
    _exclSaveY2 = _displayHandler.getCursorY();

    _displayHandler.print("   ");

    _asterSaveX2 = _displayHandler.getCursorX();
    _asterSaveY2 = _displayHandler.getCursorY();
    */
    
    for (int i = 1; i <= 8; i++) {
        _displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 17);
        _displayHandler.print(i);
        
        exclSaveCoords[i-1][0] = _displayHandler.getCursorX();
        exclSaveCoords[i-1][1] = _displayHandler.getCursorY();
        
        _displayHandler.print("   ");
        
        asterSaveCoords[i-1][0] = _displayHandler.getCursorX();
        asterSaveCoords[i-1][1] = _displayHandler.getCursorY();
    }

    shouldShowSave = true;
    
    _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
    _displayHandler.print("*");

    delay(100);
    while (shouldShowSave) {
        if (digitalRead(MENU_BTN) == LOW) {
            shouldShowSave = false;
            comByte = 0x00;
            datByte = 0x00;
            show();
        }

        if (shouldShowSave) {
            
            /*switch (_currentSelectionSave)
            {
            case 0:
                _displayHandler.setPrintPos(_asterSaveX1, _asterSaveY1);
                _displayHandler.print("*");
                //_displayHandler.print(" ");

                _displayHandler.setPrintPos(_asterSaveX2, _asterSaveY2);
                _displayHandler.print(" ");
                break;
            case 1:
                _displayHandler.setPrintPos(_asterSaveX1, _asterSaveY1);
                _displayHandler.print(" ");

                _displayHandler.setPrintPos(_asterSaveX2, _asterSaveY2);
                _displayHandler.print("*");
                break;

            default:
                break;
            }*/
            
            /*_displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
            _displayHandler.print("*");
             */

            if (digitalRead(SET_BTN) == LOW) {
                //save(_currentSelectionSave);
                Wire.begin(4);
                comByte = 0x10;
                datByte = (byte) _currentSelectionSave;
                delay(100);

                comByte = 0x00;
                datByte = 0x00;
                Wire.end();
                continue;
            }

            if (digitalRead(DOWN_BTN) == LOW) {
                if (_currentSelectionSave == 7) {
                    continue;
                }
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave++;
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print("*");
                
                delay(100);
                continue;
            }
            
            if (digitalRead(UP_BTN) == LOW) {
                if (_currentSelectionSave == 0) {
                    continue;
                }
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave--;
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print("*");
                
                delay(100);
                continue;
            }

            /*if (digitalRead(DOWN_BTN) == LOW && _currentSelectionSave == 7) {
                /*_displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave = 0;
                
                delay(100);
                //continue;
            }

            if (digitalRead(UP_BTN) == LOW && _currentSelectionSave == 0) {
                /*_displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave = 8;
                
                delay(100);
                //continue;
            }

            /*if (digitalRead(UP_BTN) == LOW && _currentSelectionSave == 0) {
                _currentSelectionSave = 1;
            }*/
        }
    }
}

/*void MenuController::save(int selection) {
    Serial.println(String(selection) + ".txt");
    if (SD.exists(String(selection) + ".txt")) {
        SD.remove(String(selection) + ".txt");

        fileToRW = SD.open(String(selection) + ".txt", FILE_WRITE);
    } else {
        fileToRW = SD.open(String(selection) + ".txt", FILE_WRITE);
        fileToRW.close();

        if(SD.exists(String(selection) + ".txt")) {
            Serial.println("New file created");
            fileToRW = SD.open(String(selection) + ".txt", FILE_WRITE);
        }
    }

    if (fileToRW) {
        //fileToRW.seek(0);

        //fileToRW.println("This is a test");
        //fileToRW.close();
        for (int i = 0; i < 4; i++) {
            long freqToSave = _filters[i].getFrequency();
            float dbToSave = _filters[i].getDB();
            int qToSave = _filters[i].getQ();

            Serial.println(freqToSave);
            Serial.println(String(dbToSave));
            Serial.println(String(qToSave));

            fileToRW.print("FILTER ");
            fileToRW.print(String(i));
            fileToRW.print(" ");
            
            fileToRW.print(String(freqToSave) + " ");
            fileToRW.print(String(dbToSave) + " ");
            fileToRW.print(String(qToSave) + " ");
            
            fileToRW.print("END ");
        }
        
        long lpfFrequencyToSave = _lpf.get();
        Serial.print("LPF: ");
        Serial.println(lpfFrequencyToSave);
        
        fileToRW.print("LPF ");
        fileToRW.print(String(lpfFrequencyToSave) + " ");
        fileToRW.print("END ");
        
        fileToRW.print("ENDFIN");
        fileToRW.close();

        Serial.println("SUCCESS WRITING TO FILE!");
    } else {
        Serial.println("Unable to open the file");
    }
}*/

/*void MenuController::load(int selection) {
    int keywordCount = 0;
    int currentCell = 0;
    String fileContents = "";
    String extractedKeyword = "";
    long frequencyData;
    float dbData;
    int qData;
    long lpfData;

    if (SD.exists(String(selection) + ".txt")) {
        fileToRW = SD.open(String(selection) + ".txt");
    }

    while (fileToRW.available()) {
        char currentCharacter = fileToRW.read();
        fileContents += currentCharacter;

        if (currentCharacter == ' ') {
            keywordCount++;
        }
    }

    keywordCount++;

    Serial.print("Keyword count: ");
    Serial.println(String(keywordCount));

    String extractedKeywords[keywordCount];

    Serial.println(fileContents);

    for (int i = 0; i <= fileContents.length() + 7; i++) {
        if (fileContents[i] != ' ') {
            extractedKeyword += fileContents[i];
        }

        if (fileContents[i] == ' ') {
            extractedKeywords[currentCell] = extractedKeyword;
            currentCell++;

            Serial.print("The extracted keyword is: ");
            Serial.println(extractedKeyword);
            extractedKeyword = "";
        }
    }

    fileToRW.close();

    int currentFilter;
    String lastKeyword;
    parserSituations lastKeywordDescription;
    for (int i = 0; i < keywordCount; i++) {
        if (extractedKeywords[i] == "FILTER") {
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = FilterDeclaration;
            continue;
        }

        if ((extractedKeywords[i] == "0" || "1" || "2" || "3") && (lastKeywordDescription == FilterDeclaration) && lastKeyword == "FILTER") {
            currentFilter = extractedKeywords[i].toInt();
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = FilterIndex;
            continue;
        }

        if (lastKeywordDescription == FilterIndex) {
            frequencyData = strtol(extractedKeywords[i].c_str(), NULL, 10);
            Serial.println(frequencyData);
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = FrequencyValue;
            continue;
        }

        if ((extractedKeywords[i].indexOf(".") > 0) && (lastKeywordDescription == FrequencyValue)) {
            dbData = extractedKeywords[i].toFloat();
            Serial.println(dbData);
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = DBValue;
            continue;
        }

        if ((lastKeyword.indexOf(".") > 0) && (lastKeywordDescription == DBValue)) {
            qData = strtol(extractedKeywords[i].c_str(), NULL, 10);
            Serial.println(extractedKeywords[i].c_str());
            //Serial.println(int(test));
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = QValue;
            continue;
        }

        if ((lastKeywordDescription == QValue) && (extractedKeywords[i] == "END")) {
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = EndFilterDeclaration;

            _filters[currentFilter].setMemFrequency(frequencyData);
            _filters[currentFilter].setMemDB(dbData);
            _filters[currentFilter].setMemQ(qData);
            continue;
        }
        
        if ((lastKeywordDescription == EndFilterDeclaration) && (extractedKeywords[i] == "LPF")) {
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = LowPassFilterDeclaration;
            continue;
        }
        
        if ((lastKeywordDescription == LowPassFilterDeclaration)) {
            lpfData = strtol(extractedKeywords[i].c_str(), NULL, 10);
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = LowPassFilterData;
            continue;
        }
        
        if ((lastKeywordDescription == LowPassFilterData) && (extractedKeywords[i] == "END")) {
            _lpf.setMem(lpfData);
            lastKeyword = extractedKeywords[i];
            lastKeywordDescription = EndLowPassFilterDeclaration;
            continue;
        }

        if (extractedKeywords[i] == "ENDFIN") {
            break;
        }
    }

    Serial.println("UPDATED VARIABLES!!");

    Serial.print("FREQUENCY VALUE: ");
    Serial.println(String(_filters[0].getMemFrequency()));

    Serial.print("DB VALUE: ");
    Serial.println(String(_filters[0].getMemDB()));
    
    Serial.print("Q VALUE: ");
    Serial.println(String(_filters[0].getMemQ()));

    Serial.println("CHECK IF THE OUTPUT MATCHES THE FILE CONTENTS!!!!!");

    //*_parentMemoryBool = true;
}*/

void MenuController::loadMenu() {
    _displayHandler.clearScreen();
    _displayHandler.setPrintPos(34, 0);
    _displayHandler.print("LOAD");

    shouldShowLoad = true;

    delay(100);
    while (shouldShowLoad) {
        if (digitalRead(MENU_BTN) == LOW) {
            shouldShowLoad = false;
            show();
        }
        
    }
}

void MenuController::returnFunction() {
    _displayHandler.clearScreen();

    _displayHandler.setFontPosTop();

    _displayHandler.setRotate180();
    //_displayHandler.setFont(ucg_font_courR12_mr);
    _displayHandler.setFont(lucida_console);
    //_displayHandler.setFont(jetbrains_mono);
    
    _filters[0].begin();
    
    // DIVIDER
    _displayHandler.setPrintPos(0, 31);
    _displayHandler.setColor(255, 255, 255);
    _displayHandler.drawHLine(0, 30, 128);
    
    _filters[1].begin();

    //DIVIDER
    _displayHandler.setPrintPos(0, 63);
    _displayHandler.setColor(255,255,255);
    _displayHandler.drawHLine(0, _displayHandler.getCursorY(), 128);
    
    //FILTER 3 INITIALIZE
    _filters[2].begin();

    //DIVIDER
    _displayHandler.setPrintPos(0, 96);
    _displayHandler.setColor(255,255,255);
    _displayHandler.drawHLine(0, _displayHandler.getCursorY(), 128);
    
    //FILTER 4 INITIALIZE
    _filters[3].begin();
    
    //DIVIDER
    _displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 14);
    _displayHandler.setColor(255,255,255);
    _displayHandler.drawHLine(0, _displayHandler.getCursorY(), 128);
    
    _displayHandler.setPrintPos(0, 129);
    _displayHandler.setColor(255,255,255);
    _displayHandler.drawHLine(0, _displayHandler.getCursorY(), 128);
    
    _lpf.begin();
    _hpf.begin();
    
    *_parentMenuBool = false;
    
    TWCR = 0;
    Wire.begin(4);
    return;
}
