#pragma once
#include "FishEngine/ECS.hpp"


class Light : public ECS::Component
{
	COMPONENT(Light);
public:
	Vector3 direction = { 0, 0, -1 };
};