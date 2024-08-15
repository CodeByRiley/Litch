#ifndef WABBLE_MENUSCENE_H
#define WABBLE_MENUSCENE_H

#include "Core/Scene.h"
#include <iostream>
#include "globals.h"
#include "glui/glui.h"
#if REMOVE_IMGUI == 0
#include "imgui.h"
#endif

class MenuScene : public Scene {
public:
    MenuScene(std::string,gl2d::Renderer2D&, glui::RendererUi&);
    virtual ~MenuScene();

    std::string name;

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
    Sound buttonClick;
    Music music;
};

#endif //WABBLE_MENUSCENE_H
