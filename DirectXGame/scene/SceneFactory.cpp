#include "SceneFactory.h"
#include "GameScene.h"
#include "TtleScene.h"
#include "ClearScene.h"
#include "OverScene.h"

Scene* SceneFactory::CreateScene(SceneName name) { 
	std::map<SceneName, Scene*> SceneMap{
	    {SceneName::TitleScene, new TtleScene()},
	    {SceneName::GameScene,  new GameScene()},
	    {SceneName::ClearScene, new ClearScene()},
	    {SceneName::OverScene,  new OverScene() },
	};

	return SceneMap[name];
}
