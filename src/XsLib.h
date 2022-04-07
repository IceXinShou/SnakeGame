#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>


#define CENTER 0
#define CENTER_LEFT 1

// ***
#define AREA_FRUIT 2
#define AREA_AIR 0
#define AREA_SNAKE_HEAD -1
#define AREA_SNAKE_BODY -2
// ***


using namespace std;

HANDLE console; // batch setting handler
static void errorPrint(int errorCode); // game crash or report
static void printRepeat(const char &c, int count); // repeat print out char
static void printRepeat(const string &c, int count); // repeat print out string
static void pos(const short &x, const short &y); // set cursor position

struct Snake {
    short x[255 * 255]{};
    short y[255 * 255]{};
    int length = 3;
    int lengthNow = 0;
    int offset = 0;
    short gameSizeWidth = 60; // game size width
    short gameSizeHeight = 30; // game size high
    unsigned int hearts = 3; // snake's hearts
    unsigned int speed = 10; // snake's speed
    unsigned int level = 3; // snake's level
};

namespace XsUtil {

    class GUI {
        vector<string> mainWords{"<1> Start To Play", "<2> Settings", "<3> Exit"};
        vector<string> settingWords{"<1> Game Size", "<2> Snake's Hearts", "<3> Snake's Speed", "<4> Exit"};

    public:
        explicit GUI(Snake *data);

        static void createMessage(const vector<string> &message, int position, Snake *data);; // no error
        static int getMaxLength(vector<string> words); // no error
        void main(); // no error
        void setting(); // no error

        static void printDefaultBorder(short width, short high);

        // no error
        static void clearScreenWithoutBorder(short width, short height);

    private:
        // no error
        Snake *data;
    };

    GUI::GUI(Snake *data) {
        this->data = data;
    }

    void GUI::main() {
        XsUtil::GUI::createMessage(mainWords, CENTER_LEFT, data);
    }

    void GUI::setting() {
        XsUtil::GUI::createMessage(settingWords, CENTER_LEFT, data);
    }

    int GUI::getMaxLength(vector<string> words) {
        return int((*std::max_element(words.begin(), words.end(),
                                      [](const auto &a, const auto &b) { return a.size() < b.size(); })).length());
    }

    void GUI::createMessage(const vector<string> &message, int position, Snake *data) {
        switch (position) {
            case CENTER: {
                clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
//                printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);

                pos(0, 1);

                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Snake's Heart(s): %d\n"
                       "║ - Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHeight, data->hearts, data->speed);
                short firstLine = (data->gameSizeHeight - 6) / 2.0 + 0.5;
                for (const auto &i: message) {
                    pos((data->gameSizeWidth - 2 - i.length()) / 2.0f, firstLine++);
                    printf("%s", i.c_str());
                }
                break;
            }
            case CENTER_LEFT: {
                short space = (data->gameSizeWidth - getMaxLength(message)) >> 1;
//                printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);
                clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
                pos(0, 1);
                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Snake's Heart(s): %d\n"
                       "║ - Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHigh, data->hearts, data->speed);
                short firstLine = (data->gameSizeHigh - 6) / 2.0 + 0.5;

                for (const string &i: message) {
                    pos(space, firstLine++);
                    printf("%s", i.c_str());
                }

                break;
            }
        }
    }

    void GUI::printDefaultBorder(short width, short high) {
        system("cls");
        pos(0, 0);
        printf("╔");
        printRepeat("═", width - 2);
        printf("╗\n");
        for (short i = 0; i < high - 2; ++i) {
            short posY = i + 1;
            pos(0, posY);
            printf("║");
            pos(width - 1, posY);
            printf("║");
        }
        printf("\n╚");
        printRepeat("═", width - 2);
        printf("╝");
    }

    void GUI::clearScreenWithoutBorder(short width, short height) {
        for (short i = 1; i < height - 1; ++i) {
            pos(1, i);
            printf(ESC"[%dX", width - 2);
        }
    }
}


namespace XsSetting {

    class Setting {
        vector<string> changeGameSizeWord{"←  Width  →    |    ↑  High  ↓"};
        vector<string> changeHeartsWord{"↑  Heart(s)  ↓"};
        vector<string> changeSpeedWord{"↑  Speed  ↓"};

    public:
        explicit Setting(Snake *data); // no error
        void start(); // no exit
        void changeGameSize(); // ! check whether string length suitable for new size
        void changeHeart(); // no error
        void changeSpeed(); // no error
    private:
        Snake *data;
    };

    Setting::Setting(Snake *data) {
        this->data = data;
    }

    void Setting::changeGameSize() {
        while (true) {
            XsUtil::GUI::printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);
            XsUtil::GUI::createMessage(changeGameSizeWord, CENTER, data);
            if (getch() == 224)
                switch (getch()) {
                    case 80:
                        // code for arrow down
                        if (data->gameSizeHeight < 255)
                            data->gameSizeHeight += 1;
                        break;
                    case 72:
                        // code for arrow up
                        if (data->gameSizeHeight > 1)
                            data->gameSizeHeight -= 1;
                        break;
                    case 145:
                        // code for ctrl arrow down
                        if (data->gameSizeHeight < 246)
                            data->gameSizeHeight += 10;
                        break;
                    case 141:
                        // code for ctrl arrow up
                        if (data->gameSizeHeight > 10)
                            data->gameSizeHeight -= 10;
                        break;
                        // ---------------------------------
                    case 75:
                        // code for arrow left
                        if (data->gameSizeWidth > 1)
                            data->gameSizeWidth -= 1;
                        break;
                    case 77:
                        // code for arrow right
                        if (data->gameSizeWidth < 255)
                            data->gameSizeWidth += 1;
                        break;
                    case 116:
                        // code for ctrl arrow right
                        if (data->gameSizeWidth < 246)
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

    void Setting::changeHeart() {
        while (true) {
            XsUtil::GUI::createMessage(changeHeartsWord, CENTER, data);
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

    void Setting::changeSpeed() {
        while (true) {
            XsUtil::GUI::createMessage(changeSpeedWord, CENTER, data);
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

    void Setting::start() {
        const short width = data->gameSizeWidth / 2 - 1;
        const short height = data->gameSizeHeight;

        char moveState = 'd';
        short area[height][width];
        // set area to 0 (default)
        for (auto &i: area)
            for (auto &j: i)
                j = AREA_AIR;

        // set spawnpoint
        short headx = width >> 1;
        short heady = height >> 1;
        area[heady][headx] = AREA_SNAKE_HEAD;

        // render setting
        float fps = 30;
        struct timeval last{}, now = {0, 0}, secTimer = {0, 0};
        long renderTime = 0;
        long maxRenTime = 0;
        long delayTime = 0;
        mingw_gettimeofday(&now, nullptr);

        // 按鍵監聽
        pthread_t keyListener;
        wchar_t key;
        pthread_create(&keyListener, nullptr, keyEvent, (void *) &key);

        //
        int q = fps / data->speed * 5;
        int timer = 0;
        while (true) {
            // render

            // get input
            switch (key) {
                case 'w':
                    moveState = 'w';
                    break;
                case 's':
                    moveState = 's';
                    break;
                case 'a':
                    moveState = 'a';
                    break;
                case 'd':
                    moveState = 'd';
                    break;
            }

            // 清除畫面
            XsUtil::GUI::clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
            printf(ESC"[1;1H");
            for (int i = 0; i < height; ++i) {
                printf(ESC"[%dd" ESC"[0m", i + 2);
                for (int j = 0; j < width; ++j) {
                    switch (area[i][j]) {
                        case AREA_SNAKE_HEAD:
                            printf(ESC"[%dG" ESC"[42m  ", j * 2 + 2);
                            break;
                        case AREA_SNAKE_BODY:
                            printf(ESC"[%dG" ESC"[43m  ", j * 2 + 2);
                            break;
                    }
                }
            }


            if (timer-- == 0) {
                timer = q;
                area[heady][headx] = AREA_SNAKE_BODY;
                data->x[data->offset + data->lengthNow] = headx;
                data->y[data->offset + data->lengthNow] = heady;
                data->lengthNow++;

                if (moveState == 'd')
                    headx++;
                else if (moveState == 'a')
                    headx--;
                else if (moveState == 'w')
                    heady--;
                else heady++;
                area[heady][headx] = AREA_SNAKE_HEAD;
            }

            // show info
            // struct rusage r_usage;
            // getrusage(RUSAGE_SELF, &r_usage);
//            sprintf(msg, "Size: %dx%d\tFPS: %.2f\t%.2fms/max: %.2fms\t change: %d",
//                    canvas.width, canvas.height,
//                    (renderTime + delayTime) == 0
//                    ? 1000000
//                    : 1000000.f / (renderTime + delayTime),
//                    (float)renderTime / 1000.f, (float)maxRenTime / 1000.f,
//                    canvas.changeLen
//            );
//            printStatusLine(msg);

//            sprintf(msgb, "Key: %d\t %d", key, 0);
//            printBottomLine(msgb);

            SetConsoleCursorPosition(console, {1, 1});
            printf("FPS: %.2f\t%.2fms/max: %.2fms %d   ",
                   (renderTime + delayTime) == 0 ? 1000000 : 1000000.f / (renderTime + delayTime),
                   (float) renderTime / 1000.f,
                   (float) maxRenTime / 1000.f,
                   headx
            );

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

void pos(short x, short y) {
    SetConsoleCursorPosition(console, {x, y});
}

#endif // MAIN_XSLIB_H
