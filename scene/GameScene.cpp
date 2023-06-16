#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;
	delete skydome_;
	delete railcamera_;
}

void GameScene::Initialize() {

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	// 自キャラの生成
	player_ = new Player();
	Vector3 playerPosition{0, 0, 50};
	// 自キャラの初期化
	textureHandleP_ = TextureManager::Load("sample.png");
	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 天球の生成
	skydome_ = new Skydome();
	// レールカメラの生成
	railcamera_ = new RailCamera();
	railcamera_->Initialise({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	player_->SetParent(&railcamera_->GetWorldTransform());
	// 読み込み
	// モデル生成
	model_ = Model::Create();
	player_->Initialize(model_, textureHandleP_, playerPosition);
	enemy_->Initialize(model_, {5.0f, 0.0f, 0.0f});
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Initialize(modelSkydome_);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// 敵キャラの更新
	enemy_->Update();
	CheckAllCollisions();
	skydome_->Update();
	railcamera_->Update();
#ifdef _DEBUG

	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}
#endif // DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = railcamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railcamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection_);
	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵キャラの描画
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {

	// 衝突対象AとBの座標
	Vector3 posA, posB;
	// 距離格納
	Vector3 distAB;
	float distAdd;
	// 半径格納
	float radA = 0.0;
	float radB = 0.0;
	float radAdd;
	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();
	// 自キャラの半径
	radA = player_->GetRadius();
	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		radB = bullet->GetRadius();
		// 敵弾の座標
		posB = bullet->GetWorldPosition();
		// AとBの距離を求める
		distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		distAdd = distAB.x + distAB.y + distAB.z;
		radAdd = radA + radB;
		// 弾と弾の交差判定
		if (distAdd <= radAdd * radAdd) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion
#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラの半径
	radA = enemy_->GetRadius();
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾の当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		// 自弾の半径
		radB = bullet->GetRadius();
		// 自弾の座標
		posB = bullet->GetWorldPosition();
		// AとBの距離を求める
		distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		distAdd = distAB.x + distAB.y + distAB.z;
		radAdd = radA + radB;
		// 弾と弾の交差判定
		if (distAdd <= radAdd * radAdd) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* pBullet : playerBullets) {
		// 自弾の半径
		radA = pBullet->GetRadius();
		// 自弾の座標
		posA = pBullet->GetWorldPosition();

		// 自弾と敵弾全ての当たり判定
		for (EnemyBullet* eBullet : enemyBullets) {
			// 敵弾の半径
			radB = eBullet->GetRadius();
			// 敵弾の座標
			posB = eBullet->GetWorldPosition();
			// AとBの距離を求める
			distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
			distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
			distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
			distAdd = distAB.x + distAB.y + distAB.z;
			radAdd = radA + radB;
			// 弾と弾の交差判定
			if (distAdd <= radAdd * radAdd) {
				// 敵弾の衝突時コールバックを呼び出す
				eBullet->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				pBullet->OnCollision();
			}
		}
	}
}
