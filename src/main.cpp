#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "XsLib.h"

#define MAIN -1
#define SETTING -2

#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52

using namespace std;
using namespace XsUtil;
using namespace XsSetting;

// Class init

void waitForInput(int type, Setting setting, GUI gui, SnakeData snakeData);


int main() {
    GUI gui;
    Setting setting;
    SnakeData snakeData;

    // Show Selections
    gui.main(snakeData);
    waitForInput(MAIN, setting, gui, snakeData);
}


void waitForInput(int type, Setting setting, GUI gui, SnakeData snakeData) {
    switch (type) {
        case MAIN: { // gui selections
            switch (getch()) {
                case KEY_1:
                    setting.start();
                    break;
                case KEY_2:
                    gui.setting(snakeData);
                    waitForInput(SETTING, setting, gui, snakeData);
                    return;
                case KEY_3:
                    return;
            }
            gui.main(snakeData);
            waitForInput(MAIN, setting, gui, snakeData);
            break;
        }

        case SETTING: { // setting selections
            switch (getch()) {
                case KEY_1:
                    setting.changeGameSize(snakeData);
                    break;
                case KEY_2:
                    setting.changeHeart(snakeData);
                    break;
                case KEY_3:
                    setting.changeSpeed(snakeData);
                    break;
                case KEY_4:
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

