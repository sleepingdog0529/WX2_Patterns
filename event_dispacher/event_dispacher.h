/*********************************************************************
 * @file	event_dispacher.h
 * @author	SleepingDog0529
 * @date	2021/07/19 16:42
 * @brief	イベントディスパッチャー
*********************************************************************/
#pragma once
#include <unordered_map>
#include <functional>
#include <concepts>

namespace wx2 {

	template <typename EventInfoBase, typename EventType>
	class EventDispacher
	{
	public:
		template<typename T>
		using CallbackFuncType = std::function<void(T&&)>;

		EventDispacher() = default;
		virtual ~EventDispacher() = default;

		// イベント登録
		template <typename F, typename... EventInfoType>
		void AddEventListener(EventType event_type, F&& callback, EventInfoType&&...)
		{
			static_assert(sizeof...(EventInfoType) <= 1);
			auto [it, unuse] = callbacks_.try_emplace(event_type, std::vector<CallbackFuncType<EventInfoBase>>());
			it->second.emplace_back([cb = std::forward<F>(callback)] (EventInfoBase&& e) { cb(static_cast<EventInfoType&&>(e)); });
		}

		// イベント呼び出し
		template <typename EventInfoType>
		requires std::convertible_to<EventInfoType, EventInfoBase>
		void Dispatch(EventType event_type, EventInfoType&& event)
		{
			auto it = callbacks_.find(event_type);
			if (it == callbacks_.end())
				return;

			for (const auto& e : it->second)
			{
				e(std::forward<EventInfoBase>(event));
			}
		}

	private:
		std::unordered_map<EventType, std::vector<CallbackFuncType<EventInfoBase>>> callbacks_;
	};

}