#pragma once
#include <Box2D/Common/b2Settings.h>

float RadiansToDegree(float radians)
{
    return radians * 180.0f / b2_pi;
}

float DegreesToRadians(float degrees)
{
    return degrees * b2_pi / 180.0f;
}