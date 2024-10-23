#include "EnemyBullet.h"
using namespace MathUtility;
EnemyBullet::EnemyBullet() {}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, Camera* camera, uint32_t texture, Vector3 pos, Vector3 direction) {
	input_ = Input::GetInstance();
	model_ = model;
	camera_ = camera;
	texture_ = texture;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	direction_ = direction;
	deleteTemer = kDeleteTemer;
}

void EnemyBullet::Update() {
	deleteTemer--;
	worldTransform_.translation_ += direction_ * kMoveSpeed;
	if (deleteTemer < 0) {
		isDelete = true;
	}
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw() { model_->Draw(worldTransform_, *camera_); }

void EnemyBullet::OnCollision() { isDelete = true; }

Vector3 EnemyBullet::GetWorldPos() {
	return Vector3(
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	);
}

Sphere EnemyBullet::GetSphere() {
	return Sphere(
		GetWorldPos(),
		kRadius
	);
}