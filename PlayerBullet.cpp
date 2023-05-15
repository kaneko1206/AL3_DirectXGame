#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	assert(model);
	model_ = model;

	textureHandle_ = TextureManager::Load("/cube/cube.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = position.x;
	worldTransform_.translation_.y = position.y;
	worldTransform_.translation_.z = position.z;
}

void PlayerBullet::Update() {

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列転送
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}