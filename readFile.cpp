#include <iostream>
#include <vector>
#include <string>
#include "colors.h"
#include "readFile.h"
#include <fstream>


File readFile(std::string fileName){
	File file;
	std::ifstream in(fileName);

  	if(!in) {
    	std::cout << BOLDRED << "Cannot open input file.\n" << RESET;
    	return file;
  	}

  	char Line[255];

  	while(in) {
    	in.getline(Line, 255);
    	file.push_back(Line);
  	}
  	in.close();
  	return file;	
}