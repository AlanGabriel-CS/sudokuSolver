#include <iostream>
#include <array>

#define SIZE 9

bool is_safe(const std::array<std::array<int, SIZE>, SIZE>& board, int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    for (int x = 0; x < SIZE; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Backtracking algorithm to solve the Sudoku
bool solve_sudoku(std::array<std::array<int, SIZE>, SIZE>& board) {
    int row, col;
    bool empty_found = false;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) { 
                empty_found = true;
                break;
            }
        }
        if (empty_found) break;
    }

    if (!empty_found) {
        return true;
    }

    // Try digits from 1 to 9
    for (int num = 1; num <= SIZE; num++) {
        // Check if it's safe to place num in the cell
        if (is_safe(board, row, col, num)) {
            board[row][col] = num;

            if (solve_sudoku(board)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    // Trigger backtracking
    return false;
}

void print_board(const std::array<std::array<int, SIZE>, SIZE>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void input_board(std::array<std::array<int, SIZE>, SIZE>& board) {
    std::cout << "Enter the Sudoku puzzle row by row (use 0 for empty cells):\n";
    for (int row = 0; row < SIZE; row++) {
        std::cout << "Enter row " << row + 1 << ": ";
        for (int col = 0; col < SIZE; col++) {
            std::cin >> board[row][col];
        }
    }
}

int main() {
    std::array<std::array<int, SIZE>, SIZE> board = {0};

    input_board(board);

    std::cout << "\nYour Sudoku puzzle (empty cells are represented by 0):\n";
    print_board(board);

    if (solve_sudoku(board)) {
        std::cout << "\nSolved Sudoku puzzle:\n";
        print_board(board);
    } else {
        std::cout << "\nNo solution exists for the Sudoku puzzle.\n";
    }

    return 0;
}
