#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model, Camera* camera, uint32_t texture)
{
	model_ = model;
	camera_ = camera;
	texture_ = texture;
	worldTransform_.Initialize();
}

void Player::Update()
{
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *camera_, texture_);
}
