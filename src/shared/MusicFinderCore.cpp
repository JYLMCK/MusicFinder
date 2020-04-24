#include <vector>
#include <sstream>
#include <unordered_map>

#include "MusicFinderCore.h"

std::optional<std::pair<std::string, std::string>> ParseInput(const std::string& input)
{
	static std::unordered_map<std::string, char> notesToNum = {
	    {"A", 0x0}, {"A#", 0x1}, {"B", 0x2}, {"C", 0x3}, {"C#", 0x4}, {"D", 0x5}, {"D#", 0x6}, {"E", 0x7}, {"F", 0x8}, {"F#", 0x9}, {"G", 0xA}, {"G#", 0xB}};

	const std::string_view noteChars = std::string_view("ABCDEFG#");

	if (input.empty())
		return {};

	std::stringstream ss;

	const static auto IsNoteChar = [&](char c) {
		return noteChars.find(c) != std::string_view::npos;
	};
	const static auto IsValidChar = [&](char c) {
		return IsNoteChar(c) || (c == ',') || (c == ' ');
	};

	bool isSharpPossible = false;
	for (const char& c : input)
	{
		if (!IsValidChar(c))
			return {};

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
					return {};
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
	// make diffSequence here as well
	std::string str;
	std::stringstream tidyInput;
	std::vector<char> vNotesNum;
	while (ss >> str)
	{
		if (str == "E#")
		{
			tidyInput << "F ";
			vNotesNum.emplace_back(notesToNum["F"]);
		}
		else if (str == "B#")
		{
			tidyInput << "C ";
			vNotesNum.emplace_back(notesToNum["C"]);
		}
		else
		{
			tidyInput << str << ' ';
			vNotesNum.emplace_back(notesToNum[str]);
		}
	}

	std::string noteSequence = tidyInput.str();
	std::string diffSequence;
	char diff;
	for (std::size_t i = 0; i < vNotesNum.size() - 1; ++i)
	{
		diff = std::abs(vNotesNum[i] - vNotesNum[i + 1]);
		if (diff > 6)
			diff = 12 - diff;
		diffSequence.push_back(diff + '0');
	}

	return std::pair(noteSequence, diffSequence);
}