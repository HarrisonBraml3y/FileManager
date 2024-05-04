#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <format>
#include <conio.h>


#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13


class Explore {
private:
	std::vector<std::filesystem::path> DrivesResult;
	std::string filePath;
	std::filesystem::path savedPath{ "C:\\Users\\harri\\Desktop\\Images\\preview" };	//should be the path of the file found with matching name
	std::string Output;

	std::string Desktop{ "C:\\Users\\harri\\Desktop" };
	std::filesystem::path rootC{ "C:\\Users" };
	std::filesystem::path rootD{ "D:" };
	std::filesystem::path exclusionPath{ rootC / "Windows" };
	std::string Images{ "C:\\Users\\harri\\Desktop\\Images" };
	bool fileFound{ false };

	std::filesystem::path CurrentPath = std::filesystem::current_path();

protected:
public:

	std::string Cut(std::string strToCut);
	void OpenFile(std::filesystem::path Directory);
	void DeleteFile(std::filesystem::directory_entry Directory);
	void Search(const std::filesystem::path& Directory, std::string& Name);
	void NewDirectory(std::string Prefix, std::string Name);
	void ListContents(std::filesystem::path Directory);
	std::string dirSearch(std::string inputDir);
	std::string fileSearch(std::filesystem::path fileToMatch);
	std::filesystem::path fileRename(std::filesystem::path oldName, std::string newName);
	std::string Rename(std::string inputName);
	void moveFile(std::filesystem::path filePath, std::string oldDir, std::string newDir);
	int fileSize(std::filesystem::path path);





};