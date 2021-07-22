#include "event_dispacher.h"
#include <iostream>
#include <string>

namespace {

	enum class InputEvent
	{
		Int,
		Char,
	};

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
	event_dispacher.AddEventListener(InputEvent::Int, OnIntInput);
	event_dispacher.AddEventListener(InputEvent::Char, OnCharInput);

	std::string input;
	std::cout << "”¼Šp•¶Žš—ñ‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n>> ";
	std::getline(std::cin, input);

	while (!input.empty())
	{
		char front = input.front();
		input.erase(input.begin());

		if (front >= '0' && front <= '9')
			event_dispacher.Dispatch(InputEvent::Int, IntInputEventInfo(static_cast<int>(front - '0')));
		else
			event_dispacher.Dispatch(InputEvent::Char, CharInputEventInfo(front));
	}

	std::cin.get();

	return 0;
}