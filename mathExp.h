#pragma once
#include <string>
#include <ctype.h>
#include <algorithm>
#include <stack>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <vector>
#include <cmath>
#include <queue>
#define NUM 0
#define OP 1
#define CH 2
#define NF std::string::npos


typedef std::vector<std::string> Exp;

struct node { 
    std::string element; 
    node *left, *right; 
};

void infixExp(node* root);

void postfixExp(node* root);

node* addExpTree(node* root, std::queue<std::string>* elementQueue);

long long toInt(std::string s);

long double eval(node* root);

bool isOperator(std::string element);

bool isOperand(std::string element);

int getPriority(char C);

Exp infixToPostfix(Exp infix);

Exp infixToPrefix(Exp infix);

short getType(char x);

Exp split(std::string perform);

long double evaluate(std::string perform);

