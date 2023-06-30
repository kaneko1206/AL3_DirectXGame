#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"



Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);