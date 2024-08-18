#include "MenuScene.h"

MenuScene::MenuScene(std::string name, gl2d::Renderer2D &renderer, glui::RendererUi &ui) : Scene(renderer, ui) {
    this->name = name;
    std::cout<<"Creating "<<name<<std::endl;
    this->renderer = &renderer;
    this->ui = &ui;
}
MenuScene::~MenuScene() {

}

void MenuScene::LoadScene() {
    std::cout<<"Loading Menu"<<std::endl;
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

void MenuScene::UnloadScene() {
    std::cout<<"Unloading Menu"<<std::endl;
    this->SceneLoaded = false;
    this->font.cleanup();
    UnloadMusicStream(music);
    UnloadSound(buttonClick);
}



void MenuScene::Update() {
    if(music.ctxData != nullptr && !changingScene && SceneLoaded) {
        SetMusicVolume(music, (MusicVolume/100));
        UpdateMusicStream(music);
    }
    if(vsync == true && usingVsync == false) {
        SetWindowState(FLAG_VSYNC_HINT);
        usingVsync = true;
    } else if (vsync == false && usingVsync == true) {
        ClearWindowState(FLAG_VSYNC_HINT);
        usingVsync = false;
    }

}
void MenuScene::FixedUpdate(float dT) {

}

void MenuScene::Draw() {
    BeginDrawing();
    ClearBackground(GRAY);
    this->DrawUI();
    DrawText("Menu Scene", 10, 10, 20, WHITE);
    EndDrawing();
}

void MenuScene::DrawUI() {
    this->renderer->updateWindowMetrics(GetRenderWidth(),GetRenderHeight());
    if(this->SceneLoaded) {
#pragma region GLUI
        this->ui->Begin(100);

        this->ui->SetAlignModeFixedSizeWidgets({0, 100});
        if(this->ui->Button("Play", &buttonClick)) {
            if(music.ctxData != nullptr)
                PlayMusicStream(music);
        }
        if(this->ui->Button("Pause", &buttonClick)) {
            if(music.ctxData != nullptr)
                PauseMusicStream(music);
        }
        if(this->ui->Button("Stop", &buttonClick)) {
            if(music.ctxData != nullptr)
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