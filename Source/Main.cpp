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

	std::string filePath;

	std::string Desktop{ "C:\\Users\\harri\\Desktop" };
	

	std::string dirSearch(std::string inputDir) {

		for (const auto& entry : std::filesystem::directory_iterator(Desktop)){		//https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
			std::cout << entry.path() << std::endl;
		}
		
		return Desktop;
	}

	std::string fileSearch(std::string inputDir) {
		
		std::filesystem::
			//to search for file name in directories; 


	}
	
};

Functions Funcs;
int main() {
	std::string dirInput;
	std::cout << "File Directory..." "\n";
	std::cin >> dirInput;
	Funcs.dirSearch(dirInput);
	
}
