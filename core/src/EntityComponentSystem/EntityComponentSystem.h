#pragma once

/**
 * @todo Since the convention is manifestly different
 * from rest of the application, consider making this
 * an external API.
 * 
 * @todo Analyze includes, delete unnecesary entries, and organize the code.
 */

/* Core includes */
#include "Core/Entity.h"
#include "Core/Registry.h"
/* Core includes end */

/* Storage includes */
#include "Storage/Storage.h"
#include "Storage/ComponentPool.h"
#include "Storage/DenseContainer.h"
/* Storage includes end */

/* Types includes */
#include "Types/TypeUtils.h"
/* Types includes end */

/**
 * @brief Entity Component System namespace
 */
namespace ECS
{
	/* Externalized for easier usage. */
	using Entity = internals::entity<uint32_t>::type;
	using System = Registry<Entity>;
}