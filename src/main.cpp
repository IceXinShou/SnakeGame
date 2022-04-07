#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "XsLib.h"

#define MAIN -1
#define SETTING -2

using namespace std;
using namespace XsUtil;
using namespace XsSetting;

// Class init

void waitForInput(int type, Setting setting, GUI gui);


int main() {
    system("chcp 65001 | cls"); // UTF-8
    auto *snakeData = new Snake();
    GUI gui = GUI(snakeData);
    Setting setting = Setting(snakeData);
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == INVALID_HANDLE_VALUE)
        return GetLastError();

    SetConsoleCursorInfo(console, new CONSOLE_CURSOR_INFO{1, false});

    // Show Selections

    gui.printDefaultBorder(snakeData->gameSizeWidth, snakeData->gameSizeHeight);
    gui.main();
    waitForInput(MAIN, setting, gui);
}

void waitForInput(int type, Setting setting, GUI gui) {
    switch (type) {
        case MAIN: { // gui selections
            switch (_getwch()) {
                case 13:  // Enter
                    setting.start();
                    break;
                case 111:  // O
                    gui.setting();
                    waitForInput(SETTING, setting, gui);
                    return;
                case 27: // Esc
                    exit(0);
            }
        }
        case SETTING: { // setting selections
            switch (getch()) {
                case '1':
                    setting.changeGameSize();
                    break;
                case '2':
                    setting.changeHeart();
                    break;
                case '3':
                    setting.changeSpeed();
                    break;
                case '4':
                    gui.main();
                    waitForInput(MAIN, setting, gui);
                    return;
            }

            gui.setting();
            waitForInput(SETTING, setting, gui);
            break;
        }
    }
}