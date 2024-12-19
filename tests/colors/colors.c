#include <stdio.h>

int main() {
    // Foreground colors
    printf("\033[41m" "\033[30m" " Black text on red bg " "\033[0m" "\n\n");
    printf("\033[30mBlack Text\033[0m\n");
    printf("\033[31mRed Text\033[0m\n");
    printf("\033[32mGreen Text\033[0m\n");
    printf("\033[33mYellow Text\033[0m\n");
    printf("\033[34mBlue Text\033[0m\n");
    printf("\033[35mMagenta Text\033[0m\n");
    printf("\033[36mCyan Text\033[0m\n");
    printf("\033[37mWhite Text\033[0m\n");

    // Background colors
    printf("\033[40mBlack Background\033[0m\n");
    printf("\033[41mRed Background\033[0m\n");
    printf("\033[42mGreen Background\033[0m\n");
    printf("\033[43mYellow Background\033[0m\n");
    printf("\033[44mBlue Background\033[0m\n");
    printf("\033[45mMagenta Background\033[0m\n");
    printf("\033[46mCyan Background\033[0m\n");
    printf("\033[47mWhite Background\033[0m\n");

    // Text styles
    printf("\033[1mBold Text\033[0m\n");
    printf("\033[4mUnderlined Text\033[0m\n");
    printf("\033[7mReversed Colors\033[0m\n");

    return 0;
}
