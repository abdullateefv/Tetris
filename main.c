/**
 * Abdul Lateef FNU
 * CS288 Itani
 * 2-19-2023
 */

#include <stdio.h>

void rotate(int pento[4][4], int numRotations) {
    int temp;
    int r, i , j;

    for ( r = 0; r < numRotations; r++) {
        for ( i = 0; i < 2; i++) {
            for ( j = i; j < 3 - i; j++) {
                temp = pento[i][j];
                pento[i][j] = pento[3 - j][i];
                pento[3 - j][i] = pento[3 - i][3 - j];
                pento[3 - i][3 - j] = pento[j][3 - i];
                pento[j][3 - i] = temp;
            }
        }
    }
}

int getLeftmost(int pento[4][4]) {
    int x, y;
    for ( y = 0; y < 4; y++) {
        for ( x = 0; x < 4; x++) {
            if (pento[x][y] == 1) {
                return y;
            }
        }
    }
    return -1;
}

int isPlaced(int placedCoords[5][2], int x, int y) {
    int i;
    for ( i = 0; i < 5; i++) {
        if (placedCoords[i][0] == x && placedCoords[i][1] == y) {
            return 1;
        }
    }
    return 0;
}

int checkCanMoveDown(int shaft[14][12], int placedCoords[5][2]) {
    int canMoveDown = 1;

    int i;
    for (i = 0; i < 5; i++) {
        int y = placedCoords[i][0];
        int x = placedCoords[i][1];

        if (isPlaced(placedCoords, y+1, x)) {
            continue;
        }

        if (shaft[y+1][x] != 0) {
            canMoveDown = 0;
        }
    }

    return canMoveDown;
}

void fixInPlace(int shaft[14][12], int placedCoords[5][2]) {
    int i;
    for (i = 0; i < 5; i++) {
        int y = placedCoords[i][0];
        int x = placedCoords[i][1];
        shaft[y][x] = 2;
    }
}

void clearRow(int shaft[14][12], int rowIndex) {
    int emptyRow[12] = {7,0,0,0,0,0,0,0,0,0,0,7};

    int i, j;
    for (i = rowIndex; i > 4; i--) {
        for (j = 0; j < 12; j++) {
            shaft[i][j] = shaft[i-1][j];
        }
    }

    for (i = 0; i < 12; i++) {
        shaft[4][i] = emptyRow[i];
    }
}

void checkAndClearRows(int shaft[14][12]) {
    int y, x;
    for (y = 4; y < 13; y++) {
        int filledNum = 0;
        for (x = 1; x < 11; x++) {
            if (shaft[y][x] != 0)
                filledNum++;
        }
        if (filledNum == 10)
            clearRow(shaft, y);
    }
}

void place(int pentomino[4][4], int shaft[14][12], int position) {

    int leftMost = getLeftmost(pentomino);
    int placementPosition = position + 1;
    int vertical, horizontal;
    int numPlaced = 0;
    int placedCoords[5][2];

    for (vertical = 0; vertical < 4; vertical++) {
        int pentominoHoriz = leftMost;
        for (horizontal = placementPosition; horizontal < placementPosition + 4 - leftMost; horizontal++) {
            if (pentomino[vertical][pentominoHoriz] == 1) {
                shaft[vertical][horizontal] = 1;
                placedCoords[numPlaced][0] = vertical;
                placedCoords[numPlaced][1] = horizontal;
                numPlaced++;
            }
            pentominoHoriz++;
        }
    }

    while (checkCanMoveDown(shaft, placedCoords) == 1) {
        int i;
        for (i = 4; i >= 0; i--) {
            int y = placedCoords[i][0];
            int x = placedCoords[i][1];
            shaft[y][x] = 0;
            placedCoords[i][0] = y + 1;
            placedCoords[i][1] = x;
            shaft[y+1][x] = 1;
        }
    }

    fixInPlace(shaft, placedCoords);
    checkAndClearRows(shaft);
}

void printShaft(int shaft[14][12]) {
    int y, x;
    for ( y = 0; y < 14; y++) {
        for ( x = 0; x < 12; x++) {
            if (shaft[y][x]==1) {
                printf("X");
            } else if (shaft[y][x]==0) {
                printf(" ");
            } else if (shaft[y][x]==7) {
                printf("|");
            } else if (shaft[y][x]==8) {
                printf("*");
            } else if (shaft[y][x]==9) {
                printf("-");
            } else if (shaft[y][x]==2) {
                printf("#");
            }
        }
        printf("\n");
    }
}

int main() {

    int pentominoB[4][4] = {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}
    };

    int pentominoD[4][4] = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0}
    };

    int pentominoG[4][4] = {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0}
    };

    int pentominoH[4][4] = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0}
    };

    int pentominoM[4][4] = {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0}
    };

    int pentominoN[4][4] = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0}
    };

    int shaft[14][12] = {
             {0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0},
             {7,0,0,0,0,0,0,0,0,0,0,7},
             {7,0,0,0,0,0,0,0,0,0,0,7},
             {7,0,0,0,0,0,0,0,0,0,0,7},
             {7,0,0,0,0,0,0,0,0,0,0,7},
             {7,0,0,0,0,0,0,0,0,0,0,7},
             {7,0,0,0,0,0,0,0,0,0,0,7},
            {7,0,0,0,0,0,0,0,0,0,0,7},
            {7,0,0,0,0,0,0,0,0,0,0,7},
            {7,0,0,0,0,0,0,0,0,0,0,7},
            {8,9,9,9,9,9,9,9,9,9,9,8}
    };

    FILE *file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }

    char id;
    int rotations, column;
    while (fscanf(file, " %c r%d c%d ", &id, &rotations, &column) == 3) {

        int realRotations = rotations % 4;
        int backwardsRotations = 4 - realRotations;

        if (id == 'B') {
            rotate(pentominoB, realRotations);
            place(pentominoB, shaft, column);
            rotate(pentominoB, backwardsRotations);
        } else if (id == 'D') {
            rotate(pentominoD, realRotations);
            place(pentominoD, shaft, column);
            rotate(pentominoD, backwardsRotations);
        } else if (id == 'G') {
            rotate(pentominoG, realRotations);
            place(pentominoG, shaft, column);
            rotate(pentominoG, backwardsRotations);
        } else if (id == 'H') {
            rotate(pentominoH, realRotations);
            place(pentominoH, shaft, column);
            rotate(pentominoH, backwardsRotations);
        } else if (id == 'M') {
            rotate(pentominoM, realRotations);
            place(pentominoM, shaft, column);
            rotate(pentominoM, backwardsRotations);
        } else if (id == 'N') {
            rotate(pentominoN, realRotations);
            place(pentominoN, shaft, column);
            rotate(pentominoN, backwardsRotations);
        }
    }

    fclose(file);
    printShaft(shaft);
    return 0;
}