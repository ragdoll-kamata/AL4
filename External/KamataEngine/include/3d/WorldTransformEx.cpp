#include "WorldTransform.h"
#include "math/Affine.h"
#include "math/MathUtility.h"
using namespace KamataEngine;
using namespace MathUtility;
void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}

	TransferMatrix();
}