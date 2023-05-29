#include "Enemy.h"
#include "ImGuiManager.h"
#include "MathUtility.h"
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
		worldTransform_.translation_.z -= kCharacterSpeed;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		worldTransform_.translation_.z += kCharacterSpeed;
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
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullet_ = newBullet;

	bullets_.push_back(newBullet);
}
