#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H
#endif // MAIN_XSLIB_H

#include <bits/stdc++.h>

#define CENTER 0
#define CENTER_LEFT 1
#define AREA_FRUIT 2
#define AREA_SNAKE_SPAWN_POINT 1
#define AREA_AIR 0
#define AREA_SNAKE_BODY -1
#define AREA_BORDER_LEFT -2
#define AREA_BORDER_RIGH -3
#define AREA_BORDER_UP -4
#define AREA_BORDER_LEFT_UP -6
#define AREA_BORDER_RIGHT_UP -7
#define AREA_BORDER_DOWN -8
#define AREA_BORDER_LEFT_DOWN -10
#define AREA_BORDER_RIGHT_DOWN -11

using namespace std;

static void errorPrint(int errorCode) {
    printf("\n\n-\n");
    if (errorCode < 0) {
        printf("Game had crash and shutdown by error: ");
        switch (errorCode) {
            case -1:
                printf("Repeat number could not be negative!");
                break;
        }
    } else {
        printf("Game met an error: ");
        switch (errorCode) {
            case -1:
                printf("Something here!");
                break;
        }
    }
    printf("\n-\n\n");
    if (errorCode < 0) exit(0);
}

static void printRepeat(char c, int count) {
    if (count < 0) errorPrint(-1);
    while (count--)
        printf("%c", c);
}

class Snake {
public:
    int gameSizeWidth = 50;
    int gameSizeHigh = 30;
    int hearts = 3;
    int speed = 10;


    void init() {
        short area[gameSizeWidth][gameSizeHigh];
        // set area to 0 (default)
        for (auto &i: area)
            for (short &j: i)
                j = AREA_AIR;


        // set high border
        for (int i = 0; i < gameSizeHigh; ++i) {
            area[0][i] += AREA_BORDER_LEFT;
            area[gameSizeWidth - 1][i] += AREA_BORDER_RIGH;
        }
        // set width border
        for (auto &i: area) {
            i[0] += AREA_BORDER_UP;
            i[gameSizeHigh - 1] += AREA_BORDER_DOWN;
        }

        area[int(gameSizeWidth / 2.0 + 0.5)][int(gameSizeHigh / 2.0 + 0.5)] = AREA_SNAKE_SPAWN_POINT;

        start();
    }

private:
    void start() {

    }


};


namespace XsUtil {


    /**
     * GUI
     */


    class GUI {
        vector<string> mainWords{"<1> Start To Play", "<2> Settings", "<3> Exit"};
        vector<string> settingWords{"<1> Game Size of High", "<2> Game Size of Width", "<3> Snake's Hearts",
                                    "<4> Snake's Speed", "<5> Exit"};

    public:
        static void createMessage(const vector<string> &message, int position, Snake data) {
            switch (position) {
                case CENTER: {
                    system("cls");
                    printf("Current:\n\tGameSize: %d*%d\n\tSnake's Heart(s): %d\n\tSnake's Speed: %d",
                           data.gameSizeWidth, data.gameSizeHigh,
                           data.hearts, data.speed);
                    printRepeat('\n', int(data.gameSizeHigh - message.size()) / 2 - 4);
                    for (const string &i: message) {
                        printf("\n");
                        printRepeat(' ', int((data.gameSizeWidth - i.length()) / 2));
                        printf("%s", i.c_str());
                    }
                    break;
                }
                case CENTER_LEFT: {
                    int space = (data.gameSizeWidth - getMaxLength(message)) / 2;
                    system("cls");
                    printf("Current:\n\tGameSize: %d*%d\n\tSnake's Heart(s): %d\n\tSnake's Speed: %d",
                           data.gameSizeWidth, data.gameSizeHigh,
                           data.hearts, data.speed);
                    printRepeat('\n', int(data.gameSizeHigh - message.size()) / 2 - 3);
                    for (const string &i: message) {
                        printRepeat(' ', space);
                        printf("%s\n", i.c_str());
                    }
                    break;
                }
            }
        };

        void main(Snake data) {
            XsUtil::GUI::createMessage(mainWords, CENTER_LEFT, data);
        }

        void setting(Snake data) {
            XsUtil::GUI::createMessage(settingWords, CENTER_LEFT, data);
        }

        static int getMaxLength(vector<string> words) {
            return int((*std::max_element(words.begin(), words.end(),
                                          [](const auto &a, const auto &b) { return a.size() < b.size(); })).length());
        }

    };
}


namespace XsSetting {

    /**
     * Setting
     */

    class Setting {
        vector<string> newGameSizeHighWord{"Type New Game Size of High (Default 30): "};
        vector<string> newGameSizeWidthWord{"Type New Game Size of Width (Default 30): "};
        vector<string> newHeartsWord{"Type New Snake's Heart(s) (Default 3): "};
        vector<string> newSpeedWord{"Type New Snake's Speed (Default 10): "};

    public:
        void changeGameSizeHigh(Snake *data) {
            XsUtil::GUI::createMessage(newGameSizeHighWord, CENTER, *data);
            scanf("%d", &data->gameSizeHigh);
        }

        void changeGameSizeWidth(Snake *data) {
            XsUtil::GUI::createMessage(newGameSizeWidthWord, CENTER, *data);
            scanf("%d", &data->gameSizeWidth);
        }

        void changeHeart(Snake *data) {
            XsUtil::GUI::createMessage(newHeartsWord, CENTER, *data);
            scanf("%d", &data->hearts);
        }

        void changeSpeed(Snake *data) {
            XsUtil::GUI::createMessage(newSpeedWord, CENTER, *data);
            scanf("%d", &data->speed);
        }

        void start() {

        }
    };
}
