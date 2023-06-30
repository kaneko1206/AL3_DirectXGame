#pragma once

#include "Input.h"
#include "MathUtility.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include"Sprite.h"

class Player {

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& pos);
	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection& viewProjection);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);
	void DrawUI();

	void Attack();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	void SetParent(const WorldTransform* parent);
	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// 半径を取得
	float GetRadius() { return radius_; }
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;
	//半径
	const float radius_ = 1.0;
	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3Dreticle_;
	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
};