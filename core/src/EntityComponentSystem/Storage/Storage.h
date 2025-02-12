#pragma once

#include <type_traits>

/* Forward declarations for better compile-time and organization */
namespace std
{
	template<typename T>
	class allocator;

	template <typename T, typename Allocator = allocator<T>>
	class vector;
}

namespace ECS
{
	/**
	 * @brief StorageTraits struct, exists for better
	 * organization, and, accessing types through storage
	 * interface.
	 * 
	 * @todo Implement a Storage interface, use CRTP.
	 * @todo Create tests for Storage.
	 * 
	 * @raisewarning ALLOCATOR SHOULD BE IMPLEMENTED TO SUPPORT BLOCK ALLOCATION.
	 */
	template<typename Type, typename Entity>
	struct StorageTraits
	{
		using ValueType = Type;
		using ValueRef = ValueType&;
		using ValuePtr = ValueType*;
		using IndexType = Entity;
	};

	template<typename Derived, typename Traits>
	class Storage
	{
	public:
		/* Defining type traits for better convention. */
		using ValueType = typename Traits::ValueType;
		using ValueRef = typename Traits::ValueRef;
		using ValuePtr = typename Traits::ValuePtr;
		using IndexType = typename Traits::IndexType;
	public:
		bool Add(IndexType index, ValueType&& value)
		{
			return Self()->AddImpl(index, std::move(value));
		}

		bool Remove(IndexType index)
		{
			return Self()->RemoveImpl(index);
		}

		ValuePtr Get(IndexType index)
		{
			return Self()->GetImpl(index);
		}

		bool Has(IndexType index)
		{
			return Self()->HasImpl(index);
		}
	private:
		Derived* Self() { return static_cast<Derived*>(this); }
	};
}
