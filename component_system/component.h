/*********************************************************************
 * @file	component.h
 * @author	SleepingDog0529
 * @date	2021/07/06 13:24
*********************************************************************/
#pragma once
#include <string_view>
#include "entity.h"

#define WX3_DECLARE_COMPONENTS_IMPL(name)					\
private:													\
	static constexpr std::string_view GetTypeName() 		\
	{														\
		return #name;										\
	}														\
	friend class Entity

namespace wx2 {

	class Entity;

	class AbstractComponent
	{
	public:
		friend Entity;

		AbstractComponent() = default;
		virtual ~AbstractComponent() = default;

		virtual void Update() = 0;
		virtual void Draw() = 0;

	private:
		Entity* parent_;
	};

}