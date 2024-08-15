#ifndef WABBLE_GAMESCENE_H
#define WABBLE_GAMESCENE_H

#include "Core/Scene.h"
#include <iostream>
#include "globals.h"
#include "glui/glui.h"
#if REMOVE_IMGUI == 0
#include "imgui.h"
#endif

class GameScene : public Scene {
public:
    std::string name;
    GameScene(std::string,gl2d::Renderer2D&, glui::RendererUi&);
    virtual ~GameScene();

    void LoadScene() override;
    void UnloadScene() override;

    void Update() override;
    void FixedUpdate(float) override;
    void Draw() override;
    void DrawUI() override;

    float MusicVolume = 100;
    bool vsync = false;
    bool usingVsync = false;
private:
    bool SceneLoaded = false;
    gl2d::Font font;
    gl2d::Texture texture;
    gl2d::Texture toggleTextureUnTicked;
    gl2d::Texture toggleTextureTicked;
    Sound buttonClick;
    Sound menuReturn;
    Sound toggleClick;
    Sound untoggleClick;
    Music music;
};


#endif //WABBLE_GAMESCENE_H
