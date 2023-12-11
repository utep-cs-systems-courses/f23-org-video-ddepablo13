#include <msp430.h>
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "input.h"

// Define game dimensions and paddle size
#define GAME_WIDTH screenWidth
#define GAME_HEIGHT screenHeight
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 30
#define BALL_SIZE 5

// Game state variables
int ballX, ballY;  // Ball position
int ballVelocityX, ballVelocityY;  // Ball velocity
int paddle1Y, paddle2Y;  // Paddle positions

void initializeGame() {
    configureClocks();
    lcd_init();
    clearScreen(COLOR_BLACK);

    // Initialize ball position and velocity
    ballX = GAME_WIDTH / 2;
    ballY = GAME_HEIGHT / 2;
    ballVelocityX = 2;
    ballVelocityY = 2;

    // Initialize paddles
    paddle1Y = (GAME_HEIGHT - PADDLE_HEIGHT) / 2;
    paddle2Y = (GAME_HEIGHT - PADDLE_HEIGHT) / 2;
}

void updateGame() {
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Collision with walls
    if (ballY <= 0 || ballY + BALL_SIZE >= GAME_HEIGHT) {
        ballVelocityY *= -1;
    }

    // TODO: Add collision logic with paddles and game over conditions
}

void drawGame() {
    clearScreen(COLOR_BLACK);

    // Draw ball
    fillRectangle(ballX, ballY, BALL_SIZE, BALL_SIZE, COLOR_WHITE);

    // Draw paddles
    fillRectangle(5, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
    fillRectangle(GAME_WIDTH - 5 - PADDLE_WIDTH, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
}

volatile char redrawScreen = 1;

void wdt_c_handler() {
    if (redrawScreen) {
        updateGame();
        updatePaddles();
        drawGame();
        redrawScreen = 0;
    }
}

void main() {
    initializeGame();
    initializeInput();

    enableWDTInterrupts();
    or_sr(0x18);  // CPU off, GIE on

    while (1) {
        // Game logic updated in WDT interrupt
    }
}

// Watchdog Timer interrupt service routine
interrupt(WDT_VECTOR) WDT() {
    updateGame();
    updatePaddles();
    drawGame();
}
