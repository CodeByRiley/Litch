#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::SceneManager(gl2d::Renderer2D& renderer, glui::RendererUi& ui)
{
    this->renderer = &renderer;
    this->ui       = &ui;
}

SceneManager::~SceneManager()
{
    for(auto& scene : this->Scenes) {
        scene.second->UnloadScene();
    }
    this->Scenes.clear();
    this->curScene = nullptr;
}
void SceneManager::Init()
{

}
void SceneManager::StartScene()
{

}
void SceneManager::UpdateScene()
{
    this->curScene->Update();
}
void SceneManager::FixedUpdateScene(float dT)
{
    if(this->curScene == nullptr) {
        std::cout << "No scene to update" << std::endl;
        return;
    }
    this->curScene->FixedUpdate(dT);
}
void SceneManager::DrawScene()
{
    if(this->curScene == nullptr) {
        std::cout << "No scene to draw" << std::endl;
        return;
    }
    this->curScene->Draw();
}
void SceneManager::AddScene(std::string name, std::unique_ptr<GameScene> scene)
{
    if(!this->Scenes.empty()) {
        if(this->Scenes.find(name) != this->Scenes.end()) {
            std::cout << "Scene with name " << name << " already exists" << std::endl;
            return;
        }
    }
    scene->LoadScene();
    this->Scenes.insert(std::make_pair(name, std::move(scene)));
}
void SceneManager::SetScene(std::string name) {
    if(this->Scenes.empty()) {
        std::cout << "No scenes to set" << std::endl;
        return;
    }
    if(this->Scenes.find(name) == this->Scenes.end()) {
        std::cout << "Scene with name " << name << " does not exist" << std::endl;
        return;
    }
    if(this->curScene != nullptr)
        this->curScene->UnloadScene();
    this->curScene = std::make_unique<GameScene>(*this->Scenes[name].get());
    this->curScene->LoadScene();
}
Scene* SceneManager::GetScene(std::string name)
{
    if(this->Scenes.empty()) {
        std::cout << "No scenes to get" << std::endl;
        return nullptr;
    }
    if(this->Scenes.find(name) == this->Scenes.end()) {
        std::cout << "Scene with name " << name << " does not exist" << std::endl;
        return nullptr;
    }
    return this->Scenes[name].get();
}
void SceneManager::RemoveScene(std::string name)
{
    if(this->Scenes.empty()) {
        std::cout << "No scenes to remove" << std::endl;
        return;
    }
    if(this->Scenes.find(name) == this->Scenes.end()) {
        std::cout << "Scene with name " << name << " does not exist" << std::endl;
        return;
    }
    this->Scenes.erase(name);
}