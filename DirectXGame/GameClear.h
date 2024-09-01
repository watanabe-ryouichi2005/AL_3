#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
class GameClear 
{public:
~GameClear();
void Init();
void Update();
void Draw();
bool IsFinished(){return finished;};



private:
bool IsDead = false;
bool finished = false;
Model* model_ = nullptr;
ViewProjection viewProjection_ ;
WorldTransform worldTransform_ ;





};