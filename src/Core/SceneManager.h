#ifndef WABBLE_SCENEMANAGER_H
#define WABBLE_SCENEMANAGER_H

#include <vector>
#include <algorithm>
#include "Core/Scene.h"
#include "Core/Scenes/MenuScene.h"
#include "Core/Scenes/GameScene.h"

class SceneManager {

public:
    SceneManager(gl2d::Renderer2D&, glui::RendererUi&);
    SceneManager();
    ~SceneManager();

public:
    void Init();
    void Unload();
    void StartScene();
    void UpdateScene();
    void FixedUpdateScene(float);
    void DrawScene();


public:
    gl2d::Renderer2D* renderer;
    glui::RendererUi* ui;

public:
    void AddScene(std::string, Scene*);
    void SetScene(std::string);
    Scene* GetScene(std::string);
    void RemoveScene(std::string);

    std::unordered_map<std::string, std::shared_ptr<Scene>> Scenes;
    std::shared_ptr<Scene> curScene;
};


#endif //WABBLE_SCENEMANAGER_H
