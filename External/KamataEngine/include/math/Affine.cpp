#include "Affine.h"
#include <cmath>
#include "math/MathUtility.h"
using namespace MathUtility;

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 matrixRotate = MakeRotateXMatrix(rotate.x) * MakeRotateYMatrix(rotate.y) * MakeRotateZMatrix(rotate.z);
	Matrix4x4 a = {
	    scale.x * matrixRotate.m[0][0],
	    scale.x * matrixRotate.m[0][1],
	    scale.x * matrixRotate.m[0][2],
	    0.0f,
	    scale.y * matrixRotate.m[1][0],
	    scale.y * matrixRotate.m[1][1],
	    scale.y * matrixRotate.m[1][2],
	    0.0f,
	    scale.z * matrixRotate.m[2][0],
	    scale.z * matrixRotate.m[2][1],
	    scale.z * matrixRotate.m[2][2],
	    0.0f,
	    translate.x,
	    translate.y,
	    translate.z,
	    1.0f};
	return a;
}


