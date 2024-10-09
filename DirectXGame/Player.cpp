#include "Player.h"
using namespace MathUtility;
Player::Player()
{
}

Player::~Player()
{
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

	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{ 
	model_->Draw(worldTransform_, *camera_, texture_);
}
