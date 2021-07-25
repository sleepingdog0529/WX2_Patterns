/*********************************************************************
 * @file	entity_pool.h
 * @author	SleepingDog0529
 * @date	2021/07/23 22:34
 * @brief	エンティティプール
*********************************************************************/
#pragma once
#include <ranges>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include "entity.h"
#include "string_hash.h"

namespace wx2 {

	class Entity;

	class EntityContainer
	{
	public:
		using EntityPtr = std::shared_ptr<Entity>;
		using EntityPtrList = std::vector<EntityPtr>;

		EntityPtr CreateEntity(std::string_view name);
		EntityPtr FindEntity(std::string_view name);
		EntityPtrList FindEntities(std::string_view name);

		template <typename Pred>
		EntityPtr FindEntityIf(Pred&& pred)
		{
			auto ret = std::ranges::find_if(
				entities_,
				[p = std::forward<Pred>(pred)](const auto& it) { return p(it.second); });
			return ret->second;
		}

		template <typename Pred>
		EntityPtrList FindEntitiesIf(Pred&& pred)
		{
			EntityPtrList ret;
			std::ranges::copy_if(
				entities_ | std::views::transform([p = std::forward<Pred>(pred)](const auto& it) { return it.second; }),
				std::back_inserter(ret),
				std::forward<Pred>(pred));
			return ret;
		}

	private:
		std::unordered_multimap<std::string, EntityPtr, StringHash, StringCompare> entities_;
	};

}