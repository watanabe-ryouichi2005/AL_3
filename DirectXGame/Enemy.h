#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"ViewProjection.h"
class Enemy {
public:
void init(ViewProjection* viewProjection,const Vector3 position);
void Update();
void Draw();
void Move();
private:
// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Vector3 velosity_ = {};
	float walkTimer_ = 0.0f;

	static inline const float kWalkSpeed = 0.02f;
	//最初の角度
	static inline const float kWalkMotionAngleStart = 0.0f;
	//最後の角度
	static inline const float kWalkMotionAngleEnd = 30.0f;
	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 1.0f;
	
	


};