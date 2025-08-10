#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

/// Sets the text (and optionally background) color for the Windows console.
inline void setColor(int textColor, int bgColor = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

/// Resets the console color to default (light gray / white).
inline void resetColor() {
    setColor(7);
}

/// Simulates a typing effect by printing characters one by one with a delay.
inline void typeWriter(const std::string &text, int delayMs = 25) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

/// Clears the console screen (Windows only).
inline void clearScreen() {
    system("cls");
}

/// Displays a simple loading animation "message...." with timed dots.
inline void loadingAnimation(const std::string &message, int dotCount = 10, int dotDelayMs = 200) {
    setColor(11); // Light Aqua for visual pop
    std::cout << message;
    resetColor();
    for (int i = 0; i < dotCount; ++i) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(dotDelayMs));
    }
    std::cout << "\n";
}

#endif // CONSOLE_UTILS_H
