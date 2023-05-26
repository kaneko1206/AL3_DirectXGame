#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

enum class Phase {
	Approach,
	Leave,
};

class Enemy {

public:

	void Initialize(Model* model, const Vector3&pos);
	void Update();
	void Draw(ViewProjection& viewProjection);
	Phase phase_ = Phase::Approach;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
