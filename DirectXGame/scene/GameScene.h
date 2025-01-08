#pragma once

#include <KamataEngine.h>
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include <memory>
#include "Scene.h"

using namespace KamataEngine;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public Scene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	std::unique_ptr<Player> player_ = nullptr;
	std::unique_ptr <Model> modelPlayer_ = nullptr;
	uint32_t tex = 0;

	std::unique_ptr <Enemy> enemy_ = nullptr;

	//
	std::unique_ptr <Skydome> skydome_ = nullptr;
	std::unique_ptr <Model> modelSkydome_ = nullptr;

	//カメラ
	std::unique_ptr <Camera> camera_ = nullptr;

	uint32_t SH = 0;
	uint32_t VH = 0;
};
