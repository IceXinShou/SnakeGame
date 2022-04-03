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

void waitForInput(int type, Setting setting, GUI gui, Snake snakeData);


int main() {
    system("chcp 65001"); // UTF-8
    GUI gui;
    Setting setting;
    Snake snakeData;


    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdHandle == INVALID_HANDLE_VALUE)
        return GetLastError();

    // Show Selections
    XsSetting::Setting::init(&stdHandle);
    gui.main(snakeData);
    waitForInput(MAIN, setting, gui, snakeData);

}


void waitForInput(int type, Setting setting, GUI gui, Snake snakeData) {
    switch (type) {
        case MAIN: { // gui selections
            switch (getch()) {
                case '1':
                    setting.start();
                    break;
                case '2':
                    gui.setting(snakeData);
                    waitForInput(SETTING, setting, gui, snakeData);
                    return;
                case '3':
                    return;
            }
            gui.main(snakeData);
            waitForInput(MAIN, setting, gui, snakeData);
            break;
        }
        case SETTING: { // setting selections
            switch (getch()) {
                case '1':
                    setting.changeGameSize(&snakeData);
                    break;
                case '2':
                    setting.changeHeart(&snakeData);
                    break;
                case '3':
                    setting.changeSpeed(&snakeData);
                    break;
                case '4':
                    gui.main(snakeData);
                    waitForInput(MAIN, setting, gui, snakeData);
                    return;
            }

            gui.setting(snakeData);
            waitForInput(SETTING, setting, gui, snakeData);
            break;
        }
    }
}
