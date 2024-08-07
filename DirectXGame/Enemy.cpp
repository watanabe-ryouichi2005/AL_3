#define NOMINMAX
#include<algorithm>
#include<cassert>
#include<numbers>
#include"Enemy.h"
#include"MyMath.h"
void Enemy::init(ViewProjection* viewProjection,const Vector3 position)
{
	// ワールド変換の初期化
	worldTransform_.Initialize();
	viewProjection_=viewProjection;
	worldTransform_.translation_ = position;

	model_ = Model::CreateFromOBJ("enemy");
	// 左を向かせる(πとか数値情報が定義されてる)
	worldTransform_.rotation_.y = std::numbers::pi_v<float>*3.0f / 2.0f;
	velosity_={-kWalkSpeed,0,0};
	walkTimer_=0.0f;

}
void Enemy::Update()
{
	worldTransform_.translation_ += velosity_;
	walkTimer_ +=1.0f/60.0f;
	worldTransform_.rotation_.x = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer_ / kWalkMotionTime);

	// 行列計算
	worldTransform_.UpdetaMatrix();
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}
void Enemy::Draw()
{
model_->Draw(worldTransform_, *viewProjection_);
}
//void Enemy::Move() {
//
//
//}