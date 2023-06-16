#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:
	void Initialise(Vector3 pos, Vector3 rot);

	void Update();

	ViewProjection& GetViewProjection() { return viewProjection_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	
};
