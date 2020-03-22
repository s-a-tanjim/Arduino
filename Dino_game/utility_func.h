
// Print welcome message
void welcomeMsg()
{
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);

  tft.setCursor(130, 80);
  tft.setTextSize(5);
  tft.println("Welcome!");

  tft.setCursor(100, 160);
  tft.setTextSize(3);
  tft.println("T-Rectus Femoris");

  tft.setCursor(200, 260);
  tft.setTextSize(2);
  tft.println("<Start>");
}

// Score print
void scorePrint(){
  tft.fillRect(399, 49, 80, 30, WHITE);
  tft.setTextColor(BLACK);
  tft.setCursor(400, 50);
  tft.setTextSize(2);
  tft.print(score);
}

void gameOverMsg(int highScore,int score)
{
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);

  tft.setCursor(115, 80);
  tft.setTextSize(5);
  tft.println("Game Over");

  tft.setCursor(110, 160);
  tft.setTextSize(3);
  tft.print("High Score: ");
  tft.print(highScore);

  tft.setCursor(155, 220);
  tft.setTextSize(2);
  tft.print("Your Score: ");
  tft.print(score);

  
  tft.setCursor(170, 260);
  tft.setTextSize(2);
  tft.println("<Start Again>");
}

void printLand()
{
  tft.fillRect(0, GROUND_BASE_POINT, tft.width(), 3, BLACK);
}

// print dino
void t_rex(int x, int y)
{
  //body
  tft.fillRect(x + 5, y + 6, 30, 30, BLACK);
  //head
  tft.fillRect(x + 31, y + 0, 15, 10, BLACK);
  //tail
  tft.fillRect(x + 0, y + 30, 5, 6, BLACK);
  //leg1
  tft.fillRect(x + 10, y + 36, 5, 10, BLACK);
  //leg2
  tft.fillRect(x + 25, y + 36, 5, 10, BLACK);
}

// clear dino
void clear_t_rex(int x, int y)
{
  //body
  tft.fillRect(x + 5, y + 6, 30, 30, WHITE);
  //head
  tft.fillRect(x + 31, y + 0, 15, 10, WHITE);
  //tail
  tft.fillRect(x + 0, y + 30, 5, 6, WHITE);
  //leg1
  tft.fillRect(x + 10, y + 36, 5, 10, WHITE);
  //leg2
  tft.fillRect(x + 25, y + 36, 5, 10, WHITE);
}
// print tree
void tree(int x, int y)
{
  //center
  tft.fillRect(x + 10, y + 0, 10, 40, BLACK);
  //left
  tft.fillRect(x + 0, y + 10, 6, 18, BLACK);
  //left L
  tft.fillRect(x + 0, y + 28, 10, 6, BLACK);
  //right
  tft.fillRect(x + 24, y + 5, 6, 15, BLACK);
  //leg2
  tft.fillRect(x + 20, y + 14, 10, 6, BLACK);
}

// clear tree
void clear_tree(int x, int y)
{
  //center
  tft.fillRect(x + 10, y + 0, 10, 40, WHITE);
  //left
  tft.fillRect(x + 0, y + 10, 6, 18, WHITE);
  //left L
  tft.fillRect(x + 0, y + 28, 10, 6, WHITE);
  //right
  tft.fillRect(x + 24, y + 5, 6, 15, WHITE);
  //leg2
  tft.fillRect(x + 20, y + 14, 10, 6, WHITE);
}

// Start buzzer
void start_buzzer()
{
  tone(BUZZER, 600);
}

void stop_buzzer()
{
  noTone(BUZZER);
}
