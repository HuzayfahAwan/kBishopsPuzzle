#include <iostream>
#include <cmath>
using namespace std;

int factorial(int k) {
    if (k == 0 || k == 1) return k;
    return k * factorial(k - 1);
}

void initializeBoardToAllZeros(int* array, int n) {
    for (int i = 0; i < n; i++) {
        *(array + i) = 0;
    }
}

void backtrack(int array[], int &bishopTracker, int n) {
    bishopTracker--; // go back one column
    if (bishopTracker < 0) return; // if the column has been backtracked to a value that is less than 0, all solutions have been printed, so terminate method
    array[bishopTracker]++; // move on to the next row
    // if the index or current bishop's position moves beyond the last square of the chess board, then initiate backtracking
    if (array[bishopTracker] > ((n * n) - 1)) {
        array[bishopTracker] = 0; // sets the current bishop's position to 0
        backtrack(array, bishopTracker, n); // backtracks again
    }
}

bool tests(int array[], int index, int dimensions) {
    /* looping through each entry of the bishops array passed-in and performing the same-square test and the up/down diagonals test to see if the
       current configuration of the k bishops on the chess board is valid or not. */
    for (int i = 0; i < index; i++) {
        // array[i] % dimensions gives you the column number of the bishop and array[i] / dimensions gives you the row number of the bishop
        if (array[index] == array[i] || abs(array[index] % dimensions - array[i] % dimensions) == abs((array[index] / dimensions) - (array[i] / dimensions))) return false; // if one of these tests fail, a queen cannot be placed in the current row value of the current column of the board
    }
    return true; // if the statement above inside of the for-loop never evaluates to true after all iterations are complete, then it means that a queen can be placed in the current row value of the current column of the board
}

int kBishops(int k, int n) {
    int numOfSolutions = 0, index = 1; // index keeps track of what bishop the program is currently on
    /* bishops[i] tells you the position of the i'th bishop (positions correspond to numbers on the chess board; it's not like the n-Queens problem, 
       where the array tells you what row the queen for that specific column is at); bishops[i] can equal any value from the (chessBoardDimensions^2 - 1) 
       example -> q[1] = 5 means that the second bishop is on square number 5 of the chess board. */
    int* bishops = new int[k];
    // initialize the chess board to hold all zeros
    initializeBoardToAllZeros(bishops, k);
    // if the program backtracks beyond the first column, then that indicates that all solutions have been found and the function should terminate
    while (index != -1) { 
        /* if the program has moved beyond the last bishop or column, it means a solution has been found and should be printed. Backtracking should 
           initiate to find a different solution. */
        if (index > (k - 1)) {
            numOfSolutions++;
            backtrack(bishops, index, n);
        }
        // if the index or bishop's position moves beyond the last square of the chess board, then initiate backtracking
        else if (bishops[index] > ((n * n) - 1)) {
            bishops[index] = 0;
            backtrack(bishops, index, n);
        }
        // checks if the current figure of bishops is valid, and if so, the program moves on to the next bishop
        else if (tests(bishops, index, n)) index++;
        // otherwise it moves to the next square of the chess board for the current bishop and checks the conditions above all over again
        else bishops[index]++;
    }
    delete[] bishops;
    return numOfSolutions;
}

int main() {
    int chessBoardDimensions, numOfBishops;
    while (true) {
        cout << "Enter an integer for the rows and columns of the chess board (-1 to STOP): ";
        cin >> chessBoardDimensions;
        if (chessBoardDimensions == -1) break;
        cout << "Enter an integer representing the number of Bishops on the board (must be less than or equal to the integer for the rows and columns: ";
        cin >> numOfBishops;
        if (numOfBishops > chessBoardDimensions) {
            cout << "The number of Bishops cannot be greater than the dimensions of the chess board. It must be less than or equal. Please try again.\n\n";
            continue;
        }
        // dividing the number of returned solutions by the numOfBishops! to get rid of any double-counting done by the program, so only unique arrangements of the bishops on the chess board are found
        cout << "\nFor " << numOfBishops << " bishops on a " << chessBoardDimensions << " by " << chessBoardDimensions << " chess board, there are " << kBishops(numOfBishops, chessBoardDimensions) / factorial(numOfBishops) << " configurations.\n\n";
    }
    return 0;
}