#pragma once
#include <KamataEngine.h>
#include "EnemyBullet.h"
#include "Sphere.h"
using namespace KamataEngine;


class Player;

class Enemy {
public:
	enum class Phase {
		Approach,
		Leave,
	};

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

	bool GetIsDeath() const { return isDeath; }
	bool GetIsEscape() const { return isEscape; }

private:
	
	void Approach();

	void Leave();

private: // メンバ変数

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;
	Camera* camera_ = nullptr;
	Vector3 approachMoveDirection;
	Vector3 leaveMoveDirection;

	static inline const float kMoveSpeed = 0.1f;
	static inline const float kRadius = 1.0f;
	std::list<std::shared_ptr<EnemyBullet>> bullets;
	Player* player_ = nullptr;
	int bulltShotTimer;
	static inline const int kBulltShotTimer = 30;

	Phase phase = Phase::Approach;

	bool isDeath = false;
	bool isEscape = false;
};
