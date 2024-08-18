#include "Game.h"


#define RAUDIOEXTENSIONS_IMPLEMENTATION
gl2d::Renderer2D renderer;
glui::RendererUi ui;
gl2d::Font font;
gl2d::Texture texture;
Sound buttonClick;
Music music;
float MusicVolume = 100;
bool vsync = false;
bool usingVsync = false;

Game::Game()
{
}
void Game::Create(const char* title, int w, int h)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(w,h,title);
    SetTargetFPS(0);
    InitAudioDevice();

    gl2d::init();
    renderer.create();

    this->window = glfwGetCurrentContext();
    this->sceneManager = new SceneManager(renderer,ui);
    this->sceneManager->Init();

    this->State = GameState::MENU;
    this->Running = !WindowShouldClose();
    this->ShouldUpdate = true;

    font.createFromFile(RESOURCES_PATH "assets/fonts/roboto_black.ttf");
    buttonClick = LoadSound(RESOURCES_PATH "audio/beans.wav");
    music = LoadMusicStream(RESOURCES_PATH "audio/scotty-scotty.wav");
    texture.loadFromFile(RESOURCES_PATH "assets/textures/ui/ui0.png", true);

    auto game = new GameScene("Game", renderer, ui);
    this->sceneManager->AddScene(game->name, std::make_unique<GameScene>(*game));
    delete game;
    this->sceneManager->SetScene("Game");
    this->sceneManager->StartScene();
}
void Game::Loop()
{
    if(this->ShouldUpdate) {
        this->Update();

    }
}
void Game::Update() {
    this->sceneManager->UpdateScene();
    accumulator += GetFrameTime();
    if(accumulator >= fixedTime) {
        accumulator -= fixedTime;
        frameTime = accumulator;
        this->FixedUpdate(frameTime);
        this->sceneManager->FixedUpdateScene(frameTime);
    }
    this->Render();
    if(this->sceneManager->curScene->wantsToQuit) {
        this->Destroy();
    }
}
void Game::FixedUpdate(float dT)
{
}

void Game::Render()
{
    this->sceneManager->DrawScene();
}

void Game::Destroy()
{
    renderer.cleanup();
    gl2d::clearnup();
    CloseAudioDevice();
    delete this->sceneManager;
    this->ShouldUpdate = false;
    this->Running = false;
}



