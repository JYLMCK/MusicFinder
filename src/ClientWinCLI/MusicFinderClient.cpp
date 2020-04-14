#include "MusicFinderClient.h"
#include <iostream>
#include <sstream>

MusicFinderClient::InputResult MusicFinderClient::_ParseInput(std::string& input)
{
	if (input.empty())
		return MusicFinderClient::InputResult::INVALID;

	std::stringstream ss;

	for (char& c : input)
		c = std::toupper(c);

	const static auto IsNoteChar = [&](char c) {
		return _noteChars.find(c) != std::string_view::npos;
	};
	const static auto IsValidChar = [&](char c) {
		return IsNoteChar(c) || (c == ',') || (c == ' ');
	};

	bool isSharpPossible = false;
	for (const char& c : input)
	{
		if (!IsValidChar(c))
			return InputResult::INVALID;

		if (c == ',')
		{
			isSharpPossible = false;
		}
		else if (c == ' ')
		{
			continue;
		}
		else
		{
			// c is one of "abcdefg#"
			if (c == '#')
			{
				if (!isSharpPossible)
					return InputResult::INVALID;
				ss << '#';
				isSharpPossible = false;
			}
			else
			{
				ss << ' ' << c;
				isSharpPossible = true;
			}
		}
	}

	// turn b# and e# to c and f, respectively
	// make _diffSequence here as well
	std::string str;
	std::stringstream tidyInput;
	std::vector<char> vNotesNum;
	while (ss >> str)
	{
		if (str == "E#")
		{
			tidyInput << "F ";
			vNotesNum.emplace_back(_notesToNum["F"]);
		}
		else if (str == "B#")
		{
			tidyInput << "C ";
			vNotesNum.emplace_back(_notesToNum["C"]);
		}
		else
		{
			tidyInput << str << ' ';
			vNotesNum.emplace_back(_notesToNum[str]);
		}
	}

	_noteSequence = tidyInput.str();

	char diff;
	for (std::size_t i = 0; i < vNotesNum.size() - 1; ++i)
	{
		diff = std::abs(vNotesNum[i] - vNotesNum[i + 1]);
		if (diff > 6)
			diff = 12 - diff;
		_diffSequence.push_back(diff + '0');
	}

	return InputResult::VALID;
}

void MusicFinderClient::GetInput()
{
	std::string str;
	std::cout << "\nEnter a note sequence (q to quit)\n> ";
	std::getline(std::cin, str);
	if (str == "q" || str == "Q")
		_status = InputResult::QUIT;
	else
		_status = _ParseInput(str);
}

const std::string& MusicFinderClient::GetNoteSequence() const
{
	return _noteSequence;
}

const std::string& MusicFinderClient::GetDiffSequence() const
{
	return _diffSequence;
}

MusicFinderClient::InputResult MusicFinderClient::GetStatus() const
{
	return _status;
}

void MusicFinderClient::Reset()
{
	_noteSequence.clear();
	_diffSequence.clear();
}