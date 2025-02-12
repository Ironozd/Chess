#pragma once

#include <type_traits>


namespace ECS
{ 
	namespace internals
	{
		/**
		 * @brief Created for future use, holds metadata.
		 */
		template<typename Type>
		struct entity 
		{
			static_assert(std::is_integral_v<Type>, "ECS::internals::entity type must be integral.");
			static_assert(std::is_unsigned_v<Type>, "ECS::internals::entity type must be unsigned.");
			static_assert(std::is_arithmetic_v<Type>, "ECS::internals::entity type must be arithmetic.");
			/* Type meta-data */
			using type = Type;
			static constexpr size_t size = sizeof(type);
			static constexpr size_t bits = sizeof(type) << 3;
		};
	}
}