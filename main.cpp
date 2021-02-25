#include <iostream>
#include <bits/stdc++.h>
#include <string>

#define ROWS_COLUMNS 10


void print_the_matrix(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    std::cout << "matrix start :: " << std::endl;
    
    for (int i = 0;  i < ROWS_COLUMNS; i++) {
        for (int j = 0; j < ROWS_COLUMNS; j++) {
            std::cout << list[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << "matrix end :: " << std::endl;
}

void print_live_field(char (&list)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    for (int i = 0;  i < ROWS_COLUMNS; i++) {
        for (int j = 0; j < ROWS_COLUMNS; j++) {
            std::cout << list[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

bool check_position(int row, int column) {
    return row >= 0 && column >=0 && row < ROWS_COLUMNS && column < ROWS_COLUMNS;
}

bool check_mine_field(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column) {
    return (list[row][column] == -1);
}

void open_field() {

}

void set_mines_field(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int value) {
    // let us set mines where m = n and m + n equals some value say 7 here
    for (int i = 0, j = 0; i < ROWS_COLUMNS ; i++) {
        for (int j = 0; j < ROWS_COLUMNS; j++) {
            if ( (i == j) || (((i + j ) > 0 ) && ((i + j) % 7) == 0)) {
                list[i][j] = -1;
            }
        }
    }

    // update the remaining entries with values corresponding number of mines to adjacent squares
    for (int i = 0;  i < ROWS_COLUMNS; i++) {
        for (int j = 0; j < ROWS_COLUMNS; j++) {
            // move on once mine is encountered
            if (list[i][j] == -1) {
                continue;
            }
            // form the adjacent square by incrementing and decrementing row by 1, similarly with column and 
            // both at the same time
            int field_value = 0;

            if (check_position(i, j + 1)) {
                field_value = check_mine_field(list, i, j + 1) ? field_value + 1 : field_value;
            }

            if (check_position(i, j - 1)) {
                field_value = check_mine_field(list, i, j - 1) ? field_value + 1 : field_value;
            }

            if (check_position(i + 1, j)) {
                field_value = check_mine_field(list, i + 1, j) ? field_value + 1 : field_value;
            }

            if (check_position(i - 1, j)) {
                field_value = check_mine_field(list, i - 1 , j) ? field_value + 1 : field_value;
            }


            if (check_position(i + 1, j + 1)) {
                field_value = check_mine_field(list, i + 1, j + 1) ? field_value + 1 : field_value;
            }

            if (check_position(i - 1, j - 1)) {
                field_value = check_mine_field(list, i - 1, j - 1) ? field_value + 1 : field_value;
            }

            list[i][j] = field_value;
            
        }
    }
}

bool decrement_columns(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }
    if (check_position(row, column - 1)) {
        if ( list[row][column - 1] == 0) {
            return decrement_columns(list, row, column - 1, live_field);
        } else {
            live_field[row][column - 1] = '0' + list[row][column - 1];
        }
    }
    return true;
}

bool increment_rows_columns(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }
    if (check_position(row + 1, column + 1)) {
        if ( list[row + 1][column + 1] == 0) {
            return decrement_columns(list, row + 1, column + 1, live_field);
        } else {
            live_field[row + 1][column + 1] = '0' + list[row + 1][column + 1];
        }
    }
    return true;
}

bool decrement_rows(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // std::cout << "increment_colunms  with row :: " << row << " by column:: " << column << " with value :: " << live_field[row][column] << std::endl;
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }
    if (check_position(row - 1, column)) {
        if ( list[row - 1][column] == 0) {
            return decrement_columns(list, row - 1, column, live_field);
        } else {
            live_field[row - 1][column] = '0' + list[row - 1][column];
        }
    }
    return true;
}

bool increment_rows(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        // std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }

    if (check_position(row + 1, column)) {
        if ( list[row + 1][column] == 0) {
            return decrement_columns(list, row + 1, column, live_field);
        } else {
            live_field[row + 1][column] = '0' + list[row + 1][column];
        }
    }
    return true;
}

bool increment_columns(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }

    if (check_position(row, column + 1)) {
        if (list[row][column + 1] == 0) {
            return increment_columns(list, row, column + 1, live_field);
        } else {
            live_field[row][column + 1] = '0' + list[row][column + 1];
        }
    }

    
    return true;
}

bool decrement_rows_columns(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (!check_position(row, column)) {
        std::cout << "Exceeded the size, return immediately: with row :: " << row << " by column:: " << column << std::endl;
        return true;
    }

    live_field[row][column] = '0' + list[row][column];
    // in case the opened field is other than zero, let the user to continue the game
    if (list[row][column] != 0) {
        // we have encountered non-zero entry, so lets print the live field and move on
        // std::cout << "non-zero return immediately" << std::endl;
        return true;
    }
    if (check_position(row - 1, column - 1)) {
        if ( list[row - 1][column - 1] == 0) {
            return decrement_columns(list, row - 1, column - 1, live_field);
        } else {
            live_field[row - 1][column - 1] = '0' + list[row - 1][column - 1];
        }
    }
    return true;
}

bool play_the_game(int (&list)[ROWS_COLUMNS][ROWS_COLUMNS], int row, int column, char (&live_field)[ROWS_COLUMNS][ROWS_COLUMNS]) {
    if (list[row][column] == -1) {
        std::cout << "Encountered mine: " << std::endl;
        print_the_matrix(list);
        return false;
    }
    
    // check the adjacent squares for zero and open them for the input row and column
    increment_rows(list, row, column, live_field);
    increment_columns(list, row, column, live_field);
    increment_rows_columns(list, row, column, live_field);
    decrement_rows_columns(list, row, column, live_field);
    decrement_rows(list, row, column, live_field);
    decrement_columns(list, row, column, live_field);
    return true;
}


int main() {
    std::cout << "Enter minesweeper" <<  std::endl;
    int initial_set[ROWS_COLUMNS][ROWS_COLUMNS];
    memset(initial_set, 0, sizeof(initial_set));
    
    print_the_matrix(initial_set);

    int value = 7;

    std::cout << "time to set the mine field:: we can set mines at rows + columns equals to input value  " << std::endl;
    std::cin >> value;
    set_mines_field(initial_set, value);
    int row = 0, column = 0;
    char live_field[ROWS_COLUMNS][ROWS_COLUMNS];

    memset(live_field, '*', sizeof(live_field));
    while (1) {
        std::cout << "Lets play " << std::endl;
        print_live_field(live_field);
        std::cout << "Enter the row position" << std::endl;
        std::cin >> row;
        std::cout << "Enter the column position" << std::endl;
        std::cin >> column;
        if (!check_position(row, column)) {
            std::cout << "enter valid position as the matrix is " << ROWS_COLUMNS << " by " << ROWS_COLUMNS << std::endl;
            continue;
        }
        if (!play_the_game(initial_set, row, column, live_field)) {
            std::cout << "Game over" << std::endl;
            break;
        }
    }
    return 1;
}