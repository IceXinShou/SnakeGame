#ifndef MAIN_XSLIB_H
#define MAIN_XSLIB_H
#endif //MAIN_XSLIB_H

#include <bits/stdc++.h>

using namespace std;

struct SnakeData {
public:
    int gameSize = 30;
    int hearts = 3;
    int speed = 10;
};


namespace XsUtil {

#define CENTER 0
#define CENTER_LEFT 1
#define HIGH 30
#define WIDTH 70

    /**
     * GUI
     */


    class GUI {
        vector<string> mainWords{"<1> Start To Play", "<2> Settings", "<3> Exit"};
        vector<string> settingWords{"<1> Game Size", "<2> Snake's Hearts", "<3> Snake's Speed", "<4> Exit"};

    public:
        static void createMessage(const vector<string> &message, int position, SnakeData data) {
            switch (position) {
                case CENTER: {
                    system("cls");
                    printf("Current:\n\tGameSize: %d\n\tSnake's Heart(s): %d\n\tSnake's Speed: %d", (data).gameSize,
                           (data).hearts, (data).speed);
                    printRepeat('\n', (HIGH - message.size()) / 2 - 4);
                    for (const string &i: message) {
                        printf("\n");
                        printRepeat(' ', (WIDTH - i.length()) / 2);
                        printf("%s", i.c_str());
                    }
                    break;
                }
                case CENTER_LEFT: {
                    int space = (WIDTH - getMaxLength(message)) / 2;
                    system("cls");
                    printf("Current:\n\tGameSize: %d\n\tSnake's Heart(s): %d\n\tSnake's Speed: %d", (data).gameSize,
                           (data).hearts, (data).speed);
                    printRepeat('\n', (HIGH - message.size()) / 2 - 3);
                    for (const string &i: message) {
                        printRepeat(' ', space);
                        printf("%s\n", i.c_str());
                    }
                    break;
                }
            }
        };

        void main(SnakeData data) {
            XsUtil::GUI::createMessage(mainWords, CENTER_LEFT, data);
        }

        void setting(SnakeData data) {
            XsUtil::GUI::createMessage(settingWords, CENTER_LEFT, data);
        }

        static int getMaxLength(vector<string> words) {
            return (*std::max_element(words.begin(), words.end(),
                                      [](const auto &a, const auto &b) { return a.size() < b.size(); })).length();
        }

        static void printRepeat(char c, int count) {
            while (count--)
                printf("%c", c);
        }
    };
}


namespace XsSetting {

    /**
     * Setting
     */

    class Setting {
        vector<string> newGameSizeWord{"Type New Game Size (Default 30): "};
        vector<string> newHeartsWord{"Type New Snake's Heart(s) (Default 3): "};
        vector<string> newSpeedWord{"Type New Snake's Speed (Default 10): "};

    public:
        void changeGameSize(SnakeData data) {
            XsUtil::GUI::createMessage(newGameSizeWord, CENTER, data);
            scanf("%d", &data.gameSize);
        }

        void changeHeart(SnakeData data) {
            XsUtil::GUI::createMessage(newHeartsWord, CENTER, data);
            scanf("%d", &data.hearts);
        }

        void changeSpeed(SnakeData data) {
            XsUtil::GUI::createMessage(newSpeedWord, CENTER, data);
            scanf("%d", &data.speed);
        }

        void start() {

        }
    };
}
