#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class Player {
public:
	Player();

	~Player();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Model* model, Camera* camera);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

private: // ƒƒ“ƒo•Ï”

	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;

};

