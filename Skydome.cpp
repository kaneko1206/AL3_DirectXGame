#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
}

void Skydome::Update() {}

void Skydome::Draw(ViewProjection& view) { model_->Draw(worldTransform_, view); }