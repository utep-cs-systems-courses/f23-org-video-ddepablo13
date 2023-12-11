#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include "libTimer.h"

// Game Constants
#define PADDLE_WIDTH 3
#define PADDLE_HEIGHT 15
#define BALL_SIZE 3
#define SCREEN_WIDTH screenWidth
#define SCREEN_HEIGHT screenHeight

// Game Variables
int paddle1Y, paddle2Y;
int ballPosX, ballPosY;
int ballVelocityX = 1, ballVelocityY = 1;

// Function Prototypes
void init_game();
void updatePaddlePositions();
void updateGame();
void drawPaddles();
void drawBall();

void main() {
    configureClocks();
    lcd_init();
    led_init();
    switch_init();
    init_game();

    enableWDTInterrupts(); // Enable watchdog timer
    or_sr(0x18);          // CPU off, GIE on

    while (1) {
        if (redrawScreen) {
            redrawScreen = 0;
            drawPaddles();
            drawBall();
            updateGame();
        }
    }
}

void init_game() {
    // Initialize game variables
    paddle1Y = paddle2Y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    ballPosX = SCREEN_WIDTH / 2;
    ballPosY = SCREEN_HEIGHT / 2;
    clearScreen(COLOR_BLACK);
}

void updateGame() {
    // Update ball position
    ballPosX += ballVelocityX;
    ballPosY += ballVelocityY;

    // Collision with top and bottom walls
    if (ballPosY <= 0 || ballPosY >= SCREEN_HEIGHT - BALL_SIZE) {
        ballVelocityY = -ballVelocityY; // Reverse Y direction
    }

    // Collision with paddles
    if (ballPosX <= PADDLE_WIDTH && ballPosY >= paddle1Y && ballPosY <= paddle1Y + PADDLE_HEIGHT) {
        ballVelocityX = -ballVelocityX; // Reverse X direction
    }
    if (ballPosX >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZE && ballPosY >= paddle2Y && ballPosY <= paddle2Y + PADDLE_HEIGHT) {
        ballVelocityX = -ballVelocityX; // Reverse X direction
    }

    // Scoring (if ball passes a paddle)
    if (ballPosX < 0 || ballPosX > SCREEN_WIDTH - BALL_SIZE) {
        // Reset ball position and serve from middle again
        ballPosX = SCREEN_WIDTH / 2;
        ballPosY = SCREEN_HEIGHT / 2;
        ballVelocityX = -ballVelocityX;
        // Implement scoring logic (if desired)
    }
}


void drawPaddles() {
    fillRectangle(0, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
    fillRectangle(SCREEN_WIDTH - PADDLE_WIDTH, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
}

void drawBall() {
    fillRectangle(ballPosX, ballPosY, BALL_SIZE, BALL_SIZE, COLOR_RED);
}

void updatePaddlePositions() {
    if (switch_state_down_1 && paddle1Y > 0) {
        paddle1Y -= 2; // Move paddle 1 up
    }
    if (switch_state_down_2 && paddle1Y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        paddle1Y += 2; // Move paddle 1 down
    }
    if (switch_state_down_3 && paddle2Y > 0) {
        paddle2Y -= 2; // Move paddle 2 up
    }
    if (switch_state_down_4 && paddle2Y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        paddle2Y += 2; // Move paddle 2 down
    }
}

