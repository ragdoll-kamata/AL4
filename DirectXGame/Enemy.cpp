#include "Enemy.h"
#include "Player.h"
#include <map>
#include <functional>

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

	approachMoveDirection = {0.0f, 0.0f, -1.0f};
	approachMoveDirection = Normalize(approachMoveDirection);

	leaveMoveDirection = {0.0f, 1.0f, 0.0f};
	leaveMoveDirection = Normalize(leaveMoveDirection);

	worldTransform_.translation_ = {10.0f, 0.0f, 100.0f};
}

void Enemy::Update() {
	std::map<Phase, std::function<void()>> phaseMap{
	    {Phase::Approach, [this]() { Approach(); }},
	    {Phase::Leave,    [this]() { Leave(); }   },
	};

	phaseMap[phase]();

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

void Enemy::OnCollision() { isDeath = true; }

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

void Enemy::Approach() {

	bulltShotTimer--;

	worldTransform_.translation_ += approachMoveDirection * kMoveSpeed;
	if (bulltShotTimer <= 0) {
		std::shared_ptr<EnemyBullet> a(new EnemyBullet);
		Vector3 targetDirection = player_->GetWorldPos() - GetWorldPos();
		a->Initialize(model_, camera_, texture_, worldTransform_.translation_, Normalize(targetDirection));
		bullets.push_back(a);
		bulltShotTimer = kBulltShotTimer;
	}

	if (worldTransform_.translation_.z <= -1.0f) {
		phase = Phase::Leave;
	}
}

void Enemy::Leave() { 
	worldTransform_.translation_ += leaveMoveDirection * kMoveSpeed;
	if (worldTransform_.translation_.y >= 30.0f) {
		isEscape = true;
	}
}
