#pragma once
#include <ImGuiManager.h>
#include <Model.h>
#include <Sprite.h>

class BG {
public:
	void Initialize();

	~BG();

	void Draw(int kinds);

private:
	Sprite* spriteTitle_ = nullptr;
	Sprite* spriteResult_ = nullptr;
};