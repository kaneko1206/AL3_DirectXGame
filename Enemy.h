#pragma once

#include "EnemyBullet.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>

enum class Phase {
	Approach,
	Leave,
};
class Player;

class Enemy {

public:
	void Initialize(Model* model, const Vector3& pos);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Fire();
	~Enemy();
	static const int kFireInterval = 60;
	Phase phase_ = Phase::Approach;
	void Approach();
	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();
	Vector3 differenceVector;
	void OnCollision();
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; }
	const float radius_ = 1.0;
	float GetRadius() { return radius_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
	int32_t pushTimer = 60;
	Player* player_ = nullptr;
};
