#include"Goal.h"
#include"Player.h"
#include"cassert"
Goal::~Goal() {
	
}
void Goal::Init(Model* model,ViewProjection* viewProjection,const Vector3 &position) 
{
assert(model);
model_ = model;
	viewProjection_=viewProjection;
	worldTransform_.Initialize();
// ワールド変換の初期化
	worldTransform_.translation_ = position;
	
	//boxModel_ = Model::CreateFromOBJ("ClearBox");
	//clearTextModel_ = Model::CreateFromOBJ("GameClear",true);



}
void Goal::Update() {
worldTransform_.UpdetaMatrix();
}
void Goal::Draw() {
model_->Draw(worldTransform_, *viewProjection_);
}
Vector3 Goal::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;

}
AABB Goal::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPos.x - kWidth/2.0f,worldPos.y-kHeight/2.0f,worldPos.z-kWidth/2.0f};
	aabb.max = {worldPos.x + kWidth/2.0f,worldPos.y+kHeight/2.0f,worldPos.z+kWidth/2.0f};

return aabb;
}
void Goal::OnCollision(Player * player)
{
	(void) player;
	isGet_ = true;

}