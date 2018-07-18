#pragma once
#include "../header/game.h"
#include "../header/vector.h"

typedef enum {
    CT_NULL    = 0,
    CT_WHITE   = 1,
    CT_BLUE    = 2,
    CT_RED     = 3,
    CT_YELLLOW = 4,
    CT_GREEN   = 5,
    CT_CYAN    = 6,
    CT_ORANGE  = 7,
    CT_PURPLE  = 8,
} ColorType;

void LookatVector(Vector3f direction);
void LookatPoint(Vector3f loc, Vector3f point);
void TranslateVector(Vector3f delta);
Vector3f getNewSideVector(Vector3f forward);
Vector3f getNewUPVector(Vector3f forward);
void InitRand();
int RandBetween(int min, int max);
bool IsBetween(float n, float min, float max);
void printString(float x, float y, const char* str, int length);
void Colored(ColorType type);