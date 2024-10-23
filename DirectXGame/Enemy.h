#pragma once
#include <KamataEngine.h>
#include "EnemyBullet.h"
#include "Sphere.h"
using namespace KamataEngine;


class Player;

class Enemy {
public:
	Enemy();

	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera, uint32_t texture);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void OnCollision();


	Vector3 GetWorldPos();
	Sphere GetSphere();

	std::list<std::shared_ptr<EnemyBullet>> GetBullets() { return bullets; }

	void SetPlayer(Player* player) { player_ = player; }

private: // メンバ変数

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;
	Camera* camera_ = nullptr;
	Vector3 direction;
	static inline const float kMoveSpeed = 0.1f;
	static inline const float kRadius = 1.0f;
	std::list<std::shared_ptr<EnemyBullet>> bullets;
	Player* player_ = nullptr;
	int bulltShotTimer;
	static inline const int kBulltShotTimer = 30;

};
