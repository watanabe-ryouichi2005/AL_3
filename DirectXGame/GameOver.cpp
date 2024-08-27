#include "GameOver.h"
GameOverScene::~GameOverScene(){delete textModel_;}
void GameOverScene::Init()
{textModel_ = Model::CreateFromOBJ("GameOver",true);
viewProjection_.Initialize();


}
void GameOverScene::Update()
{
}
void GameOverScene::Draw()
{
}