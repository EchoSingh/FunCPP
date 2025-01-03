#include <windows.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <thread>
#include <chrono>

void DrawDonut() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];

    std::cout << "\x1b[2J";

    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);

        for (j = 0; j < 6.28f; j += 0.07f) {
            for (i = 0; i < 6.28f; i += 0.02f) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = static_cast<int>(40 + 30 * D * (l * h * m - t * n));
                int y = static_cast<int>(12 + 15 * D * (l * h * n + t * m));
                int o = x + 80 * y;
                int N = static_cast<int>(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));

                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        std::cout << "\x1b[H";
        for (k = 0; k < 1760; k++) {
            std::cout.put(k % 80 ? b[k] : '\n');
        }

        A += 0.04f;
        B += 0.02f;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole();
    FILE* consoleOutput;
    freopen_s(&consoleOutput, "CONOUT$", "w", stdout);

    DrawDonut();

    fclose(consoleOutput);
    return 0;
}
