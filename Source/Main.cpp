#include <iostream>
 #include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <format>





//|/-\|

//first function, enter file name and search directory for the file




class Functions {
private:
protected:
public:
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


	std::string Cut(std::string strToCut) {
		std::size_t Result{ strToCut.find_last_of("\\/") };
		std::string Final{ strToCut.substr(strToCut.find_last_of("/\\") + 1) };
		std::size_t lastIndex{ Final.find_last_of(".") };
		std::string fullName{ Final.substr(0, lastIndex) };
		std::size_t temp{ strToCut.find_last_of("\\/") };
		savedPath = strToCut.substr(0, temp+1);


		return fullName;
	}

	
	void Search(std::string Directory, std::string Name) {


		for (auto& file : std::filesystem::directory_iterator(Directory)) {
			if (file.path().filename() == Name) {
				std::cout << "Found " << file.path() << std::endl;
				std::cout << "Properties|\n" "Size(bytes)" << std::filesystem::file_size(file) << std::endl;
				std::cout << "Last modified" << std::filesystem::last_write_time(file) << std::endl;

				std::filesystem::path Path = file.path();
				std::string Extension = Path.extension().string();
				std::cout << "File type" << Extension << std::endl;

				break;
				 //return file properties
			}
			if (file.is_directory()) {	//concern that the program will direct to the folder, then not exit the folder and look for next. 
			std::cout << "Searching " << file.path() << "..." << std::endl;
			std::cout << file.path() << "Failed" << std::endl;
			Search(file.path().string(), Name);

			}
		}
	}

	void NewDirectory(std::string Prefix, std::string Name) {
		std::string Directory = Prefix + Name;

		if (std::filesystem::exists(Prefix)) {
			std::filesystem::create_directory(Directory);
			return;
		}
		else {
			std::cout << "Specified directory does not exist." << std::endl;
			return;
		}
	}

	void ListContents(std::filesystem::path Directory) {
		


		while (true) {
			for (auto current : std::filesystem::directory_iterator(Directory)) {
				std::string Path = current.path().string();
				std::cout << Cut(Path) << std::endl;
			}
			break;
		}

		
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
		for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(Images)) {
			std::string filePath = entry.path().string();
			std::filesystem::path test = filePath;

			if (std::filesystem::is_regular_file(entry.path()) && filePath.find(exclusionPath.string())) {

				std::cout << filePath << fileSize(filePath) <<  std::endl;
				std::cout << "Name: " << Cut(filePath) << std::endl;	//removes the file name, should remove file path and keep only the name.
				std::cout << "Path: " << savedPath << std::endl;
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

	std::filesystem::path fileRename(std::filesystem::path oldName, std::filesystem::path newName) {		//function causing error at memory location 0x00000029E25FEB00

		std::string oldNamePath = oldName.generic_string();
		std::size_t Remove = oldNamePath.find_last_of("\\/");
		std::string Prefix = oldNamePath.substr(0, Remove);
		filePath = oldNamePath.substr(0, Remove);

		std::cout << "Old name: " << savedPath << std::endl;
		
		std::filesystem::rename(savedPath/oldName, savedPath/newName);

		return newName;
	}
	std::string Rename(std::string inputName) {
		std::string Prefix;
		std::string Suffix = ".jpg";


		std::string savedPathString = savedPath.string();

		std::string newPath = std::format("{}{}{}", savedPathString, inputName, Suffix);
		std::cout << "newPath string: " << newPath << std::endl;

		if (std::filesystem::exists(savedPath)) {
			std::cout << "Renaming..." << std::endl;
			std::filesystem::rename(std::string(savedPathString), std::string(newPath));	//error here //rename arguments must be of type filesystem::path
			std::cout << "Renamed" << std::endl;
		}
		else {
			std::cout << "File path doesn't exist." << std::endl;
		}

		return newPath;
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
	int Instruction{};
	int fileEdit{};
	std::filesystem::path newName;
	std::string Input;
	std::filesystem::path inputPath;
	std::filesystem::path moveTo;
	std::filesystem::path Renamed;

	std::string filepathFound;

	std::filesystem::path dirInput;
	std::string fileName{};
	std::cout << "Menu" << std::endl;
	std::cout << "1| File search.\n" << "2| List contents of directory" << std::endl;
	std::cin >> Instruction;

	//find matching file path to fileToMatch, pass as argument to Funcs.fileRename
	switch (Instruction) {
	case 1:
		std::cout << "Enter the name of the file you are looking for..." << std::endl;
		std::cin >> fileName;
		Funcs.Search("C:\\Users\\harri\\Desktop", fileName);

	case 2:
		std::cout << "Enter directory" << std::endl;
		std::cin >> dirInput;
		Funcs.ListContents(dirInput);


		break;
	default:
		std::cout << "Unrecognised input" << std::endl;
	}



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



}
