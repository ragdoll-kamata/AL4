#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class Player {
public:
	Player();

	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera,uint32_t texture);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数

	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	uint32_t texture_;
};

