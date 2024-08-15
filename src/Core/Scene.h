#ifndef WABBLE_SCENE_H
#define WABBLE_SCENE_H


#include <list>
#include <memory>
#include <iostream>
#include "Entity.h"
#include "raylib.h"
#include "glui/glui.h"
class Scene {
public:
    Scene(gl2d::Renderer2D&, glui::RendererUi&);
    virtual ~Scene();

    virtual void LoadScene();
    virtual void UnloadScene();

    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate(float);

    virtual void Draw();
    virtual void DrawUI();

    std::string name;


    gl2d::Renderer2D* renderer;
    glui::RendererUi* ui;

    std::list<std::shared_ptr<Entity>> Entities;

public:
    bool wantsToQuit = false;
};


#endif //WABBLE_SCENE_H
