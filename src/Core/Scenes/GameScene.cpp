#include "GameScene.h"

GameScene::GameScene(std::string name, gl2d::Renderer2D &renderer, glui::RendererUi &ui) : Scene(renderer, ui) {
    this->name = name;
    this->renderer = &renderer;
    this->ui = &ui;
}
GameScene::~GameScene() {

}

void GameScene::LoadScene() {
    std::cout<<"Gamers";
    font.createFromFile(RESOURCES_PATH "assets/fonts/roboto_black.ttf");
    this->buttonClick = LoadSound(RESOURCES_PATH "audio/ui/click_002.ogg");
    this->toggleClick = LoadSound(RESOURCES_PATH "audio/ui/click_005.ogg");
    this->untoggleClick = LoadSound(RESOURCES_PATH "audio/ui/click_003.ogg");
    this->menuReturn = LoadSound(RESOURCES_PATH "audio/ui/click_002.ogg");
    this->music = LoadMusicStream(RESOURCES_PATH "audio/music/simple-bgm1.wav");
    this->toggleTextureUnTicked = gl2d::Texture(RESOURCES_PATH "assets/textures/ui/check_square_grey.png", false);
    this->toggleTextureTicked = gl2d::Texture(RESOURCES_PATH "assets/textures/ui/check_square_grey_checkmark.png", false);
    this->SceneLoaded = true;
}

void GameScene::UnloadScene() {

}


void GameScene::Update() {
    SetMusicVolume(music, (MusicVolume/100));
    UpdateMusicStream(music);



}
float timer;
void GameScene::FixedUpdate(float dT) {
    timer += 1 * dT;
    if(timer >= 1.0F) {
        std::cout<<"FPS: "<<1.0F/dT<<std::endl;
        std::cout<<"FrameTime: "<<dT<<std::endl;
        timer = 0;
    }
}

void GameScene::Draw() {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawFPS(10, 10);
    DrawText("Game Scene", 10, 10, 20, DARKGRAY);
    this->DrawUI();
    EndDrawing();
}

void GameScene::DrawUI() {
    if(this->SceneLoaded) {
#pragma region GLUI
        this->renderer->updateWindowMetrics(GetRenderWidth(),GetRenderHeight());
        this->ui->Begin(100);

        this->ui->SetAlignModeFixedSizeWidgets({0, 100});
        if(this->ui->Button("Play", &buttonClick)) {
            PlayMusicStream(music);
        }
        if(this->ui->Button("Pause", &buttonClick)) {
            PauseMusicStream(music);
        }
        if(this->ui->Button("Stop", &buttonClick)) {
            StopMusicStream(music);
        }


        this->ui->BeginMenu("Settings", &buttonClick,Colors_Transparent, texture);
        this->ui->BeginMenu("Sound settings", &buttonClick,Colors_Transparent, texture);
        this->ui->sliderFloatNoDecimal("Music volume", &MusicVolume, 0, 100, Colors_White);
        if(this->ui->Button("Back", &menuReturn)) {
            this->ui->returnBack();
        }
        this->ui->EndMenu();
        this->ui->BeginMenu("Video settings", &buttonClick,Colors_Transparent, texture);
        this->ui->DualToggle("vSync", &toggleClick, &untoggleClick,Colors_Gray, &vsync, toggleTextureTicked, toggleTextureUnTicked, 25.f);
        this->ui->DualToggle("Bro", &toggleClick, &untoggleClick,Colors_Gray, &vsync, toggleTextureTicked, toggleTextureUnTicked, 55.f);
        this->ui->DualToggle("Bro##2", &toggleClick, &untoggleClick,Colors_Gray, &vsync, toggleTextureTicked, toggleTextureUnTicked, 55.f);
        if(this->ui->Button("Back", &menuReturn)) {
            this->ui->returnBack();
        }
        this->ui->EndMenu();
        if(this->ui->Button("Back", &menuReturn)) {
            this->ui->returnBack();
        }
        this->ui->EndMenu();
        if(ui->Button("Quit", nullptr)) {
            this->wantsToQuit = true;
        }
        this->ui->End();

        this->ui->renderFrame(*renderer, font, glm::vec2(GetMousePosition().x, GetMousePosition().y),
                       IsMouseButtonPressed(MOUSE_BUTTON_LEFT), IsMouseButtonDown(MOUSE_BUTTON_LEFT), IsMouseButtonReleased(MOUSE_BUTTON_LEFT),
                       "", GetFrameTime(),IsKeyReleased(KEY_BACKSPACE));
        this->renderer->flush();

#pragma endregion
    }

}