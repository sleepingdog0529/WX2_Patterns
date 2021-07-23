#include "event_dispacher.h"
#include <iostream>
#include <string>

namespace {

	// �C�x���g�̎�� (�����񓙂ł���)
	enum class InputEvent
	{
		Int,
		Char,
	};

	// �C�x���g���
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

	// �R�[���o�b�N
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

	// �C�x���g�̓o�^
	event_dispacher.AddEventListener(InputEvent::Int, OnIntInput);
	event_dispacher.AddEventListener(InputEvent::Char, OnCharInput);

	std::string input = {};

	// "quit"�ŏI��
	while (input != "quit")
	{
		for (const auto& c : input)
		{
			// �C�x���g�����s
			if (c >= '0' && c <= '9')
				event_dispacher.Dispatch(InputEvent::Int, IntInputEventInfo(static_cast<int>(c - '0')));
			else
				event_dispacher.Dispatch(InputEvent::Char, CharInputEventInfo(c));
		}

		std::cout << "���p���������͂��Ă�������\n>> ";
		std::getline(std::cin, input);
	}

	return 0;
}