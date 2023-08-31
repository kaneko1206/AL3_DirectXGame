#include "BG.h"

BG::~BG() {
	delete spriteTitle_;
	delete spriteResult_;
}

void BG::Initialize() {
	// テクスチャ取得
	uint32_t texTitle = TextureManager::Load("title.png");
	uint32_t texResult = TextureManager::Load("result.png");
	// 生成
	spriteTitle_ = Sprite::Create(texTitle, {0, 0}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
	spriteResult_ = Sprite::Create(texResult, {0, 0}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
}

void BG::Draw(int kinds) {
	if (kinds == 0) {
		spriteTitle_->Draw();
	}
	if (kinds == 1) {
		spriteResult_->Draw();
	}
}