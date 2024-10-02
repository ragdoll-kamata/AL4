#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class Player {
public:
	Player();

	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, Camera* camera);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�

	Input* input_ = nullptr;

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;

};

