#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model, Camera* camera)
{
	model_ = model;
	camera_ = camera;
}

void Player::Update()
{
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *camera_);
}
