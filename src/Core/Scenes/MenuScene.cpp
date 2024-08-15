#include "MenuScene.h"

MenuScene::MenuScene(std::string name, gl2d::Renderer2D &renderer, glui::RendererUi &ui) : Scene(renderer, ui) {
    this->name = name;
    this->renderer = &renderer;
    this->ui = &ui;
}
MenuScene::~MenuScene() {

}

void MenuScene::LoadScene() {
    std::cout<<"Whaters";
    font.createFromFile(RESOURCES_PATH "assets/fonts/roboto_black.ttf");
    this->buttonClick = LoadSound(RESOURCES_PATH "audio/beans.wav");
    this->music = LoadMusicStream(RESOURCES_PATH "audio/scotty-scotty.wav");
    texture.loadFromFile(RESOURCES_PATH "assets/textures/ui/ui0.png", true);
    this->SceneLoaded = true;
}

void MenuScene::UnloadScene() {

}


int rX,rY;
int rXV = 1;
int rYV = 1;
void MenuScene::Update() {
    SetMusicVolume(music, (MusicVolume/100));
    UpdateMusicStream(music);

    if(vsync == true && usingVsync == false) {
        SetWindowState(FLAG_VSYNC_HINT);
        usingVsync = true;
    } else if (vsync == false && usingVsync == true) {
        ClearWindowState(FLAG_VSYNC_HINT);
        usingVsync = false;
    }

}
void MenuScene::FixedUpdate(float dT) {
    rX += rXV;
    rY += rYV;
    if(rX >= GetScreenWidth() || rX < 0)
        rXV = -rXV;
    if(rY >= GetScreenHeight() || rY < 0)
        rYV = -rYV;
}

void MenuScene::Draw() {
    DrawRectangle(rX,rY,20,20, BLACK);
}

void MenuScene::DrawUI() {
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
                if(this->ui->Button("Back", &buttonClick)) {
                    this->ui->returnBack();
                }
            this->ui->EndMenu();
            this->ui->BeginMenu("Video settings", &buttonClick,Colors_Transparent, texture);
                this->ui->Toggle("vSync", Colors_Gray, &vsync);
                    if(this->ui->Button("Back", &buttonClick)) {
                        this->ui->returnBack();
                    }
            this->ui->EndMenu();
            if(this->ui->Button("Back", &buttonClick)) {
                this->ui->returnBack();
            }
        this->ui->EndMenu();
        if(this->ui->Button("Quit", nullptr)) {
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