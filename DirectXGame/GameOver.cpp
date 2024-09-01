#include<numbers>
#include<cmath>
#include "GameOver.h"
#include "DirectXCommon.h"
#include "Input.h"
GameOverScene::~GameOverScene(){delete textModel_;}
void GameOverScene::Init()
{textModel_ = Model::CreateFromOBJ("GameOver",true);
viewProjection_.Initialize();
worldTransform_.Initialize();
//const float kGameOverFont = 100.0f;
//worldTransform_.scale_ ={kGameOverFont,kGameOverFont,kGameOverFont};
//worldTransform_.rotation_.y = -0.62f * std::numbers::pi_v<float>;


}
void GameOverScene::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished = true;

	}



}
void GameOverScene::Draw()
{
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance(); 
ID3D12GraphicsCommandList* commondList = dxCommon_ -> GetCommandList();
Model::PreDraw(commondList);
textModel_->Draw(worldTransform_,viewProjection_);
Model::PostDraw();

}