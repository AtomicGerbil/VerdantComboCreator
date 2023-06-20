#include "pch.h"

using namespace std;
using json = nlohmann::json;

bool processFile(string& sFile, string& sComboPath);
size_t countOccurrences(const std::string& jsonString, const std::string& key);

int main(int argc, char** argv)
{

	string filePath = "weaponFile.config"; // default init.
	string comboPath = "./combos/";
	char c;

	while ((c = getopt(argc, argv, "w:c:s")) != -1)
	{
		switch (c)
		{
		case 'w':
			filePath = optarg;
			break;

		case 'c':
			comboPath = optarg;
			break;

		case ':':
			cout << "Option needs a value \n";
			break;
		case '?':
			if (optopt == 'c') cout << stderr << "Option -%c requires an argument.\n" << optopt;
			else if (optopt == 'w') cout << stderr << "Option -%w requires an argument.\n" << optopt;
			else if (isprint(optopt)) cout << stderr << "Unknown option.\n" << optopt;
			else cout << stderr << "Unknown option char. \n" << optopt;
			break;

		default:
			abort(); // i fear the day this ever gets hit.
			break;
		}
	}

	if (!processFile(filePath, comboPath))
	{
		cout << endl << "Failed to complete operation." << endl;
		system("Pause");
		return 1;
	}

	return 0;
}

bool processFile(string& fileName, string& comboPath)
{
	ifstream weaponFile(fileName); // input stream to read (main file).#
	if (weaponFile.fail())
		return false; // dies immediately if wrong.

	json jsonWeaponBuffer = json::parse(weaponFile);

	// since i asked and doing things by form order listed in formNames was requested...
	// ... I store these like so.
	vector<string> formOrder = jsonWeaponBuffer["formNames"];
	size_t count = 0;
	size_t numOfForms = formOrder.size();

	while (count < numOfForms)
	{
		string form = formOrder[count];
		// since idx is @ 0, i increment then apply it.
		count++;
		string comboFile = comboPath + "combo" + to_string(count) + ".json";
		ifstream comboBuffer(comboFile);
		if (comboBuffer.fail())
		{
			cout << "Error occurred @ file [" + comboFile + "]; make sure the file conforms to the format (and that it even exists)!" << endl;
			continue; // just move onto next; assumingly, modder fucked up or /i/ fucked greatly.
		}

		
		json jsonComboBuffer = json::parse(comboBuffer);
		// grab reference.
		auto& obj = jsonWeaponBuffer["forms"][form];

		obj["combo"] = jsonComboBuffer;
	}

	ofstream output("output.config");
	if (!output)
	{
		cout << "Failed to create the output file." << endl;
		return 1;
	}
	output << jsonWeaponBuffer.dump();

	cout << "File successfully created!" << endl;
	return true;
}

size_t countOccurrences(const std::string& jsonString, const std::string& key) {
	// this is wrong. it counts `"action" : "combo"` too.
	size_t count = 0;
	size_t pos = jsonString.find("\"" + key + "\"");
	while (pos != std::string::npos) {
		count++;
		pos = jsonString.find("\"" + key + "\"", pos + key.length() + 2);
	}
	return count;
}