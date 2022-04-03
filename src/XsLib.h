#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>

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

static void printRepeat(const char &c, int count) {
    if (count < 0) errorPrint(-1);
    while (count--)
        printf("%c", c);
}

static void printRepeat(const string &c, int count) {
    if (count < 0) errorPrint(-1);
    while (count--)
        cout << c;
}

class Snake {
public:
    int gameSizeWidth = 60;
    int gameSizeHigh = 28;
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

        area[int(gameSizeWidth >> 1)][int(gameSizeHigh >> 1)] = AREA_SNAKE_SPAWN_POINT;

        start();
    }

private:
    void start() {

    }


};


namespace XsUtil {

    class GUI {
        vector<string> mainWords{"<1> Start To Play", "<2> Settings", "<3> Exit"};
        vector<string> settingWords{"<1> Game Size", "<2> Snake's Hearts",
                                    "<3> Snake's Speed", "<4> Exit"};

    public:
        static void createMessage(const vector<string> &message, int position, Snake data) {
            switch (position) {
                case CENTER: {
                    system("cls");

                    // --
                    printf("╔");
                    printRepeat("═", data.gameSizeWidth - 2);
                    printf("╗\n");
                    // --


                    printf(""
                           "║ Current:\n"
                           "║   GameSize: %d * %d\n"
                           "║   Snake's Heart(s): %d\n"
                           "║   Snake's Speed: %d\n",
                           data.gameSizeWidth, data.gameSizeHigh,
                           data.hearts, data.speed);

//                    cout << left << setw(30) << "║ Current:\n";
//                    cout << left << setw(30) << "║   GameSize: " << data.gameSizeWidth << '*' << data.gameSizeHigh
//                         << '\n';
//                    cout << left << setw(30) << "║   Snake's Heart(s): " << data.hearts << '\n';
//                    cout << left << setw(30) << "║   Snake's Speed: " << data.speed << '\n';
                    printRepeat("║ \n", int(data.gameSizeHigh - message.size()) / 2.0 - 5.5);
                    for (const string &i: message) {
//                        printf("║ \n║ ");
                        cout << "║ " << std::left << setfill(' ') << setw(data.gameSizeWidth - 2) << i << "║\n";
//                        printRepeat(" ", int((data.gameSizeWidth - i.length()) / 2.0 + 0.5));
//                        printf("%s", i.c_str());
//                        printRepeat(' ', int((data.gameSizeWidth - i.length()) / 2.0));
//                        printf("║");
                    }

                    printRepeat("║ \n", int((data.gameSizeHigh - message.size()) / 2.0));

                    // --
                    printf("╚");
                    printRepeat("═", data.gameSizeWidth - 2);
                    printf("╝");
                    // --

                    break;
                }
                case CENTER_LEFT: {
                    int space = (data.gameSizeWidth - getMaxLength(message)) >> 1;
                    system("cls");

                    // --
                    printf("╔");
                    printRepeat("═", data.gameSizeWidth - 2);
                    printf("╗\n");
                    // --

                    printf(""
                           "║ Current:\n"
                           "║   GameSize: %d * %d\n"
                           "║   Snake's Heart(s): %d\n"
                           "║   Snake's Speed: %d\n",
                           data.gameSizeWidth, data.gameSizeHigh,
                           data.hearts, data.speed);

                    printRepeat("║\n", int((data.gameSizeHigh - message.size()) / 2.0 - 5.5));
                    for (const string &i: message) {
                        printf("║ ");
                        printRepeat(' ', space);
                        printf("%s\n", i.c_str());
                    }

                    printRepeat("║ \n", int((data.gameSizeHigh - message.size()) / 2.0));

                    // --
                    printf("╚");
                    printRepeat("═", data.gameSizeWidth - 2);
                    printf("╝");
                    // --

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
        vector<string> changeGameSizeWidthWord{"← Width → | ↑ High  ↓"};
        vector<string> newHeartsWord{"Type New Snake's Heart(s) (Default 3): "};
        vector<string> newSpeedWord{"Type New Snake's Speed (Default 10): "};

    public:
        void changeGameSize(Snake *data) {
            while (true) {
                XsUtil::GUI::createMessage(changeGameSizeWidthWord, CENTER, *data);

                if (getch() == 224)
                    switch (getch()) {
                        case 80:
                            // code for arrow up
                            data->gameSizeHigh += 1;
                            break;
                        case 72:
                            // code for arrow down
                            data->gameSizeHigh -= 1;
                            break;
                        case 145:
                            // code for ctrl arrow up
                            data->gameSizeHigh += 10;
                            break;
                        case 141:
                            // code for ctrl arrow down
                            data->gameSizeHigh -= 10;
                            break;
                            // ---------------------------------
                        case 75:
                            // code for arrow left
                            if (data->gameSizeWidth > 1)
                                data->gameSizeWidth -= 1;
                            break;
                        case 77:
                            // code for arrow right
                            data->gameSizeWidth += 1;
                            break;
                        case 116:
                            // code for ctrl arrow right
                            data->gameSizeWidth += 10;
                            break;
                        case 115:
                            // code for ctrl arrow left
                            if (data->gameSizeWidth > 10)
                                data->gameSizeWidth -= 10;
                            break;

                        default:
                            continue;
                    }
                else break;
            }
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

#endif // MAIN_XSLIB_H