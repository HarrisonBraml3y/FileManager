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

	std::string dirSearch(std::string inputDir) {

		std::cout << inputDir << std::endl;
		for (const auto& entry : std::filesystem::directory_iterator(Desktop)){		//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
			std::cout << entry.path() << std::endl;
		}
		//add functionality to change properties of file specified by string input, removing file directory prefix from path to match string
		return Desktop;
	}

	std::string fileSearch(std::string inputFile, std::string fileToMatch) {
		//for (const auto& entry : std::filesystem::directory_iterator(inputFile)) {
		//	std::cout < entry.path() << std::endl;
		//	for()
		//}
		for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(rootC)) {
			inputFile = entry.path().string();
			if (std::filesystem::is_regular_file(entry.path()) && inputFile.find(exclusionPath.string())) {
				std::cout << inputFile << std::endl;	//https://stackoverflow.com/questions/68460077/get-all-file-recursively-from-c
				if (inputFile == fileToMatch) {
					std::cout << fileToMatch << " found" << std::endl;
				}
			}
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
	std::cout << "File name: " << std::endl;
	std::cin >> filePath;
	Funcs.fileSearch(filePath);

}
