#pragma once

#include "../Storage/DenseContainer.h"
#include "../Storage/ComponentPool.h"

/**
 * @todo Finish documentation.
 */

namespace ECS
{
	template<typename Entity>
	class Registry
	{
	public:
		using IndexType = Entity;
		using HashType = uint64_t;

		using EntityContainerType = std::vector<IndexType>;
		using ComponentPoolGroupType = DenseContainer<HashType, void*>;
	public:
		Registry() : m_EntityContainer(EntityContainerType{}), 
			m_ComponentPoolGroups(ComponentPoolGroupType{})
		{
			m_EntityContainer.reserve(1000); /** @todo TEMPORARY, WRITE VECTOR ALLOCATOR */ 
		}
	public:
		/**
		 * @todo Modify registry entity create function.
		 */
		IndexType Create()
		{
			IndexType index = m_EntityContainer.size() - 1;
			if (index == m_EntityContainer.capacity())
			{
				m_EntityContainer.reserve(m_EntityContainer.capacity() * 2);
			}

			m_EntityContainer[index] = index;

			return m_EntityContainer[index];
		}

		/**
		 * @todo Complete destroy entity class.
		 */
		bool Destroy(IndexType entity)
		{
			//if()
		}

		bool IsAlive(IndexType entity)
		{
			if (entity >= m_EntityContainer.capacity() || m_EntityContainer[entity] == static_cast<IndexType>(-1)) return false;
			return true;
		}

		template<typename Type, typename...ARGS>
		bool Add(IndexType entity, ARGS...args)
		{
			decltype(auto) storage = Storage<Type>();
			if (storage.Has(entity)) return false;
			return storage.Add(entity, Type(std::forward<ARGS>(args)...));
		}

		template<typename Type>
		bool Remove(IndexType entity)
		{
			decltype(auto) storage = Storage<Type>();
			if (!storage.Has(entity)) return false;
			return storage.Remove(entity);
		}

		template<typename Type>
		Type& Get(IndexType entity)
		{
			decltype(auto) storage = Storage<Type>();

			if (storage.Get(entity) == nullptr)
			{
				LOG_ERROR("Component does not exist!");
				assert(false);
			}
			return static_cast<Type&>(*storage.Get(entity));
		}

		template<typename Type>
		ComponentPool<Type, IndexType>& Storage()
		{
			HashType Index = Hash<Type>::Value;

			if (!m_ComponentPoolGroups.Exists(Index))
			{
				m_ComponentPoolGroups.Insert(Index, new ComponentPool<Type, IndexType>());
			}

			return *static_cast<ComponentPool<Type, IndexType>*>(m_ComponentPoolGroups[Index]);
		}
	private:
		EntityContainerType m_EntityContainer;
		ComponentPoolGroupType m_ComponentPoolGroups;
	};
}