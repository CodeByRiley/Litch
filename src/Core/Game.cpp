#include "Game.h"

Game Game::s_Instance;
gl2d::Renderer2D renderer;
glui::RendererUi ui;
gl2d::Font font;

SceneManager* sceneManager;

Game::Game() {
    s_Instance = *this;
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

    auto menu = new MenuScene("Menu", renderer, ui);
    auto game = new GameScene("Game", renderer, ui);
    std::cout<<menu->name<<std::endl;
    std::cout<<game->name<<std::endl;
    this->sceneManager->AddScene("Game", (Scene*)game);
    this->sceneManager->AddScene("Menu", (Scene*)menu);
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
        for(auto& scene : this->sceneManager->Scenes) {
            scene.second->UnloadScene();
        }
        this->sceneManager->Scenes.clear();
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

void Game::UpdateWindowState(unsigned int flag, bool state)
{
    if(state) {
        std::cout<<"Setting Window State: "<<flag<<": "<<state<<std::endl;

        SetWindowState(flag);
    } else {
        std::cout<<"Clearing Window State: "<<flag<<": "<<state<<std::endl;
        ClearWindowState(flag);
    }
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



