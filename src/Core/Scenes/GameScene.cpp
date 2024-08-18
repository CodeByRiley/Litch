#include "GameScene.h"
#include "../Game.h"
GameScene::GameScene(std::string name, gl2d::Renderer2D &renderer, glui::RendererUi &ui) : Scene(renderer, ui) {
    this->name = name;
    std::cout<<"Creating "<<name<<std::endl;
    this->renderer = &renderer;
    this->ui = &ui;
}
GameScene::~GameScene() {

}

void GameScene::LoadScene() {
    std::cout<<"Loading Game"<<std::endl;
    this->toggleTextureUnTicked = gl2d::Texture(RESOURCES_PATH "assets/textures/ui/check_square_grey.png", false);
    this->toggleTextureTicked = gl2d::Texture(RESOURCES_PATH "assets/textures/ui/check_square_grey_checkmark.png", false);
    this->font.createFromFile(RESOURCES_PATH "assets/fonts/roboto_black.ttf");
    this->buttonClick = LoadSound(RESOURCES_PATH "audio/ui/click_002.ogg");
    this->toggleClick = LoadSound(RESOURCES_PATH "audio/ui/click_005.ogg");
    this->untoggleClick = LoadSound(RESOURCES_PATH "audio/ui/click_003.ogg");
    this->menuReturn = LoadSound(RESOURCES_PATH "audio/ui/click_002.ogg");
    this->music = LoadMusicStream(RESOURCES_PATH "audio/music/simple-bgm1.wav");
    this->changingScene = false;
    this->SceneLoaded = true;
}

void GameScene::UnloadScene() {
    std::cout<<"Unloading Game"<<std::endl;
    this->SceneLoaded = false;
    this->toggleTextureUnTicked.cleanup();
    this->toggleTextureTicked.cleanup();
    this->font.cleanup();
    UnloadMusicStream(music);
    UnloadSound(buttonClick);
    UnloadSound(toggleClick);
    UnloadSound(untoggleClick);
    UnloadSound(menuReturn);

}
void GameScene::Update() {
    if(music.ctxData != nullptr && !changingScene && SceneLoaded) {
        SetMusicVolume(music, (MusicVolume / 100));
        UpdateMusicStream(music);
    }

    if(vsync == true && usingVsync == false) {
        Game::Get().UpdateWindowState(FLAG_VSYNC_HINT, vsync);
        usingVsync = true;
    } else if (vsync == false && usingVsync == true) {
        Game::Get().UpdateWindowState(FLAG_VSYNC_HINT, vsync);
        usingVsync = false;
    }
}
float timer;
int rX,rY;
int rXV = 1;
int rYV = 1;
void GameScene::FixedUpdate(float dT) {
    timer += 1 * dT;
    if(timer >= 1.0F) {
        timer = 0;
    }

    rX += rXV;
    rY += rYV;
    if(rX >= GetScreenWidth() || rX < 0)
        rXV = -rXV;
    if(rY >= GetScreenHeight() || rY < 0)
        rYV = -rYV;
}
void DrawFPS(int posX, int posY, Color color1) {
    Color color = color1;
    int fps = GetFPS();

    if ((fps < 30) && (fps >= 15)) color = RED;  // Warning FPS
    else if (fps < 15) color = BLACK;             // Low FPS

    DrawText(TextFormat("%2i FPS", fps), posX, posY, 20, color);
}
void GameScene::Draw() {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawFPS(10, 10, ORANGE);
    DrawRectangle(rX, rY, 20, 20, BLACK);
    DrawText("Game Scene", 10, 40, 20, DARKGRAY);
    this->DrawUI();
    EndDrawing();
}



void GameScene::DrawUI() {

}