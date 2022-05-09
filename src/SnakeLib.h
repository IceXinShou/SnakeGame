#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H

#include <bits/stdc++.h>
#include <conio.h>


#define CENTER 0
#define CENTER_LEFT 1

// ***
#define AREA_FOOD 2
#define AREA_AIR 0
#define AREA_SNAKE_HEAD -1
#define AREA_SNAKE_BODY -2
// ***

#define ESC "\x1B"


using namespace std;

HANDLE console; // batch setting handler
static void errorPrint(int errorCode); // game crash or report
static void printRepeat(const char &c, int count); // repeat print out char
static void printRepeat(const string &c, int count); // repeat print out string
static void pos(short y, short x); // pos
int checkTouch(const unsigned short ax[255 * 255], const unsigned short ay[255 * 255], unsigned int x, unsigned int y,
               unsigned int length,
               unsigned int offset); // check touch

struct Snake {
public:
    unsigned short snakex[255 * 255]{};
    unsigned short snakey[255 * 255]{};
    unsigned short foodx[255 * 255]{};
    unsigned short foody[255 * 255]{};
    unsigned int foodCount = 2;
    unsigned int length = 3;
    unsigned int lengthNow = 0;
    unsigned int offset = 0;
    unsigned short gameSizeWidth = 60; // game size width
    unsigned short gameSizeHeight = 30; // game size high
    unsigned int hearts = 3; // snake's hearts
    unsigned int speed = 30; // snake's speed

    void init(); // init snake
};

void Snake::init() {
    length = 3;
    lengthNow = 0;
    offset = 0;

}

namespace XsUtil {

    class GUI {
        vector<string> mainWords = {"<ENTER> Start To Play", "<O> Settings", "<ESC> Exit"};
        vector<string> settingWords = {"<1> Game Size", "<2> Snake's Hearts", "<3> Snake's Speed", "<ESC> Exit"};

    public:
        explicit GUI(Snake *data) { this->data = data; }; // constructor
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

                SetConsoleCursorPosition(console, {0, 1});

                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Snake's Heart(s): %d\n"
                       "║ - Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHeight, data->hearts, data->speed);
                short firstLine = (data->gameSizeHeight - 6) / 2.0 + 0.5;
                for (const auto &i: message) {
                    SetConsoleCursorPosition(console,
                                             {short((data->gameSizeWidth - 2 - i.length()) / 2.0f), firstLine++});
                    printf("%s", i.c_str());
                }
                break;
            }
            case CENTER_LEFT: {
                short space = (data->gameSizeWidth - getMaxLength(message)) >> 1;
//                printDefaultBorder(data->gameSizeWidth, data->gameSizeHeight);
                clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
                SetConsoleCursorPosition(console, {0, 1});
                printf(""
                       "║ Current:\n"
                       "║ - GameSize: %d * %d\n"
                       "║ - Snake's Heart(s): %d\n"
                       "║ - Snake's Speed: %d\n",
                       data->gameSizeWidth, data->gameSizeHeight, data->hearts, data->speed);
                short firstLine = (data->gameSizeHeight - 6) / 2.0f + 0.5f;

                for (const string &i: message) {
                    SetConsoleCursorPosition(console, {space, firstLine++});
                    printf("%s", i.c_str());
                }

                break;
            }
        }
    }

    void GUI::printDefaultBorder(short width, short high) {
        system("cls");
        SetConsoleCursorPosition(console, {0, 0});
        printf("╔");
        printRepeat("═", width - 2);
        printf("╗\n");
        for (short i = 0; i < high - 2; ++i) {
            short posY = i + 1;
            SetConsoleCursorPosition(console, {0, posY});
            printf("║");
            SetConsoleCursorPosition(console, {short(width - 1), posY});
            printf("║");
        }
        printf("\n╚");
        printRepeat("═", width - 2);
        printf("╝");
    }

    void GUI::clearScreenWithoutBorder(short width, short height) {
        for (short i = 1; i < height - 1; ++i) {
            SetConsoleCursorPosition(console, {1, i});
            printf(ESC"[%dX", width - 2);
        }
    }
}


namespace XsSetting {

    class Setting {
        vector<string> gameOverWord = {"You Lose!"/*, "Press any key to continue"*/};
        vector<string> changeGameSizeWord = {"←  Width  →    |    ↑  High  ↓"};
        vector<string> changeHeartsWord = {"↑  Heart(s)  ↓"};
        vector<string> changeSpeedWord = {"↑  Speed  ↓"};

    public:
        explicit Setting(Snake *data) { this->data = data; }; // no error
        static void *keyEvent(void *wch); // no error
        void start(); // no exit
        void changeGameSize(); // ! check whether string length suitable for new size
        void changeHeart(); // no error
        void changeSpeed(); // no error
    private:
        Snake *data;
    };

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

    void *Setting::keyEvent(void *wch) {
        long usec = 100;
        struct timespec threadDelay = {usec / 1000000, (usec % 1000000) * 1000};
        while (*(wchar_t *) wch != '\r') {
            *(wchar_t *) wch = _getwch();
            nanosleep(&threadDelay, &threadDelay);
        }
        pthread_exit(nullptr);//
    }//

    void Setting::start() {
        XsUtil::GUI::clearScreenWithoutBorder(data->gameSizeWidth, data->gameSizeHeight);
        data->init();
        bool dead = false;
        const short width = data->gameSizeWidth / 2 - 1;
        const short height = data->gameSizeHeight - 1;

//            data->foodx[0] =5;
//            data->foody[0] =2;

        for (int i = 0; i < data->foodCount; ++i) {
            int x, y;
            while (checkTouch(data->foodx, data->foody,
                              (x = rand() % (width - 1) + 1), (y = rand() % (height - 1) + 1),
                              data->foodCount, 0
            ) > -1);
            data->foodx[i] = x;
            data->foody[i] = y;
            pos(data->foody[i], data->foodx[i] * 2);
            printf(ESC"[41m  ");
        }

        char moveState = 'd';
        char oldMoveState = ' ';

        // set spawnpoint
//        unsigned short headx = width >> 1;
//        unsigned short heady = height >> 1;
        unsigned short headx = 1;
        unsigned short heady = 2;
        unsigned short oldX = headx, oldY = heady;

        // render setting
        float fps = data->speed;
        struct timeval last{}, now = {0, 0}, secTimer = {0, 0};
        long renderTime = 0;
        long maxRenTime = 0;
        long delayTime = 0;
        mingw_gettimeofday(&now, nullptr);

        // 按鍵監聽
        pthread_t keyListener;
        wchar_t key = '\0';
        pthread_create(&keyListener, nullptr, keyEvent, (void *) &key);

//        int q = fps / data->speed * 5;
        int q = 1;
        int timer = 0;

        while (true) {
            // get input
            switch (key) {
                case 'w':
                    if (oldMoveState != 's')
                        moveState = 'w';
                    break;
                case 's':
                    if (oldMoveState != 'w')
                        moveState = 's';
                    break;
                case 'a':
                    if (oldMoveState != 'd')
                        moveState = 'a';
                    break;
                case 'd':
                    if (oldMoveState != 'a')
                        moveState = 'd';
                    break;
            }



            // ---------------------

//            if (!initDone) {
//                pos(heady, headx * 2);
//                printf(ESC"[43m  ");
//
//                // change old head to body
//                pos(oldY, oldX * 2);
//                printf(ESC"[42m  ");
//            } else {
            // set new head
            pos(heady, headx * 2);
            printf(ESC"[43m  ");

            // change old head to body
            pos(oldY, oldX * 2);
            printf(ESC"[42m  ");

            // remove tail
            if (data->lengthNow == data->length) {
                pos(data->snakey[data->offset], data->snakex[data->offset] * 2);
                printf(ESC"[0m  ");
            }
//            }

            // ---------------------

            // 清除畫面
            /*
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
        */
            // 更新蛇
            if (timer-- == 0) {
                timer = q; // reset timer
                // 更新蛇資料
                data->snakex[data->offset + data->lengthNow] = headx; // set snakex
                data->snakey[data->offset + data->lengthNow] = heady; // set snakey
                oldMoveState = moveState;
                switch (moveState) {
                    case 'd':
                        oldX = headx++;
                        oldY = heady;
                        break;
                    case 'a':
                        oldX = headx--;
                        oldY = heady;
                        break;
                    case 'w':
                        oldY = heady--;
                        oldX = headx;
                        break;
                    case 's':
                        oldY = heady++;
                        oldX = headx;
                        break;
                }

                // 判斷新狀態
                int i;
                if (headx <= 0 || headx >= width || heady <= 0 || heady >= height) {
                    dead = true;
                } else if (checkTouch(data->snakex, data->snakey, headx, heady, data->lengthNow,
                                      data->offset) > -1) { // if head is body
                    dead = true;
                } else if ((i = checkTouch(data->foodx, data->foody, headx, heady, data->foodCount, 0)) >
                           -1) { // if head is food
                    data->length++;
                    int x, y;
                    while (checkTouch(data->foodx, data->foody,
                                      (x = rand() % (width - 2) + 1), (y = rand() % (height - 2) + 1),
                                      data->foodCount, 0) > -1 &&
                           checkTouch(data->snakex, data->snakey, x, y,
                                      data->lengthNow, data->offset) > -1);
                    data->foodx[i] = x;
                    data->foody[i] = y;
                    pos(y, x * 2);
                    printf(ESC"[41m  ");
                }

                if (dead) {
                    XsUtil::GUI::createMessage(gameOverWord, CENTER, data);
                    return;
                }

//                // 更新蛇長度
//                if (initDone) // if init done
//                    data->offset++;
//                else if (++data->lengthNow == data->length) { // if length is full
//                    initDone = true;
//                }

                if (data->lengthNow == data->length)
                    data->offset++;
                else
                    data->lengthNow++;
            }

            SetConsoleCursorPosition(console, {1, 1});

            printf(ESC"[0m" ESC"[%dXFPS: %.2f\tRender Used: %.2fms / Max: %.2fms ",
                   data->gameSizeWidth - 2,
                   (renderTime + delayTime) == 0 ? 1000000 : 1000000.f / (renderTime + delayTime),
                   (float) renderTime / 1000.f,
                   (float) maxRenTime / 1000.f
            );

            // timer
            last = now;
            mingw_gettimeofday(&now, nullptr);
            renderTime = (now.tv_sec - last.tv_sec) * 1000000L +
                         (now.tv_usec - last.tv_usec);
            if ((now.tv_sec - secTimer.tv_sec) * 1000000L +
                (now.tv_usec - secTimer.tv_usec) >
                1000000L) {
                secTimer = now;
                maxRenTime = renderTime;
            }
            if (renderTime > maxRenTime) maxRenTime = renderTime;

            // update delay
            delayTime = 1000000 / fps - renderTime;
            if (delayTime > 0) {
                struct timespec ts = {0, delayTime * 1000};
                nanosleep(&ts, &ts);
            } else
                delayTime = 0;
            mingw_gettimeofday(&now, nullptr);

            if (key == '\r')
                break;
        }
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

int checkTouch(const unsigned short ax[255 * 255], const unsigned short ay[255 * 255], unsigned int x, unsigned int y,
               unsigned int length,
               unsigned int offset) {

    for (int i = 0; i < length; ++i)
        if (ax[offset + i] == x && ay[offset + i] == y)
            return i; // return touched index

    return -1; // not touch
}

static void pos(short y, short x) {
    SetConsoleCursorPosition(console, {x, y});
}


#endif // MAIN_XSLIB_H