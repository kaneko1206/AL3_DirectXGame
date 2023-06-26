﻿#include "Enemy.h"
#include "EnemyBullet.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MathUtility.h"
#include "Player.h"
#include <cassert>
#include <cmath>

Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	textureHundle_ = TextureManager::Load("sample.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	ApproachInitialize();
}

void Enemy::Update() {
	// デスフラグの立った弾を削除

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		ApproachUpdate();
		/*if (worldTransform_.translation_.z < 0.0f) {
		    phase_ = Phase::Leave;
		}*/
		break;
	case Enemy::Phase::Leave:
		LeaveUpdate();
		break;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}

void Enemy::ApproachUpdate() {
	worldTransform_.translation_.z -= 0.0f;
	// 発射タイマーをデクリメント
	fireTimer--;
	// 指定時間に達した
	if (fireTimer <= 0) {
		// 弾を発射
		Fire();
		// 発射タイマーを初期化
		fireTimer = kFireInterval;
	}
}

void Enemy::LeaveUpdate() {
	worldTransform_.translation_.x -= 0.2f;
	worldTransform_.translation_.y += 0.2f;

	if (deathTimer_-- < 0) {
		isDead_ = true;
	}
}

void Enemy::Fire() {
	assert(player_);
	// 弾の速度
	const float kBulletSpeed = 1.0f;

	Vector3 playerPos;
	Vector3 diff;
	playerPos = player_->Player::GetWorldPosition();
	diff.x = playerPos.x - worldTransform_.translation_.x;
	diff.y = playerPos.y - worldTransform_.translation_.y;
	diff.z = playerPos.z - worldTransform_.translation_.z;
	float length = sqrtf((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
	Vector3 dir(diff.x / length, diff.y / length, diff.z / length);
	Vector3 velocity(dir.x * kBulletSpeed, dir.y * kBulletSpeed, dir.z * kBulletSpeed);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	// bullets_.push_back(newBullet);

	gamescene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize() {
	// 発射タイマーを初期化
	fireTimer = kFireInterval;
}

void Enemy::OnCollision() { isDead_ = true; }

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}