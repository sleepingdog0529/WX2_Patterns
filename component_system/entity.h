/*********************************************************************
 * @file	entity.h
 * @author	SleepingDog0529
 * @date	2021/07/23 22:40
 * @brief	エンティティ仮想クラス
*********************************************************************/
#pragma once
#include <string_view>
#include "entity_container.h"
#include "component.h"
#include "string_hash.h"

namespace wx2 {

	class EntityContainer;
	class AbstractComponent;

	namespace detail
	{
		template <class T>
		concept ComponentDerived = std::derived_from<T, AbstractComponent>;
	}

	class Entity
	{
	public:
		template<detail::ComponentDerived T>
		using ComponentPtr = std::shared_ptr<T>;
		template<detail::ComponentDerived T>
		using ComponentPtrList = std::vector<ComponentPtr<T>>;

		explicit Entity(const EntityContainer& parent, std::string_view name) :
			parent_(&parent),
			name_(name.begin(), name.end())
		{};
		virtual ~Entity() = default;

		template<detail::ComponentDerived Component>
		ComponentPtr<Component> AddComponent()
		{
			auto component = std::make_shared<Component>();
			component->parent_ = this;
			components_.emplace(Component::GetTypeName(), component);
			return component;
		}

		template<detail::ComponentDerived Component>
		ComponentPtr<Component> GetComponent()
		{
			const auto& it = components_.find(Component::GetTypeName());
			if (it == components_.end())
				return nullptr;
			return std::static_pointer_cast<Component>(it->second);
		}

		template<detail::ComponentDerived Component>
		ComponentPtrList<Component> GetComponents()
		{
			auto [first, last] = components_.equal_range(Component::GetTypeName());
			ComponentPtrList<Component> ret;
			std::transform(first, last, std::back_inserter(ret), [](const auto& it)
				{ return std::static_pointer_cast<Component>(it.second); });
			return ret;
		}

		template<detail::ComponentDerived Component>
		void RemoveComponent(ComponentPtr<Component>& component)
		{
			std::erase_if(components_, 
				[&](const auto& it){ return it.second == component; });
		}

		template<detail::ComponentDerived Component>
		ComponentPtrList<Component> HasComponents()
		{
			return components_.find(Component::GetTypeName()) != components_.end();
		}

		[[nodiscard]] std::string_view GetName() { return std::string_view(name_); }

	private:
		const EntityContainer* parent_;
		std::string name_;
		std::unordered_multimap<std::string, ComponentPtr<AbstractComponent>, StringHash, StringCompare> components_;
	};

}