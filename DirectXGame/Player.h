#pragma once
#include <KamataEngine.h>
#include "Sphere.h"
#include "PlayerBullet.h"
using namespace KamataEngine;
class Player {
public:
	Player();

	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera, uint32_t texture);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void Rotate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void OnCollision();

	Vector3 GetWorldPos();
	Sphere GetSphere();

	std::list<std::shared_ptr<PlayerBullet>> GetBullets() { return bullets; }

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	bool GetIsDeath() const { return isDeath; }

private: // メンバ変数
	Audio* audio_ = nullptr;

	uint32_t SH = 0;

	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;
	Camera* camera_ = nullptr;
	static inline const float kMoveSpeed = 0.5f;
	std::list<std::shared_ptr<PlayerBullet>> bullets;

	static inline const float kRadius = 1.0f;

	bool isDeath = false;
};

