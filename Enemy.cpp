#include "Enemy.h"
#include "ImGuiManager.h"
#include "MathUtility.h"
#include "Player.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& pos) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	textureHandle_ = TextureManager::Load("sample.png");
	Approach();
}

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Approach() { pushTimer = kFireInterval; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

void Enemy::OnCollision() {}

void Enemy::Update() {

	pushTimer--;
	if (pushTimer <= 0) {
		Fire();
		pushTimer = kFireInterval;
	}
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	worldTransform_.UpdateMatrix();
	switch (phase_) {
	case Phase::Approach:
	default:
		worldTransform_.translation_.y -= kCharacterSpeed;
		if (worldTransform_.translation_.y < -20.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		worldTransform_.translation_.y += kCharacterSpeed;
		if (worldTransform_.translation_.y > 20.0f) {
			phase_ = Phase::Approach;
		}
		break;
	}
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire() {
	assert(player_);
	const float kBulletSpeed = 1.0f;
	differenceVector.x = player_->GetWorldPosition().x - GetWorldPosition().x;
	differenceVector.y = player_->GetWorldPosition().y - GetWorldPosition().y;
	differenceVector.z = player_->GetWorldPosition().z - GetWorldPosition().z;
	if (differenceVector.x != 0.0f || differenceVector.y != 0.0f || differenceVector.z != 0.0f) {
		float length = sqrtf(
		    differenceVector.x * differenceVector.x +
			differenceVector.y * differenceVector.y +
		    differenceVector.z * differenceVector.z);
		differenceVector.x /= length;
		differenceVector.y /= length;
		differenceVector.z /= length;
	}

	Vector3 velocity(
	    kBulletSpeed * differenceVector.x, kBulletSpeed * differenceVector.y,
	    kBulletSpeed * differenceVector.z);

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullet_ = newBullet;

	bullets_.push_back(newBullet);
}
