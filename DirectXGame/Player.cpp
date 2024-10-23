#include "Player.h"
using namespace MathUtility;
Player::Player()
{
}

Player::~Player() {
	bullets.clear();
}

void Player::Initialize(Model* model, Camera* camera, uint32_t texture) {
	input_ = Input::GetInstance();
	model_ = model;
	camera_ = camera;
	texture_ = texture;
	worldTransform_.Initialize();
}

void Player::Update()
{
	Vector3 direction = {};

	if (input_->PushKey(DIK_RIGHT)) {
		direction.x += 1.0f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		direction.x -= 1.0f;
	}
	if (input_->PushKey(DIK_UP)) {
		direction.y += 1.0f;
	}
	if (input_->PushKey(DIK_DOWN)) {
		direction.y -= 1.0f;
	}
	direction = Normalize(direction);

	worldTransform_.translation_ += direction * kMoveSpeed;
	
	Rotate();

	if (input_->TriggerKey(DIK_SPACE)) {
		std::shared_ptr<PlayerBullet> a(new PlayerBullet);
		a->Initialize(model_, camera_, texture_, worldTransform_.translation_, TransformNormal({0.0f, 0.0f, 1.0f}, worldTransform_.matWorld_));
		bullets.push_back(a);
	}
	for (std::shared_ptr<PlayerBullet> bullet : bullets) {
		bullet->Update();
	}
	bullets.remove_if([](std::shared_ptr<PlayerBullet> bullet) { return bullet->IsDelete(); });
	worldTransform_.UpdateMatrix();
}

void Player::Rotate() {
	Vector3 rotate = {};
	if (input_->PushKey(DIK_A)) {
		rotate.y -= PI / 60.0f;
	}
	if (input_->PushKey(DIK_D)) {
		rotate.y += PI / 60.0f;
	}
	worldTransform_.rotation_ += rotate;
}

void Player::Draw()
{ 
	model_->Draw(worldTransform_, *camera_, texture_);
	for (std::shared_ptr<PlayerBullet> bullet : bullets) {
		bullet->Draw();
	}
}

void Player::OnCollision() {}

Vector3 Player::GetWorldPos() { 
	return Vector3(
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	);
}

Sphere Player::GetSphere() {
	return Sphere(
		GetWorldPos(),
		kRadius
	);
}