#include<numbers>
#include<cmath>
#include "DirectXCommon.h"
#include "Input.h"
#include "GameClear.h"
GameClear::~GameClear() {
delete model_;
}
void GameClear::Init() {
model_ = Model::CreateFromOBJ("GameClear",true);
viewProjection_.Initialize();
worldTransform_.Initialize();

}
void GameClear::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished = true;

	}
}
void GameClear::Draw() {
DirectXCommon* dxCommon_ = DirectXCommon::GetInstance(); 
ID3D12GraphicsCommandList* commondList = dxCommon_ -> GetCommandList();
Model::PreDraw(commondList);
model_->Draw(worldTransform_, viewProjection_);
Model::PostDraw();

}