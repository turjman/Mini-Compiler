#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <stack>
#include <map>
#include "mathExp.h"

typedef std::queue<std::string> inst;


class Function
{
private:
	int returnValue = -1;
	std::stack<std::string> fCall;
public:
	std::string fName;
	std::map<std::string, int> varPar;
	std::map<std::string, int> varLoc; 
	inst instruct;
	void execute(std::map<int, Function*> function);
	int getReturnValue();
};