#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define played 1
#define position_occupied -1
#define position_invalid -10

//  X|O|X
//  O|X|O
//  X|O|X

void set_game (char hash[3][5]);
void print_game (char hash[3][5]);
void set_game_Positions (char hash_Position[3][5]);
int play (char position, char hash[3][5], char player);
void tic_tac_toe (char position, char hash_Position[3][5], char hash[3][5]);
bool check_winner (char hash[3][5], char player);

int main () {

    //bool control = true;
    char hash[3][5];
    char hash_Position[3][5];

    set_game (hash);
    set_game_Positions (hash_Position);

    char position;
    tic_tac_toe (position, hash_Position, hash);

    return 0;
}

void tic_tac_toe (char position, char hash_Position[3][5], char hash[3][5]) {
    bool noWinner = true;
    char player;
    int i = 0;
    while (noWinner && i < 9) {

        if (i % 2 == 0) {
            printf("Player X:\n");
            player = 'X';
        }
        else {
            printf("Player O:\n");
            player = 'O';
        }
    
        print_game (hash);
        printf("\n");
        printf("posicoes:\n");
        print_game (hash_Position);
        printf("\n");
        printf("Escolha uma posicao: ");
        scanf("%c", &position);
        getchar();
        system("clear");

        int result = play (position, hash, player);
    
        if (position_occupied == result) {
            printf("Esta posicao ja esta ocupada!\n");
        }
        else if (position_invalid == result) {
            printf("Escolha uma posicao valida!\n");
        }
        else i++;

        bool winner = check_winner (hash, player);

        if (winner) {
            noWinner = false;
            printf ("Player: %c won!\n", player);
            print_game (hash);
        }
        else if (i == 9) {
            printf ("it's a draw!\n");
            print_game (hash);
        }
    }
    //return i;
}

void set_game (char hash[3][5]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j % 2 != 0) {
                hash[i][j] = '|';
            }
            else 
                hash[i][j] = '-';
        }
    }
}

void print_game (char hash[3][5]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++)
            printf ("%c", hash[i][j]);
        printf("\n");
    }
}

void set_game_Positions (char hash[3][5]) {

    char position = 'A';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j % 2 != 0) {
                hash[i][j] = '|';
            }
            else {
                hash[i][j] = position;
                position++;
            }
        }
    }
}

int play (char position, char hash[3][5], char player) {

    if (!((position >= 'A' && position <= 'I') || (position >= 'a' && position <= 'i'))) {
        return position_invalid;
    }
    else {
        bool found = false;
        char character = 'A';
        if (position >= 'a' && position <= 'i')
            position -= 32;
        for (int i = 0; i < 3 && !found; i++) {
            for (int j = 0; j < 5; j++) {
                if (j % 2 == 0) {
                    if (character == position) {
                        if (hash[i][j] != '-') {
                            return position_occupied;
                        }
                        else {
                            hash[i][j] = player;
                            found = true;
                            break;
                        }
                    }
                    else
                        character++;
                }
            }
        }
    return played;
    }
}

bool check_winner (char hash[3][5], char player) {

    // search line
    bool winner = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (j % 2 == 0) {
                if (hash[i][j] != player) {
                    winner = false;
                    break;
                }
                else winner = true;
            }
        }
        if (winner) return true;
    }

    // search column
    for (int j = 0; j < 5; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < 3; i++) {
                if (hash[i][j] != player) {
                    winner = false;
                    break;
                }
                else winner = true;
            }
        }
        if (winner) return true;
    }

    // main diagonal
    for (int i = 0, j = 0; i < 3; i++, j += 2) {
        if (hash[i][j] != player) {
            winner = false;
            break;
        }
        else winner = true;
    }
    if (winner) return true;

    // secondary diagonal
    for (int i = 0, j = 4; i < 3; i++, j -= 2) {
        if (hash[i][j] != player) {
            winner = false;
            break;
        }
        else winner = true;
    }
    if (winner) return true;

    return false;
}

    // teste
    /* char position = 'A';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'A';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'z';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'b';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'c';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'e';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'f';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'g';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'h';
    i = tic_tac_toe (position, hash_Position, hash, i);
    position = 'i';
    tic_tac_toe (position, hash_Position, hash, i); */