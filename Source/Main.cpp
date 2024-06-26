#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <format>
#include <conio.h>

#include "Filetransfer/FileExplore.h"
#include "FileTransfer/Client.h"


#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

std::filesystem::path FileToSend = "C:\\Users\\harri\\Desktop\\ToSend.txt";
const char* File = "C:\\Users\\harri\\Desktop\\Images\\previewpreview.jpg";
std::string Destination = "C:\\Users\\harri\\Desktop\\Destination";

Explore Funcs;

int __cdecl main(int argc, char** argv) {
	int Instruction{};

	std::cout << "argc " << argc << std::endl;
	if (argc != 3) {
		printf("usage: %s server-name file-path\n", argv[0]);
		return 1;
	}
	const char* serverAddress = argv[1];
	const char* filePath = argv[2];

	if (SendFile(serverAddress, File)) {
		printf("File sent successfully.\n");
	}
	else {
		printf("Failed to send file.\n");
	}
	//SendFile(Destination, FileToSend);


//
//	std::filesystem::path dirInput;
//	std::string fileName{};
//	std::cout << "Menu" << std::endl;
//	std::cout << "1| File search.\n" << "2| List contents of directory" << std::endl;
//	std::cin >> Instruction;
//
//	//find matching file path to fileToMatch, pass as argument to Funcs.fileRename
//	switch (Instruction) {
//	case 1:
//		std::cout << "Enter the name of the file you are looking for..." << std::endl;
//		std::cin >> fileName;
//		Funcs.Search("C:\\Users\\harri\\Desktop", fileName);
//
//		break;
//	case 2:
//		std::cout << "Enter directory" << std::endl;
//		std::cin >> dirInput;
//		Funcs.ListContents(dirInput);
//
//
//		break;
//	default:
//		std::cout << "Unrecognised input" << std::endl;
//	}
//


//	switch (fileEdit) {
//	case 1: 
//		std::cout << "Enter new file name..." << std::endl;		//remove
//		//Funcs.savedPath = "C:\\Users\\harri\\Desktop\\Images\\";
//		std::cin >> Input;			//remove
//
//		//newName = Funcs.savedPath / Input;	//move to Funcs.fileRename 
//		Renamed = Funcs.Rename(Input);
//		//Funcs.fileRename(Funcs.savedPath, Input); 
//		std::cout << "New file name: " << Renamed << std::endl;
//		break;
//
//	case 2:
//		std::cout << "Enter path of directory you would like to move the chosen file to" << std::endl;
//		std::cin >> moveTo;
//		//Funcs.moveFile(); 
//		break;
//	default:
//		std::cout << "Unrecognised input" << std::endl;
//	}


	return 0;
}
