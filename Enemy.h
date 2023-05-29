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

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
	int32_t pushTimer = 60;
};
