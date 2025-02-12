#pragma once

#include <cstdint>
#include "../../Core/Logger.h"

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
	namespace internals
	{
		/**
		 * @brief dense key_value_pair struct.
		 *
		 * @warning INTERNAL CODE! CONVENTION DIFFERS.
		 */
		enum key_value_pair_state : uint8_t
		{
			Empty = 0b00000000,
			Occupied = 0b00000001
		};
		/**
		 * @brief dense key_value_pair struct.
		 *
		 * @warning INTERNAL CODE! CONVENTION DIFFERS.
		 */
		template<typename KeyType, typename ValueType>
		struct key_value_pair
		{
			KeyType Key;
			ValueType Value;
			key_value_pair_state State;
			bool IsOccupied() const
			{
				return (State & key_value_pair_state::Occupied) == key_value_pair_state::Occupied;
			}
		};
	}
	/**
	 * @brief DenseContainer class, a dense key_value_pair
	 * container. Stores the ECS::internals::key_value_pair
	 * contagiously throughout the memory.
	 *
	 * @todo Add dynamic capacity increase feature, currently set
	 * to 100 (inline with current use-case).
	 */
	template<typename Key, typename Value>
	class DenseContainer
	{
	public:
		/* Defining type traits for better convention. */
		using KeyType = Key;
		using ValueType = Value;
		using ValueRef = ValueType&;

		using ContainerType = std::vector<ECS::internals::key_value_pair<KeyType, ValueType>>;
	public:
		DenseContainer(size_t Capacity = 100) : m_Container(ContainerType{})
		{
			m_Container.resize(Capacity);
		}

		void Insert(const KeyType& key, const ValueType& value)
		{
			KeyType Index = Hash(key);

			while (m_Container[Index].IsOccupied())
			{
				if (m_Container[Index].Key == key)
				{
					m_Container[Index].Value = value;
					return;
				}
				Index = (Index + 1) % m_Container.size();
			}

			m_Container[Index] = { key, value, ECS::internals::key_value_pair_state::Occupied };
		}

		ValueRef operator[](const KeyType& key)
		{
			KeyType Index = Hash(key);

			while (m_Container[Index].IsOccupied())
			{
				if (m_Container[Index].Key == key)
				{
					return m_Container[Index].Value;
				}
				Index = (Index + 1) % m_Container.size();
			}
			LOG_ERROR("Index not found!");
			assert(false);
		}

		bool Exists(const KeyType& key)
		{
			KeyType Index = Hash(key);

			while (m_Container[Index].IsOccupied())
			{
				if (m_Container[Index].Key == key)
				{
					return true;
				}
			}
			return false;
		}
	private:
		ContainerType m_Container;
	private:
		[[nodiscard]] KeyType Hash(const Key& key) const noexcept
		{
			return std::hash<Key>{}(key) % m_Container.size();
		}
	};
}