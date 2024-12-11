#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class Skydome {
public:


	void Initialize(Model* model, Camera* viewProjection);


	void Update();

	
	void Draw();


private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	Camera* viewProjection_ = nullptr;

};
