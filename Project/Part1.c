// Part 1: Manual Maze Navigation with Point Collection (macOS compatible)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_ROWS 50
#define MAX_COLS 50
#define TIME_LIMIT 60

char maze[MAX_ROWS][MAX_COLS];
int rows = 0, cols = 0;


char getch(void) {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(STDIN_FILENO, &old) < 0) return 0;
    old.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) return 0;
    if (read(STDIN_FILENO, &buf, 1) < 0) buf = 0;
    old.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return buf;
}


void import_maze(const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (!fp) {
        printf("Failed to open maze file.\n");
        exit(1);
    }

    char line[MAX_COLS];
    while (fgets(line, sizeof(line), fp)) {
        cols = strlen(line);
        if (line[cols - 1] == '\n') cols--;
        for (int j = 0; j < cols; j++)
            maze[rows][j] = line[j];
        rows++;
    }
    fclose(fp);
}

void print_maze(int cur_r, int cur_c, int score, int time_left) {
    system("clear");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == cur_r && j == cur_c)
                printf("A");
            else
                printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    printf("\nScore: %d | Time Left: %d seconds\n", score, time_left);
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}


int main() {
    int cur_r, cur_c;
    int score = 0;
    time_t start_t, end_t;
    char c;

    import_maze("maze.txt");

    srand(time(NULL));
    while (1) {
        cur_r = rand() % rows;
        cur_c = rand() % cols;
        if (maze[cur_r][cur_c] == ' ')
            break;
    }

    time(&start_t);

    while (1) {
        time(&end_t);
        int elapsed = (int)difftime(end_t, start_t);
        if (elapsed >= TIME_LIMIT)
            break;

        print_maze(cur_r, cur_c, score, TIME_LIMIT - elapsed);

        c = getch();

        int new_r = cur_r;
        int new_c = cur_c;

        if (c == '\033') {        // arrow keys
            getch();              // skip '['
            c = getch();
            if (c == 'A') new_r--;       // up
            else if (c == 'B') new_r++;  // down
            else if (c == 'D') new_c--;  // left
            else if (c == 'C') new_c++;  // right
        }

        if (new_r >= 0 && new_r < rows &&
            new_c >= 0 && new_c < cols &&
            maze[new_r][new_c] != '*') {

            cur_r = new_r;
            cur_c = new_c;

            if (is_digit(maze[cur_r][cur_c])) {
                score += maze[cur_r][cur_c] - '0';
                maze[cur_r][cur_c] = ' ';
            }
        }
    }

    system("clear");
    printf("Time's up!\nFinal Score: %d\n", score);
    return 0;
}
