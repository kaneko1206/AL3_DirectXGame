#include "Score.h"
#include <stdio.h>

Score::~Score() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			delete sprite2DNum_[i][j];
			delete sprite2DNumResult_[i][j];
		}
	}
}

void Score::Initialize() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] = nullptr;
			sprite2DNumResult_[i][j] = nullptr;
		}
	};
	uint32_t textureNum[10] = {
	    TextureManager::Load("num/0.png"), TextureManager::Load("num/1.png"),
	    TextureManager::Load("num/2.png"), TextureManager::Load("num/3.png"),
	    TextureManager::Load("num/4.png"), TextureManager::Load("num/5.png"),
	    TextureManager::Load("num/6.png"), TextureManager::Load("num/7.png"),
	    TextureManager::Load("num/8.png"), TextureManager::Load("num/9.png"),
	};
	uint32_t textureNum2[10] = {
	    TextureManager::Load("num2/0.png"), TextureManager::Load("num2/1.png"),
	    TextureManager::Load("num2/2.png"), TextureManager::Load("num2/3.png"),
	    TextureManager::Load("num2/4.png"), TextureManager::Load("num2/5.png"),
	    TextureManager::Load("num2/6.png"), TextureManager::Load("num2/7.png"),
	    TextureManager::Load("num2/8.png"), TextureManager::Load("num2/9.png"),
	};
	float posX = 170;
	float posXResult = 1000;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] =
			    Sprite::Create(textureNum[j], {posX, 25}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
			sprite2DNumResult_[i][j] =
			    Sprite::Create(textureNum2[j], {posXResult, 200}, {1, 1, 1, 1}, {(0.0f), (0.0f)});
		}
		posX -= 50;
		posXResult -= 300;
	}
}

void Score::DrawScoreUI(int score) {
	int eachNumber[4];
	int digit = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			digit = 1000;
		}
		eachNumber[i] = score / digit;
		score -= eachNumber[i] * digit;
		digit /= 10;
	}
	sprite2DNum_[0][eachNumber[3]]->Draw();
	sprite2DNum_[1][eachNumber[2]]->Draw();
	sprite2DNum_[2][eachNumber[1]]->Draw();
	sprite2DNum_[3][eachNumber[0]]->Draw();
}
void Score::DrawScoreUIResult(int score) {
	int eachNumber[4];
	int digit = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			digit = 1000;
		}
		eachNumber[i] = score / digit;
		score -= eachNumber[i] * digit;
		digit /= 10;
	}
	sprite2DNumResult_[0][eachNumber[3]]->Draw();
	sprite2DNumResult_[1][eachNumber[2]]->Draw();
	sprite2DNumResult_[2][eachNumber[1]]->Draw();
	sprite2DNumResult_[3][eachNumber[0]]->Draw();
}