#pragma once
#include "../header/game.h"
#include "../header/vector.h"

void LookatVector(Vector3f direction);
void LookatPoint(Vector3f loc, Vector3f point);
void TranslateVector(Vector3f delta);
Vector3f getNewSideVector(Vector3f forward);
Vector3f getNewUPVector(Vector3f forward);
void InitRand();
int RandBetween(int min, int max);
bool IsBetween(float n, float min, float max);