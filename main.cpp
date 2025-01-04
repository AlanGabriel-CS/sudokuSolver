#include <iostream>
#include <array>

#define SIZE 9

// Function to check if it's safe to place a number at a given position
bool is_safe(const std::array<std::array<int, SIZE>, SIZE>& board, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < SIZE; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
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

    // Find the next empty cell
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) { // 0 represents empty cell
                empty_found = true;
                break;
            }
        }
        if (empty_found) break;
    }

    // If no empty cell is found, the board is solved
    if (!empty_found) {
        return true;
    }

    // Try digits from 1 to 9
    for (int num = 1; num <= SIZE; num++) {
        // Check if it's safe to place num in the cell
        if (is_safe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively attempt to solve the board
            if (solve_sudoku(board)) {
                return true;
            }

            // Backtrack if placing num didn't lead to a solution
            board[row][col] = 0;
        }
    }

    // Trigger backtracking
    return false;
}

// Function to print the Sudoku board
void print_board(const std::array<std::array<int, SIZE>, SIZE>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to input the Sudoku puzzle from the user
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
    // Sudoku puzzle array
    std::array<std::array<int, SIZE>, SIZE> board = {0};

    // Input the puzzle from the user
    input_board(board);

    std::cout << "\nYour Sudoku puzzle (empty cells are represented by 0):\n";
    print_board(board);

    // Solve the Sudoku puzzle
    if (solve_sudoku(board)) {
        std::cout << "\nSolved Sudoku puzzle:\n";
        print_board(board);
    } else {
        std::cout << "\nNo solution exists for the Sudoku puzzle.\n";
    }

    return 0;
}
