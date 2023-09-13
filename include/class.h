#include <deque>
#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "settings.h"

using namespace std;

class Food {
  public:
    Vector2 position;
    Texture2D texture;

    Food(){
      cout << "Made Food" << endl;
      Image image = LoadImage("bin/food.png");
      texture = LoadTextureFromImage(image);
      position = GenerateRandomPosition();
      UnloadImage(image);
    }

    ~Food() {
      UnloadTexture(texture);
    }

    void Draw() {
      DrawTexture(texture, position.x * CELL_SIZE, position.y * CELL_SIZE, WHITE);
    }

    Vector2 GenerateRandomPosition(){
      float x = GetRandomValue(0, CELL_SIZE - 10);
      float y = GetRandomValue(0, CELL_SIZE - 10);
      return Vector2{x,y};
    }
};

class Snake {
  public :
    deque<Vector2> body = {Vector2{6,9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void Draw() {
      for(unsigned int i = 0; i < body.size(); i++){
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{x * CELL_SIZE, y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
        DrawRectangleRounded(segment, 0.5, 1, fg);
      }
    }

    void Update() {
      body.pop_back();
      body.push_front(Vector2Add(body[0], direction));
    }
};

class Game {
  public:
    
    Food food;
    Snake snake;

    void Draw() {
      snake.Draw();
      food.Draw();
    }

    void Update() {
      snake.Update();
      checkCollisionWithFood();
    }
    
    void checkCollisionWithFood() {
      if (Vector2Equals(snake.body[0], food.position)){
        food.position = food.GenerateRandomPosition();
      }
    }
};
