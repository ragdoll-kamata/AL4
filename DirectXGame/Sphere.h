#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
struct Sphere {
	Vector3 pos;
	float radius;
};

bool CollisionDetection(Sphere a, Sphere b);