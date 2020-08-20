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
#include <JC_Button.h>
//#include <SD.h>
//#include <SPI.h>

class Ucglib_ST7735_18x128x160_HWSPI;
Button menuBtn(5);

const int SHORT_PRESS_TIME = 1000;
const int LONG_PRESS_TIME  = 1000;

int lastState = HIGH;
int currentState;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

void MenuController::show() {
    if(!shouldShowController) {
        resetFunc();
    } else {
        menuBtn.begin();
        Wire.end();
        //TWCR = 0;
        _displayHandler.clearScreen();
        _displayHandler.setFont(ucg_font_inb16_mr);
    
        _displayHandler.setPrintPos(34, 0);

        _displayHandler.print("MENU");
        
        //Serial.println("SHOWING MENU");

        //_displayHandler.setPrintPos(0, 30);
        //_displayHandler.print("SAVE   ");

        //_asteriskMainSaveX = _displayHandler.getCursorX();
        //_asteriskMainSaveY = _displayHandler.getCursorY();

        //_displayHandler.print("*");

        //_displayHandler.setPrintPos(0, _asteriskMainSaveY + 17);

        //_displayHandler.print("LOAD   ");

        //_asteriskMainLoadX = _displayHandler.getCursorX();
        //_asteriskMainLoadY = _displayHandler.getCursorY();
        
        for (int i = 1; i <= 8; i++) {
            _displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 17);
            _displayHandler.print(i);
            
            exclSaveCoords[i-1][0] = _displayHandler.getCursorX();
            exclSaveCoords[i-1][1] = _displayHandler.getCursorY();
            
            _displayHandler.print("   ");
            
            asterSaveCoords[i-1][0] = _displayHandler.getCursorX();
            asterSaveCoords[i-1][1] = _displayHandler.getCursorY();
        }

        shouldShowController = true;
        
        _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
        _displayHandler.print("*");
        
        menuBtn.read();

        while (shouldShowController)
        {
            menuBtn.read();
            /*if (_currentSelectionMain == 0) {
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
            }*/
            
            //currentState = digitalRead(MENU_BTN);
            
            /*if (currentState == LOW) {
                shouldShowController = false;
                *_parentMenuBool = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
            }*/
            
            if (menuBtn.wasReleased()) {
                if (_currentSelectionSave == 7) {
                    _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                    _displayHandler.print(" ");
                    
                    //continue;
                    _currentSelectionSave = 0;
                    
                    _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                    _displayHandler.print("*");
                    continue;
                }
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave++;
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print("*");
                //lastState = currentState;
                delay(100);
                continue;
            } else if (menuBtn.pressedFor(LONG_PRESS_TIME)) {
                shouldShowController = false;
                //*_parentMenuBool = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
            }
            
            /*if (menuBtn.pressedFor(LONG_PRESS_TIME)) {
                shouldShowController = false;
                *_parentMenuBool = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
                //return;
            } else {
                if (_currentSelectionSave == 7) {
                    //continue;
                    _currentSelectionSave = 0;
                    continue;
                }
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print(" ");
                
                _currentSelectionSave++;
                
                _displayHandler.setPrintPos(asterSaveCoords[_currentSelectionSave][0], asterSaveCoords[_currentSelectionSave][1]);
                _displayHandler.print("*");
                //lastState = currentState;
                delay(100);
                continue;
            }*/
            
            //Serial.print("currentState = ");
            //Serial.println(String(currentState));

            if (digitalRead(SET_BTN) == LOW) {
                //Wire.begin(4);
                //delay(500);
                //saveMenu();
                
                comByte = 0x20;
                datByte = (byte) _currentSelectionSave;
                
                Wire.begin(4);
                //comByte = 0x20;
                //datByte = (byte) _currentSelectionSave;
                
                delay(100);
                
                Wire.end();
                
                *_parentMemoryBool = true;
                shouldShowController = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
            }

            if (digitalRead(DOWN_BTN) == LOW) {
                //loadMenu();
                /*Wire.begin(4);
                comByte = 0x20;
                datByte = 0x00;
                
                delay(100);
                
                comByte = 0x00;
                datByte = 0x00;
                Wire.end();
                 */
                //TWCR = 0;
                //load(0);
                //saveMenu();
                
                comByte = 0x10;
                datByte = (byte) _currentSelectionSave;
                
                Wire.begin(4);
                
                delay(100);
                
                Wire.end();
                
                *_parentMemoryBool = true;
                shouldShowController = false;
                comByte = 0x00;
                datByte = 0x00;
                _displayHandler.clearScreen();
                returnFunction();
            }

            /*if (digitalRead(UP_BTN) == LOW && _currentSelectionMain == 0) {
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
            }*/
            
        }
    }
}

void MenuController::saveMenu() {
    _displayHandler.clearScreen();
    _displayHandler.setPrintPos(34, 0);
    //_displayHandler.print("SAVE");
    
    if (_currentSelectionMain == 0) {
        _displayHandler.print("SAVE");
    } else {
        _displayHandler.print("LOAD");
    }
    
    //_displayHandler.print("SAVE LOAD");

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
        currentState = digitalRead(MENU_BTN);
        
        if (lastState == HIGH && currentState == LOW) {
            pressedTime = millis();
        } else if (lastState == LOW && currentState == HIGH) {
            releasedTime = millis();
            
            long pressDuration = releasedTime - pressedTime;
            
            if (pressDuration < SHORT_PRESS_TIME) {
                if (_currentSelectionSave == 7) {
                    //continue;
                    _currentSelectionSave = 0;
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
            
            if (pressDuration > LONG_PRESS_TIME) {
                return;
            }
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
                if (_currentSelectionMain == 0) {
                    comByte = 0x10;
                } else {
                    comByte = 0x20;
                }
                datByte = (byte) _currentSelectionSave;
                delay(100);

                comByte = 0x00;
                datByte = 0x00;
                Wire.end();
                continue;
            }

            /*if (digitalRead(DOWN_BTN) == LOW) {
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
            }*/
            
            if (digitalRead(DOWN_BTN) == LOW) {
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

/*void MenuController::loadMenu() {
    _displayHandler.clearScreen();
    _displayHandler.setPrintPos(34, 0);
    _displayHandler.print("LOAD");
    
    for (int i = 1; i <= 8; i++) {
        _displayHandler.setPrintPos(0, _displayHandler.getCursorY() + 17);
        _displayHandler.print(i);
        
        //exclLoadCoords[i-1][0] = _displayHandler.getCursorX();
        //exclLoadCoords[i-1][1] = _displayHandler.getCursorY();
        
        _displayHandler.print("   ");
        
        asterLoadCoords[i-1][0] = _displayHandler.getCursorX();
        asterLoadCoords[i-1][1] = _displayHandler.getCursorY();
    }

    shouldShowLoad = true;

    delay(100);
    while (shouldShowLoad) {
        if (digitalRead(MENU_BTN) == LOW) {
            shouldShowLoad = false;
            comByte = 0x00;
            datByte = 0x00;
            show();
        }
        
        _displayHandler.setPrintPos(asterLoadCoords[_currentSelectionLoad][0], asterLoadCoords[_currentSelectionLoad][1]);
        _displayHandler.print("*");
        
        if (shouldShowLoad) {
            if (digitalRead(SET_BTN) == LOW) {
                //save(_currentSelectionSave);
                Wire.begin(4);
                comByte = 0x20;
                datByte = (byte) _currentSelectionLoad;
                delay(100);

                comByte = 0x00;
                datByte = 0x00;
                Wire.end();
                continue;
            }

            if (digitalRead(DOWN_BTN) == LOW) {
                if (_currentSelectionLoad == 7) {
                    continue;
                }
                
                _displayHandler.setPrintPos(asterLoadCoords[_currentSelectionLoad][0], asterLoadCoords[_currentSelectionLoad][1]);
                _displayHandler.print(" ");
                
                _currentSelectionLoad++;
                
                _displayHandler.setPrintPos(asterLoadCoords[_currentSelectionLoad][0], asterLoadCoords[_currentSelectionLoad][1]);
                _displayHandler.print("*");
                
                delay(100);
                continue;
            }
            
            if (digitalRead(UP_BTN) == LOW) {
                if (_currentSelectionLoad == 0) {
                    continue;
                }
                
                _displayHandler.setPrintPos(asterLoadCoords[_currentSelectionLoad][0], asterLoadCoords[_currentSelectionLoad][1]);
                _displayHandler.print(" ");
                
                _currentSelectionLoad--;
                
                _displayHandler.setPrintPos(asterLoadCoords[_currentSelectionLoad][0], asterSaveCoords[_currentSelectionLoad][1]);
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

            
        }
    }
}*/

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
    
    //*_parentMenuBool = false;
    didJustExitMenu = true;
    
    //TWCR = 0;
    //Wire.begin(4);
    //delay(100);
    return;
}
