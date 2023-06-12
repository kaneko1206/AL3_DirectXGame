#pragma once
#include "Model.h"
#include "WorldTransform.h"

class PlayerBullet {

public:
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	bool isDead() const { return isDead_; }

	float GetRadius() { return radius_; }

	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	bool isDead_ = false;
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	const float radius_ = 1.0;
};