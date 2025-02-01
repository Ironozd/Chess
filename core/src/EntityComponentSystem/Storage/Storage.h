#pragma once

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
	 * 
	 * @raisewarning ALLOCATOR SHOULD BE IMPLEMENTED TO SUPPORT BLOCK ALLOCATION.
	 */
	template<typename Type, typename Entity>
	struct StorageTraits
	{
		using ValueType = Type;
		using ValueRef = ValueType&;
		using IndexType = Entity;
	};

	/**
	 * @brief ComponentStorage class, stores components
	 * of type "Type", who has owner "Entity". This class
	 * represents the pool of 1 component.
	 */
	template<typename Type, typename Entity>
	class ComponentStorage
	{
	public:
		/* Defining type traits for a better convention. */
		using Traits = StorageTraits<Type, Entity>;

		using ValueType = typename Traits::ValueType;
		using ValueRef = typename Traits::ValueType&;
		using IndexType = typename Traits::IndexType;

		/* Container types */
		using SparseSetType = std::vector<IndexType>;
		using DenseSetType = std::vector<ValueType>;
	public:

		ComponentStorage() : m_SparseSet(SparseSetType{}), m_DenseSet(DenseSetType{}) { }

		/**
		 * @brief Adds Component to the storage.
		 * 
		 * @param Entity : Parent of the component.
		 * @param Component : Component object.
		 * 
		 * @returns true : if operation is successful.
		 * @returns false : if operation is not successful.
		 */
		bool Add(IndexType index, ValueType& value)
		{
			if (Has(index)) return false;
			
			if (index >= m_SparseSet.size())
			{
				m_SparseSet.resize(index + 1, static_cast<IndexType>(-1));
			}

			if (m_SparseSet[index] == static_cast<IndexType>(-1))
			{
				m_SparseSet[index] = m_DenseSet.size();
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
		bool Remove(IndexType index)
		{
			if (!Has(index)) return false;

			IndexType DenseIndex = m_SparseSet[index];
			IndexType LastIndex = m_DenseSet.size() - 1;

			if (LastIndex != DenseIndex)
			{
				Swap(m_SparseSet[LastIndex], m_SparseSet[DenseIndex]);
				Swap(m_DenseSet[LastIndex], m_DenseSet[DenseIndex]);
				m_SparseSet[LastIndex] = DenseIndex;
			}

			m_SparseSet[index] = static_cast<IndexType>(-1);
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
		bool Has(IndexType index)
		{
			if (index >= m_SparseSet.size() || m_SparseSet[index] == static_cast<IndexType>(-1)) return false;
			if (m_SparseSet[index] >= m_DenseSet.size()) return false;
			return true;
		}

		/**
		 * @brief Gets component of the given Entity.
		 * 
		 * @param Entity : Parent of the component.
		 * 
		 * @returns Type& : reference of component.
		 */
		ValueRef Get(IndexType index)
		{
			if (!Has(index))
			{
				LOG_INFO("Entity does not have component.");
				assert(false);
			}
			return m_DenseSet[m_SparseSet[index]];
		}
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
