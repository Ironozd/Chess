#pragma once

namespace ECS
{
	namespace internals
	{
		uint64_t TypeCounter = 0;
	}
	template<typename Type>
	struct Hash final
	{
		static const uint64_t Value;

		static const uint64_t NextType();
	};

	template<typename Type>
	const uint64_t Hash<Type>::Value = Hash::NextType();

	template<typename Type>
	inline const uint64_t Hash<Type>::NextType()
	{
		return internals::TypeCounter++;
	}
}