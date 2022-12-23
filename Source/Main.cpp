#include <iostream>
 #include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>





//|/-\|

//first function, enter file name and search directory for the file




class Functions {
private:
protected:
public:
	std::vector<std::filesystem::path> DrivesResult;
	std::string filePath;
	std::filesystem::path savedPath;
	std::string Output;

	std::string Desktop{ "C:\\Users\\harri\\Desktop" };
	std::filesystem::path rootC{ "C:\\Users" };
	std::filesystem::path rootD{ "D:" };
	std::filesystem::path exclusionPath =  rootC / "Windows" ;
	std::string Images = "C:\\Users\\harri\\Desktop\\Images";

	bool fileFound = false;


	std::string Cut(std::string strToCut) {
		std::size_t Result = strToCut.find_last_of("\\/");
		std::string Final = strToCut.substr(strToCut.find_last_of("/\\") + 1);
		std::size_t lastIndex = Final.find_last_of(".");
		std::string fullName = Final.substr(0, lastIndex);
		std::size_t temp = strToCut.find_last_of("\\/");
		savedPath = strToCut.substr(0, temp);

		return fullName;
	}

	std::string dirSearch(std::string inputDir) {
		std::cout << "Searching... " <<  inputDir << std::endl;
		for(const auto& entry : std::filesystem::directory_iterator(Desktop)){		//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
			std::cout << entry.path() << std::endl;
		}
		//add functionality to change properties of file specified by string input, removing file directory prefix from path to match string
		return Desktop;
	}

	std::string fileSearch(std::filesystem::path fileToMatch) {
		std::string test = "C:x64\Debug\FileManager.vcxproj.FileListAbsolute.txt";

		//for (const auto& entry : std::filesystem::directory_iterator(inputFile)) {
		//	std::cout < entry.path() << std::endl;
		//	for()
		//}
		for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(Images)) {
			std::string filePath = entry.path().string();
			std::filesystem::path test = filePath;

			if (std::filesystem::is_regular_file(entry.path()) && filePath.find(exclusionPath.string())) {

				std::cout << filePath << fileSize(filePath) <<  std::endl;
				std::cout << Cut(filePath) << std::endl;	//removes the file name, should remove file path and keep only the name.
				std::cout << "path: " << savedPath;
				//std::cout << test.substr(0, test.find_last_of("\\/")) << std::endl;
				//std::cout << test.remove_filename() << std::endl;


				if (Cut(filePath) == fileToMatch) {
					//remove directory prefix
					fileFound = true;
					std::cout << fileToMatch << " found" << std::endl;
				}
			}

		}

		if(fileFound == false) {
			std::cout << "File not found" << std::endl;
		}
//		for (const auto& entry : std::filesystem::directory_iterator("C:\\")) {
//			DrivesResult.push_back(entry.path());
//			for (int i = 0; i < sizeof(DrivesResult); i++) {
//				//run input against results
//				//add fail check for no file found
//				if (DrivesResult[i] == inputFile) {
//					std::cout << std::filesystem::directory_iterator(DrivesResult[i]);
//				}
//
//			}
//		}



			//to search for file name in directories; take filename input and check against existing file names in directories

		return filePath;
	}

	std::string fileRename(std::filesystem::path oldName, std::filesystem::path newName) {		//maybe change two parameters back to std::string

		std::size_t Remove = oldName.find_last_of("\\/");
		std::string Prefix = oldName.substr(0, Remove);
		filePath = oldName.substr(0, Remove);
		
		std::filesystem::rename(savedPath/oldName, savedPath/newName);



		return newName;
	}

	void moveFile(std::filesystem::path filePath, std::string oldDir, std::string newDir) {		//seperating each directory into substrings per path directory. can be used for renaming each directory for moving a file
		//can be done using std::filesystem::rename, by renaming the filepath.  
		std::string subDir1;
		std::string subDir2;
		std::string subDir3;
		
		std::vector <std::string> subDirs;
		std::vector <std::size_t> found;
		//std::vector <std::size_t> found = oldDir.find("\\");
		while (oldDir.find("\\")) {
			found.push_back(oldDir.find("\\"));
		}
		for (int i{ 0 }; i < sizeof(found); i++) {
			subDirs[i] = oldDir.substr(found[i], found[i+2] - found[i]);	//wrong, subDirs[i] should be the substring between found places.
		}


		std::filesystem::rename(oldDir, newDir);




	}

	int fileSize(std::filesystem::path path) {
		std::cout << "        Size: " <<  std::filesystem::file_size(path) << std::endl;
		return std::filesystem::file_size(path);
	}

	
};

Functions Funcs;
int main() {
	int fileEdit{};
	std::filesystem::path newName;
	std::string Input;
	std::filesystem::path inputPath;
	std::filesystem::path moveTo;

	std::string dirInput;
	std::cout << "File Directory..." "\n";
	std::cin >> dirInput;
	Funcs.dirSearch(dirInput);
	
	std::string filePath;
	std::string fileToMatch;
	std::cout << "File name to search for: " << std::endl;
	std::cin >> fileToMatch;
	Funcs.fileSearch(fileToMatch);
	if (Funcs.fileFound == true) {
		std::cout << "Enter an interrelating number for a function from the list below:\n" "1. Rename\n";
		std::cin >> fileEdit;
	}


	
	//find matching file path to fileToMatch, pass as argument to Funcs.fileRename

	switch (fileEdit) {
	case 1: 
		std::cout << "Enter new file name..." << std::endl;		//remove
		//Funcs.savedPath = "C:\\Users\\harri\\Desktop\\Images\\";
		std::cin >> Input;			//remove

		newName = Funcs.savedPath / Input;						//move to Funcs.fileRename 
		Funcs.fileRename(Funcs.savedPath, newName); 
		std::cout << "New file name: " << newName;
		break;

	case 2:
		std::cout << "Enter path of directory you would like to move the chosen file to" << std::endl;
		std::cin >> moveTo;
		//Funcs.moveFile();
		break;
	default:
		std::cout << "Unrecognised input" << std::endl;
	}



}
