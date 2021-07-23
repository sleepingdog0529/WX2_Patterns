#include "event_dispacher.h"
#include <iostream>
#include <string>

namespace {

	// イベントの種類 (文字列等でも可)
	enum class InputEvent
	{
		Int,
		Char,
	};

	// イベント情報
	struct IntInputEventInfo : wx2::IEventInfo
	{
		IntInputEventInfo(int v) : val(v) {}
		int val;
	};
	struct CharInputEventInfo : wx2::IEventInfo
	{
		CharInputEventInfo(int v) : val(v) {}
		char val;
	};

	// コールバック
	void OnIntInput(const IntInputEventInfo& info)
	{
		std::cout << "Input int : " << info.val << std::endl;
	}
	void OnCharInput(const CharInputEventInfo& info)
	{
		std::cout << "Input char: " << info.val << std::endl;
	}

}

int main()
{
	wx2::EventDispacher<InputEvent> event_dispacher;

	// イベントの登録
	event_dispacher.AddEventListener(InputEvent::Int, OnIntInput);
	event_dispacher.AddEventListener(InputEvent::Char, OnCharInput);

	std::string input = {};

	// "quit"で終了
	while (input != "quit")
	{
		for (const auto& c : input)
		{
			// イベントを実行
			if (c >= '0' && c <= '9')
				event_dispacher.Dispatch(InputEvent::Int, IntInputEventInfo(static_cast<int>(c - '0')));
			else
				event_dispacher.Dispatch(InputEvent::Char, CharInputEventInfo(c));
		}

		std::cout << "半角文字列を入力してください\n>> ";
		std::getline(std::cin, input);
	}

	return 0;
}