#pragma once

#include "Storage.h"

namespace ECS
{
	/**
	 * @brief ComponentPool class, stores components
	 * of type "Type", who has owner "Entity". This class
	 * represents the pool of 1 component.
	 */
	template<typename Type, typename Entity>
	class ComponentPool : public Storage<ComponentPool<Type, Entity>, StorageTraits<Type, Entity>>
	{
		static_assert(std::is_integral_v<Entity>, "Entity must be an integral type!");
		static_assert(std::is_unsigned_v<Entity>, "Entity must be an unsigned type!");
	public:
		/* Defining type traits for better convention. */
		using Traits = StorageTraits<Type, Entity>;

		using ValueType = typename Traits::ValueType;
		using ValueRef = typename Traits::ValueRef;
		using ValuePtr = typename Traits::ValuePtr;
		using IndexType = typename Traits::IndexType;

		/* Container types */
		using SparseSetType = std::vector<IndexType>;
		using DenseSetType = std::vector<ValueType>;
	public:
		ComponentPool() : m_SparseSet(SparseSetType{}), m_DenseSet(DenseSetType{}) {}
	private:
		/**
		 * @brief Adds Component to the storage.
		 *
		 * @param Entity : Parent of the component.
		 * @param Component : Component object.
		 *
		 * @returns true : if operation is successful.
		 * @returns false : if operation is not successful.
		 */
		bool AddImpl(IndexType entity, ValueType& value)
		{
			if (Has(entity)) return false;

			if (entity >= m_SparseSet.size())
			{
				m_SparseSet.resize(entity + 1, static_cast<IndexType>(-1));
			}

			if (m_SparseSet[entity] == static_cast<IndexType>(-1))
			{
				m_SparseSet[entity] = m_DenseSet.size();
				m_DenseSet.emplace_back(std::move(value));
				return true;
			}
			return false;
		}
		
		/**
		 * @brief Removes the component from DenseSet and,
		 * removes the ownership of Entity from SparseSet.
		 *
		 * @param Entity : Parent of the component.
		 *
		 * @returns true : if operation is successful.
		 * @returns false : if operation is not successful.
		 */
		bool RemoveImpl(IndexType entity)
		{
			if (!Has(entity)) return false;

			IndexType DenseIndex = m_SparseSet[entity];
			IndexType LastIndex = m_DenseSet.size() - 1;

			if (LastIndex != DenseIndex)
			{
				Swap(m_SparseSet[LastIndex], m_SparseSet[DenseIndex]);
				Swap(m_DenseSet[LastIndex], m_DenseSet[DenseIndex]);
				m_SparseSet[LastIndex] = DenseIndex;
			}

			m_SparseSet[entity] = static_cast<IndexType>(-1);
			m_DenseSet.pop_back();
			return true;
		}

		/**
		 * @brief Component existence test by checking sizes
		 * and value of SparseSet entry.
		 *
		 * @param Entity : Parent of the component.
		 *
		 * @returns true : if entity has component.
		 * @returns false : if entity does not have component.
		 */
		[[nodiscard]] inline bool HasImpl(IndexType entity) noexcept
		{
			if (entity >= m_SparseSet.size() || m_SparseSet[entity] == static_cast<IndexType>(-1)) return false;
			if (m_SparseSet[entity] >= m_DenseSet.size()) return false;
			return true;
		}

		/**
		 * @brief Gets component of the given Entity.
		 *
		 * @param Entity : Parent of the component.
		 *
		 * @returns Type& : reference of component.
		 */
		[[nodiscard]] ValuePtr GetImpl(IndexType entity)
		{
			if (!Has(entity))
			{
				LOG_INFO("Entity does not have component.");
				return nullptr;
			}
			return static_cast<ValuePtr>(&m_DenseSet[m_SparseSet[entity]]);
		}
	private:
		friend class Storage<ComponentPool<Type, Entity>, Traits>;
	private:
		/* Container holding the owner's representation of component. */
		SparseSetType m_SparseSet;
		/* Container holding all components contagiously in memory. */
		DenseSetType m_DenseSet;
	private:
		/**
		 * @brief Swaps the allocated memory.
		 *
		 * @warning Will be deprecated.
		 *
		 * @todo Put the function inside SparseSet and DenseSet wrappers.
		 */
		template<typename T>
		void Swap(T& lhs, T& rhs)
		{
			T Temp = std::move(lhs);
			lhs = std::move(rhs);
			rhs = std::move(Temp);
		}
	};
}