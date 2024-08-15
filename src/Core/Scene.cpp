#include "Scene.h"
Scene::Scene(gl2d::Renderer2D& renderer, glui::RendererUi& ui) {
    this->renderer = &renderer;
    this->ui       = &ui;
    std::cout<<"New Scene "<<name;
}
Scene::~Scene() {
    UnloadScene();
}
void Scene::Start() {
}
void Scene::Update() {
}
void Scene::FixedUpdate(float) {
}
void Scene::LoadScene() {
}
void Scene::UnloadScene() {
}
void Scene::Draw() {
}
void Scene::DrawUI() {
}