#include "WorldTransform.h"
#include "math/Affine.h"
using namespace KamataEngine;
void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}