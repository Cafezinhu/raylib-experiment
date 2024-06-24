#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <string.h>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

const int screenWidth = 800;
const int screenHeight = 600;

//------------------ASSETS--------------
// Texture tex;
Model boat;
Model boat2;
Camera3D camera;
Model cube;
Shader shader;

int main() {

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Raylib basic window");

#ifndef PLATFORM_ANDROID
  ChangeDirectory("assets");
#endif

  boat = LoadModel("boat-sail-a.glb");
  shader = LoadShader(TextFormat("shaders/glsl%i/luz.vert", GLSL_VERSION),
                      TextFormat("shaders/glsl%i/luz.frag", GLSL_VERSION));
  int objectColorLoc = GetShaderLocation(shader, "objectColor");
  int lightColorLoc = GetShaderLocation(shader, "lightColor");
  int lightPosLoc = GetShaderLocation(shader, "lightPos");

  SetShaderValue(shader, objectColorLoc, (float[3]){1.0f, 0, 0},
                 SHADER_UNIFORM_VEC3);
  SetShaderValue(shader, lightColorLoc, (float[3]){1.0f, 1.0f, 1.0f},
                 SHADER_UNIFORM_VEC3);
  SetShaderValue(shader, lightPosLoc, (float[3]){0, 0, 3}, SHADER_UNIFORM_VEC3);

  boat.materials[0].shader = shader;
  boat.materials[1].shader = shader;
  cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
  cube.materials[0].shader = shader;
  printf("%d", boat.materialCount);
  boat2 = LoadModel("boat2.glb");
  boat2.materials[1].shader = shader;
  // tex = LoadTexture("flat-dark.png");

  camera = (Camera){0};
  camera.position = (Vector3){2.0f, 4.0f, 6.0f}; // Camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
  // DisableCursor();
  SetExitKey(0);

  SetTargetFPS(60);
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
  if (IsCursorHidden())
    UpdateCamera(&camera, CAMERA_ORBITAL);
  // float cameraPos[3] = {camera.position.x, camera.position.y,
  //                       camera.position.z};
  // SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
  //                SHADER_UNIFORM_VEC3);
  // UpdateLightValues(shader, light);
  // BeginDrawing();
  // ClearBackground(RAYWHITE);
  // // DrawText("It works!", 20, 100, 20, BLACK);
  // const Rectangle rec = {0, 160, 160, 160};
  // const Vector2 pos = {0, 0};
  // // DrawTextureRec(tex, rec, pos, WHITE);
  // BeginMode3D(camera);
  // BeginShaderMode(shader);
  // const Vector3 posboat = {0, 0, 0};
  // DrawModel(boat, posboat, 1, WHITE);
  // DrawPlane((Vector3){0, 0, 0}, (Vector2){10.0f, 10.0f}, WHITE);
  // EndShaderMode();
  // DrawGrid(10, 1);
  // DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
  // EndMode3D();
  // EndDrawing();
  //
  // UpdateCamera(&camera, CAMERA_ORBITAL);
  //
  // RLG_SetViewPositionV(camera.position);

  //----------------------------------------------------------------------------------
  if (IsKeyPressed(KEY_ESCAPE)) {
    EnableCursor();
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    DisableCursor();
  }

  int lightPosLoc = GetShaderLocation(shader, "lightPos");
  SetShaderValue(shader, lightPosLoc,
                 (float[3]){sin(GetTime()) * 3, 0, cos(GetTime()) * 3},
                 SHADER_UNIFORM_VEC3);
  int viewPosLoc = GetShaderLocation(shader, "viewPos");
  SetShaderValue(
      shader, viewPosLoc,
      (float[3]){camera.position.x, camera.position.y, camera.position.z},
      SHADER_UNIFORM_VEC3);

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();
  ClearBackground(RAYWHITE);

  BeginMode3D(camera);

  DrawGrid(10, 1.0f);
  DrawModel(boat, (Vector3){1, 0, 0}, 1, WHITE);
  DrawModel(boat2, (Vector3){-1, 0, 0}, 1, WHITE);
  DrawModel(cube, (Vector3){0, 0, 2}, 1, WHITE);

  EndMode3D();
  DrawFPS(10, 10);

  EndDrawing();
}
