#pragma once
#include "Scene.h"
#include "KamataEngine.h"

using namespace KamataEngine;
class TtleScene : public Scene {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	DirectXCommon* dxCommon_ = nullptr;
	uint32_t tex;
	Sprite* sprite;
};
