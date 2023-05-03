#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10
#define SHIPS 5

int board[ROWS][COLS];
int ships = SHIPS;

void init_board();
void print_board();
void place_ships();
int fire(int row, int col);
int is_sunk(int ship);
int is_valid(int row, int col);
//Ian Purkis Honors Project - ipurkis2 656176178
int main() {
    int row, col;
    init_board();
    place_ships();
    while (ships > 0) {
        print_board();
        printf("Enter row and column to fire (e.g. 3 5): ");
        scanf("%d %d", &row, &col);
        if (!is_valid(row, col)) {
            printf("Invalid input. Please enter a row and column between 1 and %d.\n", ROWS);
            continue;
        }
        if (fire(row - 1, col - 1)) {
            printf("Hit!\n");
            if (is_sunk(board[row - 1][col - 1])) {
                ships--;
                printf("You sunk a battleship! You have %d ships remaining.\n", ships);
            }
        } else {
            printf("Miss.\n");
        }
    }
    printf("You won!\n");
    return 0;
}

void init_board() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
}

void print_board() {
    int i, j;
    printf("  ");
    for (i = 0; i < COLS; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("%c ", 'A' + i);
        for (j = 0; j < COLS; j++) {
            switch (board[i][j]) {
                case 0:
                    printf(". ");
                    break;
                case 1:
                    printf("X ");
                    break;
                case 2:
                    printf("O ");
                    break;
            }
        }
        printf("\n");
    }
}

void place_ships() {
    int i;
    for (i = 0; i < SHIPS; i++) {
        int row, col;
        do {
            row = rand() % ROWS;
            col = rand() % COLS;
        } while (board[row][col] != 0);
        board[row][col] = i + 1;
    }
}

int fire(int row, int col) {
    if (board[row][col] != 0) {
        board[row][col] = 1;
        return 1;
    } else {
        board[row][col] = 2;
        return 0;
    }
}

int is_sunk(int ship) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == ship) {
                return 0;
            }
        }
    }
    return 1;
}

int is_valid(int row, int col) {
    if (row >= 1 && row <= ROWS && col >= 1 && col <= COLS)
        return 1;
    else
        return 0;
}
