//
// DisplayFearTestUno
//
// Description of the project
// Developed with [embedXcode](https://embedXcode.weebly.com)
//
// Author         Omer Shamai
//                 ___ORGANIZATIONNAME___
//
// Date            19/07/2020 18:24
// Version        <#version#>
//
// Copyright    © Omer Shamai, 2020
// Licence        <#licence#>
//
// See         ReadMe.txt for references
//


// Core library for code-sense - IDE-based
// !!! Help: http://bit.ly/2AdU7cu
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.8 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

// Set parameters


// Include application, user and local libraries
// !!! Help http://bit.ly/2CL22Qp
#include <Ucglib.h>
#include "Menu.h"
#include <Wire.h>
#include "Filter.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"

// Define structures and classes


// Define variables and constants
#define TFT_CS                          8
#define TFT_RST                         9
#define TFT_DC                          8

#define CARD_CS                         2

#define AD_CS                           4
#define AD_MOSI                        23
#define AD_MISO                        36
#define AD_SCK                          5

#define MENU_BTN                        5
#define SET_BTN                         4

#define SW_LO_PK                        3
#define SW_MID2_PK                     22
#define SW_HI_PK                       25
#define SW_FILTER_ON                   24
#define SW_BYPASS                      27

#define LED_FILTER_ON                  28
#define LED_HI_PK                      29
#define LED_MID2_PK                     6
#define LED_BYPASS                     47
#define LED_LO_PK                      44

#define LOW_FILTER_CAP        0.000000082
#define MID1_MID2_FILTER_CAP 0.0000000082
#define HIGH_FILTER_CAP      0.0000000039
#define LOW_PASS_CAP        0.00000000033
#define HIGH_PASS_CAP        0.0000000012

byte commandByte = 0x00;
byte dataByte = 0x00;

int setCounter = 0;
int setState = 0;
int lastSetState = 0;

int lowPickCounter = 0;
int lowPickState = 0;
int lastLowPickState = 0;

int mid2Counter = 0;
int mid2State = 0;
int lastMid2PickState = 0;

//2068

int highPickCounter = 0;
int highPickState = 0;
int lastHighPickState = 0;

int filterOnCounter = 0;
int filterOnState = 0;
int lastFilterOnState = 0;

int bypassCounter = 0;
int bypassState = 0;
int lastBypassState = 0;

bool shouldUseMemory = false;
bool isShowingMenu = false;

Ucglib_ST7735_18x128x160_HWSPI ucg(8, 10, 9);
Filter filter1(ucg, shouldUseMemory, 0, 99, LOW_FILTER_CAP, 40, 800, 3, 255, 255, 0);
Filter filter2(ucg, shouldUseMemory, 0, 66, MID1_MID2_FILTER_CAP, 400, 8000, 1, 0, 162, 255);
Filter filter3(ucg, shouldUseMemory, 0, 33, MID1_MID2_FILTER_CAP, 400, 8000, 2, 255, 60, 0);
Filter filter4(ucg, shouldUseMemory, 0, 0, HIGH_FILTER_CAP, 800, 17000, 3, 255, 0, 196);

Filter filters[] = { filter1, filter2, filter3, filter4 };

LowPassFilter lpf(ucg, long(96.46), 14615, LOW_PASS_CAP, 0, 133, 219, 84, 97);
HighPassFilter hpf(ucg, long(26.526), long(2368.4), HIGH_PASS_CAP, 0, 149, 61, 84, 103);
MenuController menu(ucg, &isShowingMenu, &commandByte, &dataByte, &shouldUseMemory, &filters, &lpf, &hpf);

// Prototypes
// !!! Help: http://bit.ly/2TAbgoI


// Utilities


// Functions
void initAllFilters() {
    // FIRST FILTER INITIATE
    filters[0].begin();
    
    // DIVIDER
    ucg.setPrintPos(0, 31);
    ucg.setColor(255, 255, 255);
    ucg.drawHLine(0, 30, 128);
    
    // SECOND FILTER INITIATE
    filters[1].begin();

    // DIVIDER
    ucg.setPrintPos(0, 63);
    ucg.setColor(255,255,255);
    ucg.drawHLine(0, ucg.getCursorY(), 128);
    
    // FILTER 3 INITIALIZE
    filters[2].begin();

    // DIVIDER
    ucg.setPrintPos(0, 96);
    ucg.setColor(255,255,255);
    ucg.drawHLine(0, ucg.getCursorY(), 128);
    
    // FILTER 4 INITIALIZE
    filters[3].begin();
    
    // DIVIDER
    ucg.setPrintPos(0, ucg.getCursorY() + 14);
    ucg.setColor(255,255,255);
    ucg.drawHLine(0, ucg.getCursorY(), 128);
    
    ucg.setPrintPos(0, 129);
    ucg.setColor(255,255,255);
    ucg.drawHLine(0, ucg.getCursorY(), 128);
    
    lpf.begin();
    hpf.begin();
}


void receiveEvent(int howMany) {
    
    if (isShowingMenu == false && digitalRead(MENU_BTN) == LOW) {
        //Wire.beginTransmission(1);
        //Wire.write(0x01);
        //Wire.endTransmission();
        commandByte = 0x01;
        dataByte = 0x01;
        
        menu.shouldShowController = true;
        return;
        //menu.show();
    }
    if (isShowingMenu == true && digitalRead(MENU_BTN) == HIGH) {
        return;
    }
    
    //Serial.println("RECEIVED");
    char buffer[howMany];
    int currentCell = 0;
    
    for (int i = 0; i < 39; i++) {
        buffer[i] = 0x00;
    }
    
    char extractedKeywords[2][40];
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 39; j++) {
            extractedKeywords[i][j] = 0x00;
        }
    }
    
    Wire.readBytes(buffer, howMany);
    
    byte algoKey = buffer[0];
    
    if (algoKey == 0x00) {
        //filters[0].setTextFrequency(extractedKeywords[1]);
        //Serial.println("0x00 RECEIVED");
        ucg.setPrintPos(filters[0].frequencyX(), filters[0].frequencyY());
        ucg.setColor(255, 255, 0);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
        Serial.println();
    } else if (algoKey == 0x01) {
        //filters[0].setTextDB(extractedKeywords[1]);
        //Serial.println("0x01 RECEIVED");
        ucg.setPrintPos(filters[0].dbX(), filters[0].dbY());
        ucg.setColor(255, 255, 0);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x02) {
        filters[0].setTextQ(extractedKeywords[1]);
        ucg.setPrintPos(filters[0].qX(), filters[0].qY());
        ucg.setColor(255, 255, 0);
        
        ucg.print(buffer[1]);
        ucg.print(buffer[2]);
        ucg.print(buffer[3]);
    } else if (algoKey == 0x10) {
        ucg.setPrintPos(filters[1].frequencyX(), filters[1].frequencyY());
        ucg.setColor(0, 162, 255);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x11) {
        ucg.setPrintPos(filters[1].dbX(), filters[1].dbY());
        ucg.setColor(0, 162, 255);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x12) {
        ucg.setPrintPos(filters[1].qX(), filters[1].qY());
        ucg.setColor(0, 162, 255);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x20) {
        ucg.setPrintPos(filters[2].frequencyX(), filters[2].frequencyY());
        ucg.setColor(255, 60, 0);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x21) {
        ucg.setPrintPos(filters[2].dbX(), filters[2].dbY());
        ucg.setColor(255, 60, 0);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x22) {
        ucg.setPrintPos(filters[2].qX(), filters[2].qY());
        ucg.setColor(255, 60, 0);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x30) {
        //char buf[sizeof(buffer) - 1];
        
        //memcpy(buf, buffer + 1, sizeof(buffer) - 1);
        
        ucg.setPrintPos(filters[3].frequencyX(), filters[3].frequencyY());
        ucg.setColor(255, 0, 196);
        //ucg.print(buf);
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
        //ucg.setPrintPos(0, 2);
        //ucg.print(algoBuffer);
        
        //Serial.print("GOT INPUT: ");
        //Serial.println(algoBuffer);
    } else if (algoKey == 0x31) {
        //filters[3].setTextDB(extractedKeywords[1]);
        ucg.setPrintPos(filters[3].dbX(), filters[3].dbY());
        ucg.setColor(255, 0, 196);
        
        /*for (int i = 1; i < 6; i++) {
            ucg.print(buffer[i]);
        }*/

        ucg.print(buffer[1]);
        ucg.print(buffer[2]);
        ucg.print(buffer[3]);
        ucg.print(buffer[4]);

        //Serial.print(buffer[2]);
        //Serial.println();
        //Serial.println();
    } else if (algoKey == 0x32) {
        //filters[3].setTextQ(extractedKeywords[1]);
        ucg.setPrintPos(filters[3].qX(), filters[3].qY());
        ucg.setColor(255, 0, 196);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x40) {
        //lpf.setText(extractedKeywords[1]);
        ucg.setPrintPos(lpf.frequencyX(), lpf.frequencyY());
        ucg.setColor(219, 84, 97);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x50) {
        ucg.setPrintPos(hpf.frequencyX(), hpf.frequencyY());
        ucg.setColor(61, 84, 103);
        
        for (int i = 1; i < sizeof(buffer); i++) {
            ucg.print(buffer[i]);
        }
    } else if (algoKey == 0x90) {
        ucg.setPrintPos(90, 149);
        ucg.setColor(0, 255, 0, 0);
        ucg.print("MEM");
    } else if (algoKey == 0x80) {
        ucg.setPrintPos(90, 149);
        ucg.setColor(0, 255, 0, 0);
        ucg.print("   ");
    }
}

void requestEvent() {
    Wire.write(commandByte);
    Wire.write(dataByte);

    commandByte = 0x00;
    dataByte = 0x00;
}

void reset() {
    ucg.clearScreen();
    
    initAllFilters();
}

// Add setup code
void setup()
{
    Serial.begin(9600);
    ucg.begin(UCG_FONT_MODE_SOLID);
    ucg.clearScreen();
    ucg.setFontPosTop();
    ucg.setRotate180();
    ucg.setFont(lucida_console);
    ucg.setColor(255, 255, 255);
    
    pinMode(MENU_BTN, INPUT);
    pinMode(SET_BTN, INPUT);
    
    
    //digitalWrite(MENU_BTN, HIGH);
    
    //ucg.setPrintPos(0, 0);
    //ucg.print("Test");
    
    initAllFilters();
    
    delay(1000);
    
    Wire.begin(4);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

// Add loop code
void loop()
{
    if (isShowingMenu == false && digitalRead(MENU_BTN) == LOW) {
        menu.shouldShowController = true;
        menu.show();
    }
    if (isShowingMenu == true && digitalRead(MENU_BTN) == HIGH) {
        return;
    }
    
    setState = digitalRead(SET_BTN);
    
    if (setState != lastSetState) {
        if (setState == LOW) {
            setCounter++;
        }
        
        delay(50);
    }
    
    lastSetState = setState;
    
    if (setCounter % 2 == 0) {
        //shouldUseMemory = false;

        commandByte = 0x02;
        dataByte = 0x00;

        delay(100);
        //ucg.setPrintPos(90, -1);
        //ucg.setColor(0, 255, 0, 0);
        //ucg.print("   ");
    } else {
        //shouldUseMemory = true;
        commandByte = 0x02;
        dataByte = 0x01;

        delay(100);
    }
}
