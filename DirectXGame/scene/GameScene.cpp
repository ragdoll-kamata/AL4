#include "GameScene.h"
#include <cassert>
#include "Sphere.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete enemy_;
	delete player_;
	delete modelPlayer_;
	delete camera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//


	camera_ = new Camera();
	camera_->Initialize();

	modelPlayer_ = Model::Create();

	tex = TextureManager::Load("mario.jpg");

	player_ = new Player();
	player_->Initialize(modelPlayer_, camera_, tex);

	enemy_ = new Enemy();
	enemy_->Initialize(modelPlayer_, camera_, tex);
	enemy_->SetPlayer(player_);

}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();
	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw();
	enemy_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {

	std::list<std::shared_ptr<PlayerBullet>> playerBullets = player_->GetBullets();
	std::list<std::shared_ptr<EnemyBullet>> eneyBullets = enemy_->GetBullets();

	// 自機弾と敵弾
	for (std::shared_ptr<PlayerBullet> a : playerBullets) {
		for (std::shared_ptr<EnemyBullet> b : eneyBullets) {
			if (CollisionDetection(a->GetSphere(), b->GetSphere())) {
				a->OnCollision();
				b->OnCollision();
			}
		}
	}

	// 敵と自機弾
	for (std::shared_ptr<PlayerBullet> a : playerBullets) {
		if (CollisionDetection(a->GetSphere(),enemy_->GetSphere())) {
			a->OnCollision();
			enemy_->OnCollision();
		}
	}

	// 自機と敵弾
	for (std::shared_ptr<EnemyBullet> a : eneyBullets) {
		if (CollisionDetection(a->GetSphere(), player_->GetSphere())) {
			a->OnCollision();
			player_->OnCollision();
		}
	}

}
