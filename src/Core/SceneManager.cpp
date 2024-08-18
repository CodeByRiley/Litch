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
    this->curScene = nullptr;
    this->Scenes.clear();
}
void SceneManager::Init()
{

}
void SceneManager::Unload()
{

}
void SceneManager::StartScene()
{

}
void SceneManager::UpdateScene()
{
    if(GetKeyPressed() == KEY_ENTER) {
        std::cout<<"Enter Pressed";
        if(this->GetScene("Game") == this->curScene.get()) {
            this->SetScene("Menu");
        } else {
            this->SetScene("Game");
        }
    }
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
void SceneManager::AddScene(std::string name, Scene* scene)
{
    if(!this->Scenes.empty()) {
        if(this->Scenes.find(name) != this->Scenes.end()) {
            std::cout << "Scene with name " << name << " already exists" << std::endl;
            return;
        }
    }
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
    if(this->curScene != nullptr) {
        this->curScene->changingScene = true;
        this->curScene->UnloadScene();
    }
    this->curScene = this->Scenes[name];
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