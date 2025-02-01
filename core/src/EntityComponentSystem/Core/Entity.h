#pragma once


namespace ECS
{
	using Entity = uint32_t;
}

#define INVALID_ENTITY static_cast<ECS::Entity>(-1)