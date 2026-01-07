#include <conio.h>
#include <dos.h>
#include <stdlib.h>

#define WIDTH   60
#define HEIGHT  20

#define ALIVE 1
#define DEAD  0

#define FRAME_DELAY     120
#define EVOLVE_INTERVAL 3
#define BEAT_INTERVAL   6

int grid[HEIGHT][WIDTH];
int next_grid[HEIGHT][WIDTH];

int generation = 0;
int frame = 0;

int scale[] = { 196, 220, 247, 262, 294, 330 };
int scale_len = 6;

void seed_grid(void)
{
    int x, y;
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;

    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            grid[y][x] = DEAD;

    grid[cy][cx]         = ALIVE;
    grid[cy][cx + 1]     = ALIVE;
    grid[cy + 1][cx]     = ALIVE;
    grid[cy + 1][cx + 1] = ALIVE;

    grid[cy][cx + 4] = ALIVE;
    grid[cy][cx + 5] = ALIVE;
    grid[cy][cx + 6] = ALIVE;

    grid[cy + 3][cx + 2] = ALIVE;
    grid[cy + 3][cx + 3] = ALIVE;
    grid[cy + 3][cx + 4] = ALIVE;
    grid[cy + 4][cx + 1] = ALIVE;
    grid[cy + 4][cx + 2] = ALIVE;
    grid[cy + 4][cx + 3] = ALIVE;
}

int count_neighbors(int y, int x)
{
    int dy, dx, count = 0;
    int ny, nx;

    for (dy = -1; dy <= 1; dy++)
        for (dx = -1; dx <= 1; dx++)
        {
            if (dy == 0 && dx == 0)
                continue;

            ny = (y + dy + HEIGHT) % HEIGHT;
            nx = (x + dx + WIDTH) % WIDTH;

            count += grid[ny][nx];
        }

    return count;
}

void update(void)
{
    int x, y, n;

    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
        {
            n = count_neighbors(y, x);

            if (grid[y][x] == ALIVE)
                next_grid[y][x] = (n == 2 || n == 3);
            else
                next_grid[y][x] = (n == 3);
        }

    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            grid[y][x] = next_grid[y][x];
}

void play_beep(void)
{
    static int last_alive = 0;
    int x, y;
    int alive = 0;
    int note;
    int duration;

    if (frame % BEAT_INTERVAL != 0)
        return;

    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            if (grid[y][x] == ALIVE)
                alive++;

    if (alive == 0)
        return;

    note = alive % scale_len;
    duration = (alive != last_alive) ? 60 : 25;

    sound(scale[note]);
    delay(duration);
    nosound();

    last_alive = alive;
}

void render(void)
{
    int x, y;

    for (y = 0; y < HEIGHT; y++)
    {
        gotoxy(1, y + 1);

        for (x = 0; x < WIDTH; x++)
        {
            if (grid[y][x] == ALIVE)
            {
                textcolor(YELLOW);
                putch(219);
            }
            else
            {
                textcolor(GREEN);
                putch(' ');
            }
        }
    }

    play_beep();
}

int main(void)
{
    textmode(C80);
    textbackground(GREEN);
    textcolor(YELLOW);
    clrscr();

    seed_grid();

    while (!kbhit())
    {
        render();

        if (frame % EVOLVE_INTERVAL == 0)
        {
            update();
            generation++;
        }

        frame++;
        delay(FRAME_DELAY);
    }

    nosound();
    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    clrscr();
    getch();

    return 0;
}
