#include "Function.h"

int Function::getReturnValue(){
	return Function::returnValue;
}

void Function::execute(std::map<int, Function*> function){
	inst instruct = Function::instruct; std::string perform;
	while(instruct.size()){
		perform = instruct.front();
		if(perform.find("return") != NF){
			std::string temp;
			perform = perform.substr((int)perform.find("n") + 2, perform.size() - (int)perform.find("n") + 2);
			for(int i = 0; i < perform.size(); ++i)
				if(perform[i] != ' ')
					temp += perform[i];
			perform = temp;
			temp = "";
			std::string x, z; int num;
			for(int i = 0; i < perform.size(); ++i){
				x = perform[i];
				if(getType(perform[i]) == OP || getType(perform[i]) == NUM)
					temp += perform[i];
				else if(getType(perform[i]) == CH){
					if(varPar.find(x) != varPar.end()){
						num = varPar[x];
						while(num){
							z.insert(0, 1, ('0' + (num % 10)));
							num /= 10;
						}
						temp += z;
						z = "";
					}
					else if(varLoc.find(x) != varPar.end()){
						num = varPar[x];
						while(num){
							z.insert(0, 1, ('0' + (num % 10)));
							num /= 10;
						}
						temp += z;
						z = "";
					}
				}				
			}
			perform = temp;
			temp = "";
			bool isNum = 1;
			for(int i = 0; i < perform.size(); ++i)
				if(getType(perform[i]) != NUM){
					isNum = 0;
					break;
				}
			if(isNum){
			//	std::cout << "\nBefore stoi 1 \n" << perform << '\n';
				Function::returnValue = std::stoi(perform);
			}
			else{
				Function::returnValue = evaluate(perform);
			}
		}
		else if(perform.find("int") != NF){
			std::string varName, fName;
			varName = (perform.substr((int)perform.find('t') + 2, (-((int)perform.find('t')) - 3 + ((int)perform.find('=')))));
			varLoc[varName];	
			fName = (perform.substr((int)perform.find('=') + 2, (-((int)perform.find('=')) - 2 + ((int)perform.find('(')))));
			fCall.push(fName);
			for(auto i = function.begin(); i != function.end(); ++i)
				if(i->second->fName == fName){
					std::string var[2];
					int cnt = 0;
					var[0] = (perform.substr((int)perform.find('(') + 1, (-((int)perform.find('(')) - 1 + ((int)perform.find(',')))));
					var[1] = (perform.substr((int)perform.find(',') + 2, (-((int)perform.find(',')) - 2 + ((int)perform.find(')')))));
					if(getType(var[0][0]) != NUM){
						std::string temp = var[0];
						int num = varLoc[temp]; var[0] = "";
						while(num){
							var[0].insert(0, 1, ('0' + (num % 10)));
							num /= 10;
						}
					}
					if(getType(var[1][0]) != NUM){
						std::string temp = var[1];
						int num = varLoc[temp]; var[1] = "";
						while(num){
							var[1].insert(0, 1, ('0' + (num % 10)));
							num /= 10;
						}
					}
					for(auto b = i->second->varPar.begin(); b != i->second->varPar.end(); ++b){
						std::string temp = var[cnt];
					//	std::cout << "\nBefore stoi 2 \n" << temp << '\n';
						b->second = std::stoi(temp);
						cnt++;
					}
					i->second->execute(function);
					Function::varLoc[varName] = i->second->getReturnValue();
					fCall.pop();
					break;
				}
		}
		instruct.pop();
	}
}


