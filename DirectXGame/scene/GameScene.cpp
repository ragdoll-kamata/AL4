#include "GameScene.h"
#include <cassert>
#include "Sphere.h"
#include "SceneManager.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//
	

	camera_ = std::make_unique<Camera>();
	camera_->Initialize();

	std::unique_ptr<Model> a(Model::Create());
	modelPlayer_ = std::move(a);

	tex = TextureManager::Load("mario.jpg");

	std::unique_ptr<Model> b(Model::CreateFromOBJ("skydome"));
	modelSkydome_ = std::move(b);

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get(), camera_.get());

	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), camera_.get(), tex);

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelPlayer_.get(), camera_.get(), tex);
	enemy_->SetPlayer(player_.get());
	SH = audio_->LoadWave("GameBGM.mp3");
	VH = audio_->PlayWave(SH, true, 0.5f);
}

void GameScene::Update() {
	skydome_->Update();
	player_->Update();
	enemy_->Update();
	CheckAllCollisions();
	if (enemy_->GetIsDeath()) {
		SceneManager::GetInstance()->SetNextScene(SceneName::ClearScene);
		audio_->StopWave(VH);
	}
	if (enemy_->GetIsEscape()) {
		SceneManager::GetInstance()->SetNextScene(SceneName::OverScene);
		audio_->StopWave(VH);
	}
	if (player_->GetIsDeath()) {
		SceneManager::GetInstance()->SetNextScene(SceneName::OverScene);
		audio_->StopWave(VH);
	}
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

	skydome_->Draw();
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
	for (std::shared_ptr<PlayerBullet> playerBullet : playerBullets) {
		for (std::shared_ptr<EnemyBullet> eneyBullet : eneyBullets) {
			if (CollisionDetection(playerBullet->GetSphere(), eneyBullet->GetSphere())) {
				playerBullet->OnCollision();
				eneyBullet->OnCollision();
			}
		}
	}

	// 敵と自機弾
	for (std::shared_ptr<PlayerBullet> playerBullet : playerBullets) {
		if (CollisionDetection(playerBullet->GetSphere(), enemy_->GetSphere())) {
			playerBullet->OnCollision();
			enemy_->OnCollision();
		}
	}

	// 自機と敵弾
	for (std::shared_ptr<EnemyBullet> eneyBullet : eneyBullets) {
		if (CollisionDetection(eneyBullet->GetSphere(), player_->GetSphere())) {
			eneyBullet->OnCollision();
			player_->OnCollision();
		}
	}

}
