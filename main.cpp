#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "mathExp.h"
#include "colors.h"
#include "readFile.h"
#include "Function.h"
#define NF std::string::npos

int main(int argc, char const *argv[])
{
	system("CLS");
	Function* temp;
	int index = 0;
	std::map<int, Function*> function;
	File file;
	if(argc > 1)
	file = readFile(argv[1]);
	else
	return 0;
	for(int i = 0; i < file.size(); ++i){
		if(file[i].size()){
			if(file[i].find('{') == NF && file[i].find('}') != NF) // skip empty lines
				continue;
			else if(file[i].find("int") != NF && file[i].find(')') != NF && file[i].find('=') == NF){ // when function
					temp = new Function; // i will delete pointers later ;)
					temp->fName = file[i].substr(4, (int)file[i].find('(') - 4);
					if(file[i].find("int", 5) != NF){ // when a function has arguments 
						std::string varName;
						varName = (file[i].substr((int)file[i].find('(') + 5, (-((int)file[i].find('(')) - 5 + ((int)file[i].find(',')))));
						temp->varPar[varName];
						varName = (file[i].substr((int)file[i].find(',') + 6, (-((int)file[i].find(',')) - 6 + ((int)file[i].find(')')))));
						temp->varPar[varName]; ++i;
						while(file[i].find('}') == NF){
							if(file[i].find("return") != NF){
								temp->instruct.push(file[i].substr((int)file[i].find("return"), (int)file[i].find(';') - (int)file[i].find("return")));
							}
							else if(file[i].find("int") != NF){
								temp->instruct.push(file[i].substr((int)file[i].find("int"), (int)file[i].find(';') - (int)file[i].find("int")));
							}
							++i;
						}
					}
					else{ // when function does not have arguments like main()
						++i;
						while(file[i].find('}') == NF){
							if(file[i].find("return") != NF){
								temp->instruct.push(file[i].substr((int)file[i].find("return"), (int)file[i].find(';') - (int)file[i].find("return")));
							}
							else if(file[i].find("int") != NF){
								temp->instruct.push(file[i].substr((int)file[i].find("int"), (int)file[i].find(';') - (int)file[i].find("int")));
							}
							++i;
						}
					}
					function[index] = temp;
					++index;
			}
		}
	}

	function[4]->execute(function); 
	for(auto i = function[4]->varLoc.begin(); i != function[4]->varLoc.end(); ++i){
		std::cout << i->first << ' ' << i->second << '\n';
	}
	std::cout  << BOLDGREEN << "\n\nDisplay all file data simplified :D\n\n\n";
	// display all file data siplified :D
	for(auto i = function.begin(); i != function.end(); ++i){
		std::cout << i->second->fName << '\n';
		for(auto b = i->second->varPar.begin(); b != i->second->varPar.end(); ++b){
			std::cout << b->first << '\n';
		}
		while(i->second->instruct.size()){
			std::cout << i->second->instruct.front() << '\n';
			i->second->instruct.pop();
		}
	}
	std::cout << RESET << "\n\n";
	// I do clean pointers :) no memory leak any more :D
	for(auto i = function.begin(); i != function.end(); ++i){
		delete i->second;
		i->second = NULL;
	}
	return 0;
}