#define NOMINMAX
#include<algorithm>
#include<cassert>
#include<numbers>
#include"Enemy.h"
void Enemy::init(/*ViewProjection* viewProjection_,*/const Vector3 position)
{
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	model_ = Model::CreateFromOBJ("enemy");
	// 左を向かせる(πとか数値情報が定義されてる)
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

}
void Enemy::Update()
{
}
void Enemy::Draw()
{
model_->Draw(worldTransform_, *viewProjection_);
}
void Enemy::Move() {


}