#ifndef WABBLE_GAME_H
#define WABBLE_GAME_H
#include <vector>
#include <algorithm>
#include <string.h>

#include "iostream"
#include "raylib.h"
#include "globals.h"
#include "Core/SceneManager.h"
#include "rlgl.h"
#include "Audio/RAudioExtensions.h"
#include "Core/Scenes/GameScene.h"
#if REMOVE_IMGUI == 0
    #include "imgui.h"
    #include "backends/imgui_impl_glfw.h"
    #include "backends/imgui_impl_opengl3.h"
    #include "imguiThemes.h"
#endif
#include "GLFW/glfw3.h"

enum GameState {
    MENU,
    GAME
};

class Game {
public:
    Game();
    void Create(const char*, int,int);
    void Destroy();

    static Game Instance;

    void Loop();
    void Update();
    void FixedUpdate(float);
    void Render();

    GameState State;
    GLFWwindow* window;

    bool Running;
    bool ShouldUpdate;

    Game(const Game &) = delete;

    static Game &Get() {
        return s_Instance;
    }

private:
    int WIDTH, HEIGHT;
    const char* TITLE;

    float fixedTime = 1/120.0F;
    float accumulator = 0;
    float frameTime = 0;

    static Game s_Instance;
    SceneManager* sceneManager;
};



#endif //WABBLE_GAME_H
