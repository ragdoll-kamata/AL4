#pragma once
#include <KamataEngine.h>
#include "Sphere.h"
using namespace KamataEngine;
class EnemyBullet {
public:
	EnemyBullet();

	~EnemyBullet();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Camera* camera, uint32_t texture, Vector3 pos, Vector3 direction);

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

	bool IsDelete() { return isDelete; }

private: // メンバ変数
	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;
	Camera* camera_ = nullptr;
	static inline const float kMoveSpeed = 2.0f;
	Vector3 direction_;
	bool isDelete = false;
	static inline const int kDeleteTemer = 60;
	int deleteTemer = 60;

	static inline const float kRadius = 1.0f;
};
