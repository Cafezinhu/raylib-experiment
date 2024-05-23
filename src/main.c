#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

const int screenWidth = 800;
const int screenHeight = 600;

void UpdateDrawFrame();

int main() {

  InitWindow(screenWidth, screenHeight, "Raylib basic window");
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
  EndDrawing();
}
