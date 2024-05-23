#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

const int screenWidth = 800;
const int screenHeight = 600;

//------------------ASSETS--------------
Texture tex;

int main() {

  InitWindow(screenWidth, screenHeight, "Raylib basic window");

#ifndef PLATFORM_ANDROID
  ChangeDirectory("assets");
#endif

  tex = LoadTexture("flat-dark.png");

#ifndef PLATFORM_ANDROID
  ChangeDirectory("..");
#endif
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  // SetTargetFPS(60);
  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif
  CloseWindow();
  return 0;
}

void UpdateDrawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText("It works!", 20, 100, 20, BLACK);
  const Rectangle rec = {0, 160, 160, 160};
  const Vector2 pos = {0, 0};
  DrawTextureRec(tex, rec, pos, WHITE);
  EndDrawing();
}
