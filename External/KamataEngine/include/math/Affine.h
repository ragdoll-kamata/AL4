#pragma once
#include <math/Matrix4x4.h>
#include <math/Vector3.h>

using namespace KamataEngine;

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
