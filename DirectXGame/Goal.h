#include "AABB.h"
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
class Player;
class Goal {
public:
~Goal();
void Init(Model* model,ViewProjection* viewProjection,const Vector3 &position);
void Update();
void Draw();
Vector3 GetWorldPosition();
AABB GetAABB();
void OnCollision(Player* player);
bool IsGet(){return isGet_;};


private:
static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	Model* model_ = nullptr;
//Model* boxModel_ =nullptr;
//Model* clearTextModel_ = nullptr;
WorldTransform worldTransform_ ;
ViewProjection* viewProjection_ = nullptr ;
bool isGet_ = false;















};