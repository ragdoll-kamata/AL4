#pragma once
#include <math/Matrix4x4.h>
#include <math/Vector3.h>

using namespace KamataEngine;
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 Transform(const Vector3& v, const Matrix4x4& m1);
