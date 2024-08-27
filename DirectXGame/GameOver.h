#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class GameOverScene {
public:
~GameOverScene();
void Init();
void Update();
void Draw();



private:
Model *textModel_ = nullptr;
ViewProjection viewProjection_ ;
WorldTransform worldTransform_ ;







};