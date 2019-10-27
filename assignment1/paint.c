// Assignment 1 19T3 COMP1511: CS Paint
// paint.c
//
// This program was written by Soorriamoorthy S Saruva (z5258068)
//
// Version 1.6.1 (2019-10-23): Add comments and minor refactor

#include <stdio.h>

// Note: you may find the square root function (sqrt) from the math
// library useful for drawing ellipses in Stage 3 and Stage 4.
#include <math.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

// IF YOU NEED MORE #defines ADD THEM HERE
#define DRAW_LINE_ARG_COUNT 4
#define FILL_SQUARE_ARG_COUNT 4
#define SHADE_ARG_COUNT 1
#define COPY_ARG_COUNT 6
#define ELLIPSE_ARG_COUNT 6
#define MAX_ARG_COUNT 6

// Provided helper functions:
// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

// Calculate the distance between two points.
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2);

// Command Functions
// Command 1
void drawLine(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int angle, int shade);

// Command 2
void fillSquare(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int angle, int shade);

// Command 4
void copyPaste(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int direction, int targetX, int targetY);

// Command 0
void drawEllipse(int canvas[N_ROWS][N_COLS], int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length, int fill, int shade);

// Helper Functions
int isInCanvas(int row, int col);

int isSquareInCanvas(int startRow, int startCol, int length, int direction);

int isInEllipse(int row, int col, int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length);

int isOnEllipseEdge(int row, int col, int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length);

int getRowDir(int direction);

int getColDir(int direction);

int normaliseDirection(int direction, int isLengthNegative);

int abs(int n);

int getArgCount(int command);

void executeCommand(int canvas[N_ROWS][N_COLS], int command, int args[MAX_ARG_COUNT], int shade);

int main(void) {
    int canvas[N_ROWS][N_COLS];
    int shade = BLACK;

    clearCanvas(canvas);

    int command;
    while (scanf("%d", &command) == 1) {
        int argCount = getArgCount(command);
        int args[MAX_ARG_COUNT] = {0};
        int i = 0;
        if (command == 0) {
            // Handle ellipse command separately as it needs
            // a float input
            // Get the first 4 arguments which are all integers
            while (i < 4) {
                scanf("%d", &args[i]);
                i++;
            }
            // Handle length differently as it can be a double
            double length;
            scanf("%lf", &length);
            // Get the last argument
            scanf("%d", &args[5]);
            drawEllipse(canvas, args[0], args[1], args[2], args[3], length, args[5], shade);
        } else if (command == 3) {
            int shadeChange = 0;
            // Get the amount the shade should change by
            scanf("%d", &shadeChange);
            int result = shade + shadeChange;
            // Only change the shade if it is between 0 (BLACK)
            // and 4 (WHITE) inclusive.
            if (result >= 0 && result <= 4) {
                shade = result;
            }
        } else {
            // Get all the arguments for the Draw Line, Fill
            // Square and Copy Paste commands.
            while (i < argCount) {
                scanf("%d", &args[i]);
                i++;
            }
            // Run the given command
            executeCommand(canvas, command, args, shade);
        }
    }

    displayCanvas(canvas);

    return 0;
}

// * ADD CODE FOR YOUR FUNCTIONS HERE

// Draws a line in the canvas.
void drawLine(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int direction, int shade) {
    // Assume the line is valid then correct later
    int isValid = 1;

    // Get the direction adjusted to be between 0 and 360 degress
    direction = normaliseDirection(direction, length < 0);

    // Get the relative directions according to the angle
    int rowDir = getRowDir(direction);
    int colDir = getColDir(direction);

    // If both relative directions are `0`, the line is invalid
    if (rowDir == 0 && colDir == 0) {
        isValid = 0;
    }

    // Calculate the enpoints of the line
    int endRow = startRow + (length - 1) * rowDir;
    int endCol = startCol + (length - 1) * colDir;

    // Check if the endpoints lie withinin the canvas
    isValid = isInCanvas(startRow, startCol) &&
              isInCanvas(endRow, endCol) &&
              isValid;

    // if the line is valid, draw it
    if (isValid) {
        int i = 0;
        while (i < length) {
            int currentRow = startRow + i * rowDir;
            int currentCol = startCol + i * colDir;
            canvas[currentRow][currentCol] = shade;
            i++;
        }
    }
}

// Draws a filled square in the canvas.
// Requires the above `drawLine` function.
void fillSquare(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int direction, int shade) {
    // Assume the rectangle is valid then correct later
    int isValidSquare = 1;
    // Get the direction adjusted to be between 0 and 360 degress
    direction = normaliseDirection(direction, length < 0);
    // Get the direction of the pixels to be drawn relative to the
    // start row and column
    int rowDir = getRowDir(direction);
    int colDir = getColDir(direction);

    // If the relative row or column directions are 0, then it is
    // a line or and invalid function call (i.e. not a valid
    // square)
    if (rowDir == 0 || colDir == 0) {
        isValidSquare = 0;

        // If the relative row and column directions are different,
        // then it is a line
        if (rowDir != colDir) {
            drawLine(canvas, startRow, startCol, length, direction, shade);
        }
    }

    // check if the square lies within the canvas
    isValidSquare = isSquareInCanvas(startRow, startCol, length, direction) &&
                    isValidSquare;
    // Get the absolue value of the length to account for if it
    // is negative
    length = abs(length);

    // if the square is valid, draw it
    if (isValidSquare) {
        int i = 0;
        int drawDirection;
        // if the relative row direction is `-1`, then the lines
        // should be drawn below it. Otherwise, the lines should
        // be drawn above it
        if (rowDir == -1) {
            drawDirection = 0;
        } else {
            drawDirection = 180;
        }
        // Draw the square by draw all the lines required
        while (i < length) {
            int currentCol = startCol + i * colDir;
            drawLine(canvas, startRow, currentCol, length, drawDirection, shade);
            i++;
        }
    }
}

// Copies a square of pixels from the canvas to another spot in the
// canvas.
void copyPaste(int canvas[N_ROWS][N_COLS], int startRow, int startCol, int length, int direction, int targetRow, int targetCol) {
    // Assume the source and target are valid then correct later
    int isValid = 1;
    // Get the direction adjusted to be between 0 and 360 degress
    direction = normaliseDirection(direction, length < 0);
    // Get the direction of the pixels to be drawn relative to the
    // start row and column
    int rowDir = getRowDir(direction);
    int colDir = getColDir(direction);

    // If the relative directions are 0, then the direction was
    // not valid
    if (rowDir == 0 && colDir == 0) {
        isValid = 0;
    }

    // Get the absolue value of the length to account for if it
    // is negative
    length = abs(length);

    // Check whether the source and target squares lie completely
    // within the canvas
    isValid = isSquareInCanvas(startRow, startCol, length, direction) &&
              isSquareInCanvas(targetRow, targetCol, length, direction) &&
              isValid;

    // Source and target square are valid, then copy the source
    // to the target
    if (isValid) {
        int i = 0;
        int j = 0;
        // Array to hold copy of original
        int source[N_ROWS][N_COLS] = {0};
        // Copy original from canvas into the source array
        while (i < length) {
            j = 0;
            while (j < length) {
                source[i][j] = canvas[startRow + i * rowDir][startCol + j * colDir];
                j++;
            }
            i++;
        }

        // Copy from source array to target position in the canvas
        i = 0;
        while (i < length) {
            j = 0;
            while (j < length) {
                // Set the target cell to the corresponding source cell
                canvas[targetRow + i * rowDir][targetCol + j * colDir] = source[i][j];
                j++;
            }
            i++;
        }
    }
}

// Draws an ellipse to the canvas with given foci, radius, shade and
// whether it should be filled.
void drawEllipse(int canvas[N_ROWS][N_COLS], int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length, int fill, int shade) {
    // Iterate over all pixels of the canvas to check if they
    // should be drawn as part of the ellipse.
    int i = 0;
    while (i < N_ROWS) {
        int j = 0;
        while (j < N_COLS) {
            if (fill == 0) {
                // If there should be no fill, change pixel colour
                // according to if it is on the edge of the ellipse.
                if (isOnEllipseEdge(i, j, focus1Row, focus1Col, focus2Row, focus2Col, length)) {
                    canvas[i][j] = shade;
                }
            } else {
                // If there should be fill, change pixel colour
                // according to if it is in the ellipse.
                if (isInEllipse(i, j, focus1Row, focus1Col, focus2Row, focus2Col, length)) {
                    canvas[i][j] = shade;
                }
            }
            j++;
        }
        i++;
    }
}

// Checks whether the specified row and column indices lie in
// the canvas. Requires N_ROWS and N_COLS defined above.
int isInCanvas(int row, int col) {
    // Return 1 if row is between 0 and N_ROWS and col is
    // between 0 and N_COLS
    return ((row >= 0) &&
            (row < N_ROWS) &&
            (col >= 0) &&
            (col < N_COLS));
}

// Checks whether the square with given start row and column, length
// and direction is wholly contained within the canvas.
int isSquareInCanvas(int startRow, int startCol, int length, int direction) {
    // Get the normalised direction
    direction = normaliseDirection(direction, length < 0);
    // Get the absolute value of the length to account for it is
    // negative
    length = abs(length);

    // Get the direction of the pixels to be drawn relative to the
    // start row and column
    int rowDir = getRowDir(direction);
    int colDir = getColDir(direction);

    // Calculate the coordinates of the opposite corner of the square
    int endRow = startRow + (length - 1) * rowDir;
    int endCol = startCol + (length - 1) * colDir;

    // Return whether both the start and end points are in the canvas
    return isInCanvas(startRow, startCol) && isInCanvas(endRow, endCol);
}

// Returns whether a point is within the ellipse with the given
// foci and length.
int isInEllipse(int i, int j, int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length) {
    return distance(focus1Row, focus1Col, i, j) + distance(focus2Row, focus2Col, i, j) <= 2 * length;
}

// Returns whether a point is on the edge of the ellipse with the
// given foci and length.
int isOnEllipseEdge(int row, int col, int focus1Row, int focus1Col, int focus2Row, int focus2Col, double length) {
    // The current pixel should be in the ellipse
    int thisPixelIsIn = isInEllipse(row, col, focus1Row, focus1Col, focus2Row, focus2Col, length);
    // At least one of the pixels below up, right, down or
    // left of the above pixel should not be in the ellipse
    int upIsNotIn = !isInEllipse(row - 1, col, focus1Row, focus1Col, focus2Row, focus2Col, length);
    int rightIsNotIn = !isInEllipse(row, col + 1, focus1Row, focus1Col, focus2Row, focus2Col, length);
    int downIsNotIn = !isInEllipse(row + 1, col, focus1Row, focus1Col, focus2Row, focus2Col, length);
    int leftIsNotIn = !isInEllipse(row, col - 1, focus1Row, focus1Col, focus2Row, focus2Col, length);
    // Return 1 if any of the pixels around the checked
    // pixel is not in the ellipse and the checked pixel
    // is in the ellipse.
    return (upIsNotIn || rightIsNotIn || downIsNotIn || leftIsNotIn) && thisPixelIsIn;
}

// Returns which direction (positive/right or negative/left)
// the row(s) of the result should be, relative to the start.
// Returns `0` if there should be no pixels drawn in either
// horizontal direction
int getRowDir(int direction) {
    if (direction == 0 || direction == 45 || direction == 315) {
        // If the direction requires upward drawing, return `-1`
        return -1;
    } else if (direction == 135 || direction == 180 || direction == 225) {
        // If the direction requires downward drawing, return `1`
        return 1;
    }
    // If the angle is none of the above, there is no vertical movement
    // when drawing and return `0`
    return 0;
}

// Returns which direction (positive/down or negative/up)
// the column(s) of the result should be relative to the start.
// Returns `0` if there should be no pixels drawn in either
// vertical direction
int getColDir(int direction) {
    if (direction == 225 || direction == 270 || direction == 315) {
        // If the direction requires leftward drawing, return `-1`
        return -1;
    } else if (direction == 45 || direction == 90 || direction == 135) {
        // If the direction requires rightward drawing, return `1`
        return 1;
    }
    // If the angle is none of the above, there is no horizontal movement
    // when drawing and return `0`
    return 0;
}

// Returns the direction adjusted for a negative length and an
// angle greater than 360 degrees.
int normaliseDirection(int direction, int isLengthNegative) {
    int result = direction;
    // If the length is negative add 180 to the original angle
    // to get the angle opposite on a compass
    if (isLengthNegative) {
        result += 180;
    }
    // Return the equivalent angle between 0 and 360
    return result % 360;
}

// Returns the absolute value of the input integer.
int abs(int n) {
    // If n is negative, return its negative
    if (n < 0) {
        return -n;
    }
    // If n is positive, return n
    return n;
}

// Returns the argument count required for the given command.
int getArgCount(int command) {
    if (command == 0) {
        // Ellipse command
        return ELLIPSE_ARG_COUNT;
    } else if (command == 1) {
        // Draw line command
        return DRAW_LINE_ARG_COUNT;
    } else if (command == 2) {
        // Fill Square command
        return FILL_SQUARE_ARG_COUNT;
    } else if (command == 3) {
        // Shade command
        return SHADE_ARG_COUNT;
    } else if (command == 4) {
        // Copy Paste command
        return COPY_ARG_COUNT;
    }
    return 0;
}

// Calls a function for the given command number with the
// given arguments.
void executeCommand(int canvas[N_ROWS][N_COLS], int command, int args[MAX_ARG_COUNT], int shade) {
    if (command == 1) {
        drawLine(canvas, args[0], args[1], args[2], args[3], shade);
    } else if (command == 2) {
        fillSquare(canvas, args[0], args[1], args[2], args[3], shade);
    } else if (command == 4) {
        copyPaste(canvas, args[0], args[1], args[2], args[3], args[4], args[5]);
    }
}

// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the displayCanvas function.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}

// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the clearCanvas function.
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

// Calculate the distance between two points (row1, col1) and (row2, col2).
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}
