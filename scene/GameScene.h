#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "AxisIndicator.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// サウンドデータハンドル
	uint32_t soundDataHanndle_ = 0;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle_2 = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	// スプライト
	Sprite* sprite_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロダクション
	ViewProjection viewProjection_;
	// ImGuiで値を入力する変数
	float inputFloat3[3]{0, 0, 0};
	// 音声再生ハンドル
	uint32_t voiceHnndle_ = 0;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
};
