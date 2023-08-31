#include "Enemy.h"
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
	textureHandle_ = TextureManager::Load("Enemy.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

}

void Enemy::Update() {

	// デスフラグの立った弾を削除
	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		ApproachUpdate();
		if (worldTransform_.translation_.z < -70.0f) {
		    phase_ = Phase::Leave;
		}
		break;
	case Enemy::Phase::Leave:
		LeaveUpdate();
		break;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::ApproachUpdate() {
	worldTransform_.translation_.z -= 0.1f;
	// 発射タイマーをデクリメント
	fireTimer_--;
	// 指定時間に達した
	if (fireTimer_ <= 0) {
		// 弾を発射
			Fire();
		// 発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}
}

void Enemy::LeaveUpdate() {
		isDead_ = true;
}

void Enemy::Fire() {
	assert(player_);
	// 弾の速度
	const float kBulletSpeed = 1.5f;

	Vector3 playerPos;
	Vector3 enemyPos;
	Vector3 diff;
	playerPos = player_->Player::GetWorldPosition();
	enemyPos =GetWorldPosition();
	diff.x = playerPos.x - enemyPos.x;
	diff.y = playerPos.y - enemyPos.y;
	diff.z = playerPos.z - enemyPos.z;
	float length = sqrtf((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
	Vector3 dir(diff.x / length, diff.y / length, diff.z / length);
	Vector3 velocity(dir.x * kBulletSpeed, dir.y * kBulletSpeed, dir.z * kBulletSpeed);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_,GetWorldPosition(), velocity);

	gamescene_->AddEnemyBullet(newBullet);
}

void Enemy::OnCollision() { isDead_ = true; }

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}