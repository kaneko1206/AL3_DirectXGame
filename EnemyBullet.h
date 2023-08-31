#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& pos, const Vector3& velocity);

	void Update();
	
	void Draw(ViewProjection& viewProjection);
	
	bool IsDead() const { return isDead_; }
	
	void OnCollision();
	
	Vector3 GetWorldPosition();
	
	float GetRadius() { return radius_; }

private:
	static const int32_t kLifetime = 60 * 5;
	int32_t deathTimer_ = kLifetime;
	bool isDead_ = false;
	WorldTransform worldTransform_;
	Vector3 velocity_;
	Model* model_;
	uint32_t textureHandle_;
	const float radius_ = 1.0;
};