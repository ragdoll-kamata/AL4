#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;
void SceneManager::Initialize() { 
	sceneFactory = new SceneFactory; }

void SceneManager::Update() {
	if (nextScene) {
		if (activeScene) {
			delete activeScene;
		}

		activeScene = nextScene;
		nextScene = nullptr;
		activeScene->Initialize();
	}
	activeScene->Update();
}

void SceneManager::Draw() {
	activeScene->Draw();
}

void SceneManager::SetNextScene(SceneName sceneName) {
	nextScene = sceneFactory->CreateScene(sceneName); }

SceneManager* SceneManager::GetInstance() {
	if (instance == nullptr) {
		instance = new SceneManager;
	}
	return instance;
}

void SceneManager::Finalize() { 
	delete instance;
	instance = nullptr;
}
