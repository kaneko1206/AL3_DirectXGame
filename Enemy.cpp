#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& pos) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	textureHandle_ = TextureManager::Load("sample.png");
}

void Enemy::Update() {

	// Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	worldTransform_.UpdateMatrix();
	switch (phase_) {
	case Phase::Approach:
	default:
		worldTransform_.translation_.z -= kCharacterSpeed;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		worldTransform_.translation_.z += kCharacterSpeed;
		break;
	}
	//	move.z -= kCharacterSpeed;

	// worldTransform_.translation_.x += move.x;
	// worldTransform_.translation_.y += move.y;
	// worldTransform_.translation_.z += move.z;
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
