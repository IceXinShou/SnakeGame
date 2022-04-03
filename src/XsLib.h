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

HANDLE hOut;

static void errorPrint(int errorCode);

static void printRepeat(const char &c, int count);

static void printRepeat(const string &c, int count);

struct Snake {
public:
    short gameSizeWidth = 60;
    short gameSizeHigh = 28;
    unsigned int hearts = 3;
    unsigned int speed = 10;
};


namespace XsUtil {

    class GUI {
        vector<string> mainWords{"<1> Start To Play", "<2> Settings", "<3> Exit"};
        vector<string> settingWords{"<1> Game Size", "<2> Snake's Hearts", "<3> Snake's Speed", "<4> Exit"};

    public:
        static void createMessage(const vector<string> &message, int position, Snake *data);; // lots of problems
        void main(Snake *data); // no error
        void setting(Snake *data); // no error
        static int getMaxLength(vector<string> words); // no error

    private:
        static void printDefaultBorder(int width, int high); // no error
    };

    void GUI::main(Snake *data) {
        XsUtil::GUI::createMessage(mainWords, CENTER_LEFT, data);
    }

    void GUI::setting(Snake *data) {
        XsUtil::GUI::createMessage(settingWords, CENTER_LEFT, data);
    }

    int GUI::getMaxLength(vector<string> words) {
        return int((*std::max_element(words.begin(), words.end(),
                                      [](const auto &a, const auto &b) { return a.size() < b.size(); })).length());
    }

    void GUI::createMessage(const vector<string> &message, int position, Snake *data) {
        switch (position) {
            case CENTER: {
                printDefaultBorder(data->gameSizeWidth, data->gameSizeHigh);

                SetConsoleCursorPosition(hOut, {0, 1});

                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Snake's Heart(s): %d\n"
                       "║ - Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHigh, data->hearts, data->speed);
                short firstLine = (data->gameSizeHigh - 6) / 2.0 + 0.5;
                for (const auto &i: message) {
                    SetConsoleCursorPosition(hOut, {short((data->gameSizeWidth - 2 - i.length()) / 2.0), firstLine++});
                    printf("%s", i.c_str());
                }
                break;
            }
            case CENTER_LEFT: {
                int space = (data->gameSizeWidth - getMaxLength(message)) >> 1;
                system("cls");

                // --
                printf("╔");
                printRepeat("═", data->gameSizeWidth - 2);
                printf("╗\n");
                // --

                printf(""
                       "║ Current:\n"
                       "║   GameSize: %d * %d\n"
                       "║   Snake's Heart(s): %d\n"
                       "║   Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHigh,
                       data->hearts, data->speed);

                printRepeat("║\n", int((data->gameSizeHigh - message.size()) / 2.0 - 5.5));
                for (const string &i: message) {
                    printf("║ ");
                    printRepeat(' ', space);
                    cout << std::left << setw(data->gameSizeWidth - space) << setfill(' ') << i << "║\n";
//                        printf("%s\n", i.c_str());

                }

                printRepeat("║ \n", int((data->gameSizeHigh - message.size()) / 2.0));

                // --
                printf("╚");
                printRepeat("═", data->gameSizeWidth - 2);
                printf("╝");
                // --

                break;
            }
        }
    }

    void GUI::printDefaultBorder(int width, int high) {
        system("cls");
        SetConsoleCursorPosition(hOut, {0, 0});
        printf("╔");
        printRepeat("═", width - 2);
        printf("╗\n");
        for (short i = 0; i < high - 2; ++i) {
            short posY = i + 1;
            SetConsoleCursorPosition(hOut, {0, posY});
            printf("║");
            SetConsoleCursorPosition(hOut, {short(width - 1), posY});
            printf("║");
        }
        printf("\n╚");
        printRepeat("═", width - 2);
        printf("╝");
    }
}


namespace XsSetting {

    class Setting {
        vector<string> changeGameSizeWord{"←  Width  →    |    ↑  High  ↓"};
        vector<string> newHeartsWord{"Type New Snake's Heart(s) (Default 3): "};
        vector<string> newSpeedWord{"Type New Snake's Speed (Default 10): "};

    public:

        static void init(HANDLE hOut); //
        static void start(Snake *data); // none
        void changeGameSize(Snake *data); // ! check whether string length suitable for new size
        void changeHeart(Snake *data); // no error
        void changeSpeed(Snake *data); // no error
    };

    void Setting::changeGameSize(Snake *data) {
        while (true) {
            XsUtil::GUI::createMessage(changeGameSizeWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->gameSizeHigh < 255)
                            data->gameSizeHigh += 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->gameSizeHigh > 1)
                            data->gameSizeHigh -= 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->gameSizeHigh < 246)
                            data->gameSizeHigh += 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->gameSizeHigh > 10)
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
                        if (data->gameSizeHigh < 255)
                            data->gameSizeWidth += 1;
                        break;
                    case 116:
                        // code for ctrl arrow right
                        if (data->gameSizeHigh < 246)
                            data->gameSizeWidth += 10;
                        break;
                    case 115:
                        // code for ctrl arrow left
                        if (data->gameSizeWidth > 10)
                            data->gameSizeWidth -= 10;
                        break;

                    default:
                        break;
                }
            else break;
        }
    }

    void Setting::changeHeart(Snake *data) {
        while (true) {
            XsUtil::GUI::createMessage(newHeartsWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->hearts > 1)
                            data->hearts -= 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->hearts < 4294967295)
                            data->hearts += 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->hearts > 10)
                            data->hearts -= 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->hearts < 4294967286)
                            data->hearts += 10;
                        break;
                    default:
                        break;
                }
            else break;
        }
    }

    void Setting::changeSpeed(Snake *data) {
        while (true) {
            XsUtil::GUI::createMessage(newSpeedWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->speed > 1)
                            data->speed -= 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->speed < 4294967295)
                            data->speed += 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->speed > 10)
                            data->speed -= 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->speed < 4294967286)
                            data->speed += 10;
                        break;
                    default:
                        break;
                }
            else break;
        }
    }

    void Setting::init(HANDLE hOut) {
        ::hOut = hOut;
    }

    void Setting::start(Snake *data) {

        short area[data->gameSizeWidth][data->gameSizeHigh];
        // set area to 0 (default)
        for (auto &i: area)
            for (short &j: i)
                j = AREA_AIR;


        // set high border
        for (int i = 0; i < data->gameSizeHigh; ++i) {
            area[0][i] += AREA_BORDER_LEFT;
            area[data->gameSizeWidth - 1][i] += AREA_BORDER_RIGH;
        }

        // set width border
        for (auto &i: area) {
            i[0] += AREA_BORDER_UP;
            i[data->gameSizeHigh - 1] += AREA_BORDER_DOWN;
        }

        area[int(data->gameSizeWidth >> 1)][int(data->gameSizeHigh >> 1)] = AREA_SNAKE_SPAWN_POINT;

    }
}

void printRepeat(const string &c, int count) {
    if (count < 0) errorPrint(-1);
    while (count--)
        cout << c;
}

void printRepeat(const char &c, int count) {
    if (count < 0) errorPrint(-1);
    while (count--)
        printf("%c", c);
}

void errorPrint(int errorCode) {
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
            case 1:
                printf("Something here!");
                break;
        }
    }
    printf("\n-\n\n");
    if (errorCode < 0) exit(0);
}


#endif // MAIN_XSLIB_H
