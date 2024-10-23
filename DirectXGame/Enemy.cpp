#include "Enemy.h"
#include "Player.h"

using namespace MathUtility;

Enemy::Enemy() {}

Enemy::~Enemy() { 
	bullets.clear(); 
}

void Enemy::Initialize(Model* model, Camera* camera, uint32_t texture) {
	model_ = model;
	camera_ = camera;
	texture_ = texture;
	worldTransform_.Initialize();
	direction = {0.0f, 0.0f, -1.0f};
	worldTransform_.translation_ = {10.0f, 0.0f, 100.0f};
}

void Enemy::Update() {
	direction = Normalize(direction);

	bulltShotTimer--;

	worldTransform_.translation_ += direction * kMoveSpeed;
	if (bulltShotTimer <= 0) {
		std::shared_ptr<EnemyBullet> a(new EnemyBullet);
		Vector3 targetDirection = player_->GetWorldPos() - GetWorldPos();
		a->Initialize(model_, camera_, texture_, worldTransform_.translation_, Normalize(targetDirection));
		bullets.push_back(a);
		bulltShotTimer = kBulltShotTimer;
	}
	
	
	for (std::shared_ptr<EnemyBullet> bullet : bullets) {
		bullet->Update();
	}
	bullets.remove_if([](std::shared_ptr<EnemyBullet> bullet) { return bullet->IsDelete(); });
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() {
	model_->Draw(worldTransform_, *camera_); 
	for (std::shared_ptr<EnemyBullet> bullet : bullets) {
		bullet->Draw();
	}
}

void Enemy::OnCollision() {}

Vector3 Enemy::GetWorldPos() {
	return Vector3(
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	); 
}

Sphere Enemy::GetSphere() {
	return Sphere(
		GetWorldPos(),
		kRadius
	); 
}
