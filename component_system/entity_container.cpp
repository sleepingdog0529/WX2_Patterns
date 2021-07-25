#include "entity_container.h"

namespace wx2 {

	using EntityPtr = std::shared_ptr<Entity>;
	using EntityPtrList = std::vector<EntityPtr>;

	EntityPtr EntityContainer::CreateEntity(std::string_view name)
	{
		auto it = entities_.emplace(std::piecewise_construct,
			std::make_tuple(name),
			std::make_tuple(std::make_unique<Entity>(*this, name)));
		return it->second;
	}

	EntityPtr EntityContainer::FindEntity(std::string_view name)
	{
		auto it = entities_.find(name);
		return it->second;
	}

	EntityPtrList EntityContainer::FindEntities(std::string_view name)
	{
		auto [first, last] = entities_.equal_range(name);
		EntityPtrList ret;
		std::transform(first, last, std::back_inserter(ret),
			[](const auto& it) { return it.second; });
		return ret;
	}

}