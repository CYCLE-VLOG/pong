// Pong Game for ESP32 with 64x64 matrix panel
// Uses the ESP32-HUB75-MatrixPanel-DMA library
// By ChatGPT

void setup() {
  // Initialization code goes here
}

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

// -------------------------------------
// -------   Matrix Config   ------
// -------------------------------------
const uint16_t PANEL_RES_X = 64;  // Number of pixels wide of each INDIVIDUAL panel module.
const uint16_t PANEL_RES_Y = 64;  // Number of pixels tall of each INDIVIDUAL panel module.
const uint16_t PANEL_CHAIN = 1; // Total number of panels chained one to another

// -------------------------------------
// -------   Game Config   ------
// -------------------------------------
const uint8_t PADDLE_HEIGHT = 16;
const uint8_t PADDLE_WIDTH = 2;
const uint8_t BALL_SIZE = 4;
const uint8_t BALL_SPEED = 2;

// -------------------------------------
// -------   Variables   ------
// -------------------------------------
int16_t leftPaddleY;
int16_t rightPaddleY;
int16_t ballX;
int16_t ballY;
int8_t ballSpeedX;
int8_t ballSpeedY;
int16_t leftScore;
int16_t rightScore;

// -------------------------------------
// -------   Matrix Objects   ------
// -------------------------------------
MatrixPanel_I2S_DMA *dma_display = nullptr;

// -------------------------------------
// -------   Helper Functions   ------
// -------------------------------------
void drawPaddle(int16_t x, int16_t y, uint16_t color) {
  for (int i = 0; i < PADDLE_HEIGHT; i++) {
    dma_display->drawPixel(x, y, color);
    // dma_display->setPixel(x, y + i, color);
  }
}

void erasePaddle(int16_t x, int16_t y) {
  drawPaddle(x, y, dma_display->color565(0, 0, 0));
}

void drawBall(int16_t x, int16_t y, uint16_t color) {
  for (int i = 0; i < BALL_SIZE; i++) {
    for (int j = 0; j < BALL_SIZE; j++) {
      dma_display->drawPixel(x, y, color);
    //  dma_display->setPixel(x + i, y + j, color);
    }
  }
}

void eraseBall(int16_t x, int16_t y) {
  drawBall(x, y, dma_display->color565(0, 0, 0));
}

void resetGame() {
  // Reset paddles to the center of the screen
  leftPaddleY = PANEL_RES_Y / 2 - PADDLE_HEIGHT / 2;
  rightPaddleY = PANEL_RES_Y / 2 - PADDLE_HEIGHT / 2;
  
  // Reset ball to the center of the screen
  ballX = PANEL_RES_X / 2 - BALL_SIZE / 2;
  ballY = PANEL_RES_Y / 2 - BALL_SIZE / 2;
  
  // Randomize ball speed and direction
  ballSpeedX = random(0, 2) == 0 ? -BALL_SPEED : BALL_SPEED;
  ballSpeedY = random(-BALL_SPEED, BALL_SPEED);
}

void startGame() {
  // Reset scores
  leftScore = 0;
  rightScore = 0;

  // Reset game
  resetGame();
}

void loop() {
  // Move ball
  eraseBall(ballX, ballY);
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Bounce ball off top/bottom walls
  if (ballY <= 0 || ballY >= PANEL_RES_Y - BALL_SIZE) 
    ballSpeedY = -ballSpeedY;
  }
  //
