///
/// @file		Menu.h
/// @brief		Library header
/// @details	<#details#>
/// @n
/// @n @b		Project SPIEqualizerEmbedded
/// @n @a		Developed with [embedXcode](https://embedXcode.weebly.com)
///
/// @author		Omer Shamai
/// @author		Omer Shamai
///
/// @date		15/06/2020 11:58
/// @version	<#version#>
///
/// @copyright	(c) Omer Shamai, 2020
/// @copyright	<#licence#>
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

#ifndef Menu____FILEEXTENSION___
#define Menu____FILEEXTENSION___

#include <Ucglib.h>
#include "Filter.h"
#include "LowPassFilter.h"
#include "HighPassFilter.h"
//#include <SD.h>
#include <SPI.h>

#define MENU_BTN  5
#define SET_BTN   4
#define DOWN_BTN  7
#define UP_BTN    6

#define CARD_CS   2

class Ucglib_ST7735_18x128x160_HWSPI;

class MenuController {
private:
    Ucglib_ST7735_18x128x160_HWSPI& _displayHandler;
    bool* _parentMenuBool;
    bool* _parentMemoryBool;

    //Sd2Card card;
    //SdVolume volume;
    //SdFile root;

    //File fileToRW;
        
    void returnFunction();
    void loadMenu();
    void(* resetFunc) (void) = 0;

    void save(int selection);
    void load(int selection);

    Filter (&_filters)[4];
    
    LowPassFilter (&_lpf);
    HighPassFilter (&_hpf);
    
    byte (&comByte);
    byte (&datByte);
    
    ucg_int_t _currentSelectionSave = 0;
    ucg_int_t _currentSelectionLoad = 0;

    ucg_int_t _asteriskMainSaveX = 0;
    ucg_int_t _asteriskMainSaveY = 0;

    ucg_int_t _asteriskMainLoadX = 0;
    ucg_int_t _asteriskMainLoadY = 0;
    
    ucg_int_t exclSaveCoords[8][2];
    ucg_int_t asterSaveCoords[8][2];
    
    ucg_int_t asterLoadCoords[9][2];
    
    enum parserSituations {
        FilterDeclaration,
        FilterIndex,
        FrequencyValue,
        DBValue,
        QValue,
        EndFilterDeclaration,
        LowPassFilterDeclaration,
        LowPassFilterData,
        EndLowPassFilterDeclaration,
        HighPassFilterDeclaration,
        HighPassFilterData,
        EndHighPassFilterDeclaration
    };

    /*int _exclSaveX1 = 0;
    int _exclSaveY1 = 0;

    int _exclSaveX2 = 0;
    int _exclSaveY2 = 0;

    int _exclSaveX3 = 0;
    int _exclSaveY3 = 0;

    int _exclSaveX4 = 0;
    int _exclSaveY4 = 0;

    int _exclSaveX5 = 0;
    int _exclSaveY5 = 0;

    int _exclSaveX6 = 0;
    int _exclSaveY6 = 0;

    int _exclSaveX7 = 0;
    int _exclSaveY7 = 0;

    int _exclSaveX8 = 0;
    int _exclSaveY8 = 0;

    int _exclSaveX9 = 0;
    int _exclSaveY9 = 0;
    */

    /*int _asterSaveX1 = 0;
    int _asterSaveY1 = 0;

    int _asterSaveX2 = 0;
    int _asterSaveY2 = 0;

    int _asterSaveX3 = 0;
    int _asterSaveY3 = 0;

    int _asterSaveX4 = 0;
    int _asterSaveY4 = 0;

    int _asterSaveX5 = 0;
    int _asterSaveY5 = 0;

    int _asterSaveX6 = 0;
    int _asterSaveY6 = 0;

    int _asterSaveX7 = 0;
    int _asterSaveY7 = 0;

    int _asterSaveX8 = 0;
    int _asterSaveY8 = 0;

    int _asterSaveX9 = 0;
    int _asterSaveY9 = 0;
    */

public:
    MenuController(Ucglib_ST7735_18x128x160_HWSPI& displayHandler, bool* parentMenuBool, byte* commandByte, byte* dataByte, bool* parentMemoryBool, Filter (*filters)[4], LowPassFilter* lpf, HighPassFilter* hpf): _displayHandler(displayHandler), _parentMenuBool(parentMenuBool), _parentMemoryBool(parentMemoryBool), _filters(*filters), _lpf(*lpf), _hpf(*hpf), comByte(*commandByte), datByte(*dataByte) {};
    void show();
    void saveMenu();
    bool shouldShowController = false;
    bool shouldShowSave = false;
    bool shouldShowLoad = false;
    bool didJustExitMenu = false;
    ucg_int_t _currentSelectionMain = 0;
};

#endif // Menu____FILEEXTENSION___
