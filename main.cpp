#include <cmath>
#include <iostream>
#include <deque>

#include "include/raylib.h"
#include "include/raymath.h"
#include "include/settings.h"
#include "include/colors.h"
#include "include/class.h"

using namespace std;

double updateTime = 0;
bool eventTrigger(double interval) {
  double currentTime = GetTime();
  if (currentTime - updateTime >= interval) {
    updateTime = currentTime;
    return true;
  }
  return false;
}

int main (int argc, char *argv[])
{
  cout << "Starting the Game ..." <<endl;
  InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "Retro Snake");  
  SetTargetFPS(60);
  Game game;

  while (WindowShouldClose()==false)
  {
    BeginDrawing();
      if(eventTrigger(0.2)){ 
      game.Update();  
      }
      
      //snake direction
      if(IsKeyPressed(KEY_UP)) game.snake.direction = {0, -1};
      if(IsKeyPressed(KEY_DOWN)) game.snake.direction = {0, 1};
      if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != -1) game.snake.direction = {-1, 0};
      if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != 1) game.snake.direction = {1, 0};


      ClearBackground(bg);
      game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
