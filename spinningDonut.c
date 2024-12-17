#include <stdio.h>
#include <string.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 22
#define SIZE 1760
#define CLEAR_SCREEN "\x1b[2J"
#define MOVE_CURSOR_TOP "\x1b[H"

int main()
{
    float A = 0, B = 0;
    char buffer[SIZE];
    float zbuffer[SIZE];

    printf(CLEAR_SCREEN);

    for (;;)
    {
        memset(buffer, ' ', SIZE);
        memset(zbuffer, 0, sizeof(zbuffer));

        for (float j = 0; j < 6.28; j += 0.07)
        {
            float cos_j = cos(j), sin_j = sin(j);

            for (float i = 0; i < 6.28; i += 0.02)
            {
                float sin_i = sin(i), cos_i = cos(i);
                float cos_A = cos(A), sin_A = sin(A);
                float cos_B = cos(B), sin_B = sin(B);

                float h = cos_j + 2;
                float D = 1 / (sin_i * h * sin_A + sin_j * cos_A + 5);
                float t = sin_i * h * cos_A - sin_j * sin_A;

                int x = WIDTH / 2 + (30 * D * (cos_i * h * cos_B - t * sin_B));
                int y = HEIGHT / 2 + (15 * D * (cos_i * h * sin_B + t * cos_B));

                int o = x + WIDTH * y;
                int luminance = 8 * ((sin_j * sin_A - sin_i * cos_j * cos_A) * cos_B - sin_i * cos_j * sin_A - sin_j * cos_A - cos_i * cos_j * sin_B);

                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && D > zbuffer[o])
                {
                    zbuffer[o] = D;
                    buffer[o] = ".,-~:;=!*#$@"[luminance > 0 ? luminance : 0];
                }
            }
        }

        printf(MOVE_CURSOR_TOP);
        for (int k = 0; k < SIZE; k++)
        {
            putchar(k % WIDTH ? buffer[k] : '\n');
        }

        A += 0.04;
        B += 0.08;
    }
    return 0;
}
