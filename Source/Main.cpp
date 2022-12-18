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
	std::string Output;

	std::string Desktop{ "C:\\Users\\harri\\Desktop" };
	std::filesystem::path rootC{ "C:" }; 
	std::filesystem::path exclusionPath =  rootC / "Windows" ;

	std::string Cut(std::string strToCut) {
		std::size_t Result = strToCut.find_last_of("/\\");


		std::string Final = Result;
		return strToCut.substr(0, Result);




	}

	std::string dirSearch(std::string inputDir) {
		std::cout << "Searching... " <<  inputDir << std::endl;
		for(const auto& entry : std::filesystem::directory_iterator(Desktop)){		//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
			std::cout << entry.path() << std::endl;
		}
		//add functionality to change properties of file specified by string input, removing file directory prefix from path to match string
		return Desktop;
	}

	std::string fileSearch(std::string fileToMatch) {
		std::string test = "C:x64\Debug\FileManager.vcxproj.FileListAbsolute.txt";
		bool fileFound = false;
		//for (const auto& entry : std::filesystem::directory_iterator(inputFile)) {
		//	std::cout < entry.path() << std::endl;
		//	for()
		//}
		for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(rootC)) {
			std::string filePath = entry.path().string();
			std::filesystem::path test = filePath;
			if (std::filesystem::is_regular_file(entry.path()) && filePath.find(exclusionPath.string())) {

				std::cout << Cut(filePath) << std::endl;	//removes the file name, should remove file path and keep only the name.
				//std::cout << filePath << std::endl;
				//std::cout << test.substr(0, test.find_last_of("\\/")) << std::endl;
				//std::cout << test.remove_filename() << std::endl;

				if (filePath == fileToMatch) {
					//remove directory prefix
					fileFound = true;
					std::cout << fileToMatch << " found" << std::endl;
				}
				else {
					fileFound = false;
				}
			}

		}

		if (fileFound == false) {
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
	
};

Functions Funcs;
int main() {
	std::string dirInput;
	std::cout << "File Directory..." "\n";
	std::cin >> dirInput;
	Funcs.dirSearch(dirInput);
	
	std::string filePath;
	std::string fileToMatch;
	std::cout << "File name to search for: " << std::endl;
	std::cin >> fileToMatch;
	Funcs.fileSearch(fileToMatch);

}
