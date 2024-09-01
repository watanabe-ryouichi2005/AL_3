
// #include "MapChipField.h"
//#include "WorldTransform.h"
#include <cassert>
#include <map>
#include<cstdint>
#include "MyMath.h"
#include "GameScene.h"
#include "TextureManager.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
	for (Enemy* enemy_ : enemies_) {
		delete enemy_;
	}
delete modelParticle_,delete player_, delete model_, delete modelBlock_, delete debugCamera_,
	    delete mapChipField_,delete modelSkydome_,delete cameraController_,delete goals_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
		for (WorldTransform* worldTrandformBlock : worldTransformBlockLine) {
			delete worldTrandformBlock;
		}
}
//	worldTransformBlocks_.clear();

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelEnemy_ = Model::CreateFromOBJ("enemy");
	modelBlock_ = Model::CreateFromOBJ("block");
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);
	modelParticle_=Model::CreateFromOBJ("deathParticle",true);
	modelGoals_ = Model::CreateFromOBJ("ClearBox",true);

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	Vector3 goalposition_ = mapChipField_->GetMapChipPositionByIndex(2,8);
	cameraController_ = new CameraController();
	mapChipField_ = new MapChipField;
	player_ = new Player();
	//enemy_ = new Enemy();
	goals_ = new Goal();
	goals_->Init(modelGoals_,&viewProjection_,goalposition_);
	
	skydome_ = new Skydome();
	deathParticle_ = new DeathParticle();
	Vector3 playerposition_ = mapChipField_->GetMapChipPositionByIndex(2, 18);
	//パーティクルはプレイヤーと同じ座標
	deathParticle_->Init(&viewProjection_,playerposition_);
	CameraController::Rect cameraArea = {12.0f,100-12.0f,6.0f,6.0f};
	cameraController_->SetMovableArea( cameraArea);
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	mapChipField_->LoadMapChipCsv("Resources/map.csv");
	//自機と敵
	player_->Initialize(&viewProjection_,playerposition_);
	Enemy* newEnemy = new Enemy();
	/*for (int32_t i = 0; i < 3; ++i) {
		enemyposition_ = mapChipField_->GetMapChipPositionByIndex(18+(i*2),18-(i*2));
	}*/
	Vector3 enemyposition_ = mapChipField_->GetMapChipPositionByIndex(25, 18);
	newEnemy->init(&viewProjection_,enemyposition_ );
	enemies_.push_back(newEnemy);
	//<<<<<<< Updated upstream
	//=======
	//<<<<<<< Updated upstream
	skydome_->Initialize(modelSkydome_, textureHandle_, &viewProjection_);

	//>>>>>>> Stashed changes
	GenerateBlocks();
	/*const uint32_t kNumBlockHorizontal = 20;
	const uint32_t kNumBlockVirtical = 10;
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;*/
	//	=======

	 //playerposition_;

//	player_->Initialize(model_, &viewProjection_,playerposition_ );
	player_->SetMapChipField(mapChipField_);
	
	//<<<<<<< Updated upstream
	//=======
	skydome_->Initialize(modelSkydome_, textureHandle_, &viewProjection_);
	//>>>>>>> Stashed changes]
	// mapChipField_->LoadMapChipCsv("Resource/map.csv ");
	debugCamera_ = new DebugCamera(1280, 720);
//	CheckAllCollision();
	phase_ = Phase::kPlay;

}
void GameScene::GenerateBlocks() {
	uint32_t numBlockVirtical = mapChipField_->GetkNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetkNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {

		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {

		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ =
				    mapChipField_->GetMapChipPositionByIndex(j, i);

				//} else {
				// worldTransformBlocks_[i][j] = nullptr;
			}
		}
	}
}
void GameScene::CheckAllCollision()
{
	AABB aabb1,aabb2,aabb3;
	
aabb1 = player_->GetAABB();
for (auto* enemy : enemies_) {
	aabb2 = enemy->GetAABB();
	if (IsCollision(aabb1, aabb2)){
		player_->OnCollision(enemy);
	enemy->OnCollision(player_);

	}

}
aabb3 = goals_->GetAABB();
if (IsCollision(aabb1,aabb3)) {
 
	goals_->OnCollision(player_);
	if (goals_->IsGet()) {
		clearFlag_ = true;
	}

	

}


}
void GameScene::Update() {
	
	
ChangePhase();
switch (phase_) {
		case Phase::kPlay:
			
	//天球の更新
	skydome_->Update();
	//自機の更新
	player_->Update();
	//敵の更新
	for (Enemy* enemy : enemies_) {
	enemy->Update();

	}
	goals_->Update();
			//カメラの更新
	UpdateCamera();
	// ブロックの更新
	UpdateBlocks();
			/*debugCamera_->Update();
	cameraController_->Update();*/
	/*for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdetaMatrix();
		}
	}*/
	//全部の当たり判定
	CheckAllCollision();
	/*if (deathParticle_) {
		deathParticle_->Update();
	}*/
			
	break;
		
	case Phase::kDeath:
		if (deathParticle_ && deathParticle_->IsFinished()) {
			finished_ = true;
		}
	//天球の更新	
	skydome_->Update();

		/*debugCamera_->Update();
		cameraController_->Update();*/
	//敵の更新
	for (Enemy* enemy : enemies_) {
	enemy->Update();
	}
	//パーティクルの更新
	if (deathParticle_) {
		deathParticle_->Update();
	}
		//カメラの更新
	UpdateCamera();
	//ブロックの更新
	UpdateBlocks();

	/*for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdetaMatrix();
		}
	}*/
	//CheckAllCollision();	
			break;
	}
//カメラの更新があった場所

	/*debugCamera_->Update();
	player_->Update();
	cameraController_->Update();*/
	// ブロックの更新があった場所
	/*for (Enemy* enemy : enemies_) {
	enemy->Update();
5
	}

	CheckAllCollision();

	if (deathParticle_) {
		deathParticle_->Update();
	

	}*/

}
void GameScene::ChangePhase() {
	switch (phase_) {
		case Phase::kPlay:
			if (player_->GetIsDead()) {
				phase_ = Phase::kDeath;
				const Vector3& deathParticlesPosition = player_->GetWorldPosition();
				deathParticle_->Init(&viewProjection_,deathParticlesPosition);

			}
			if (goals_->IsGet()) {
				phase_ = Phase::kClear;

			}
	break;

		
	case Phase::kDeath:
		
		
		
		break;
	case Phase::kClear:
		
		
		
		break;

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
	skydome_->Draw();
	if(!player_->GetIsDead()){
	player_->Draw();
	
	}
	if (deathParticle_) {

	deathParticle_->Draw();
	}
	for (Enemy* enemy : enemies_) {

	enemy->Draw();

	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}
	goals_->Draw();
	/// </summary>

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
void GameScene::UpdateCamera() {
	cameraController_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		/*if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else
			isDebugCameraActive_ = true;*/
	isDebugCameraActive_ = !isDebugCameraActive_;
	}

#endif

	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		//viewProjection_.UpdateMatrix();
		viewProjection_.matView=cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection=cameraController_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

	}
}
void GameScene::UpdateBlocks() {
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			worldTransformBlock->UpdetaMatrix();
		}
	}
}

