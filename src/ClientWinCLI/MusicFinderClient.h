#pragma once

#include <string>
#include <unordered_map>
#include <string_view>

class MusicFinderClient
{
public:
	enum class InputResult
	{
		VALID,
		INVALID,
		QUIT
	};

private:
	std::unordered_map<std::string, char> _notesToNum = {
		{"A", 0x0},  {"A#", 0x1}, {"B", 0x2}, {"C", 0x3},  {"C#", 0x4}, {"D", 0x5},
		{"D#", 0x6}, {"E", 0x7},  {"F", 0x8}, {"F#", 0x9}, {"G", 0xA},  {"G#", 0xB} };

	const std::string_view _noteChars = std::string_view("ABCDEFG#");

	std::string _noteSequence;
	std::string _diffSequence;
	InputResult _status;

private:
	InputResult _ParseInput(std::string& input);

public:
	void GetInput();
	const std::string& GetNoteSequence() const;
	const std::string& GetDiffSequence() const;
	InputResult GetStatus() const;
	void Reset();
};
