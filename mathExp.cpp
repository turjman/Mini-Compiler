#include "mathExp.h"

void infixExp(node* root){
    if(root == NULL)
        return;
    else{
        infixExp(root->left);
        std::cout << (root->element) << ' ';
        infixExp(root->right);
    }
}

void postfixExp(node* root){
    if(root == NULL)
        return;
    else{
        infixExp(root->left);
        infixExp(root->right);
        std::cout << (root->element) << ' ';
    }
}

node* addExpTree(node* root, std::queue<std::string>* elementQueue){
    if(!elementQueue->size())
        return root;
    while(true)
    {
        if(root == NULL){
            root = new node;
            root->element = elementQueue->front();
            root->right = NULL;
            root->left = NULL;
          }
        else{
            if(isOperand(elementQueue->front())){
                elementQueue->pop();
                return root;
            }
            elementQueue->pop();
            root->left = addExpTree(root->left, elementQueue);
            root->right = addExpTree(root->right, elementQueue);
            return root; 
        }
    }              
}
 
// Utility function to return the integer value 
// of a given string 
long long toInt(std::string element)  
{  
    long long num = 0;  
        
      // Check if the integral value is  
      // negative or not 
      // If it  is not negative, generate the number  
      // normally 
      if(element[0] != '-') 
        for (int i=0; i<element.length(); i++)  
            num = num * 10 + ((long long)(element[i]) - 48);  
    // If it is negative, calculate the +ve number 
    // first ignoring the sign and invert the  
    // sign at the end 
      else
        for (int i = 1; i < element.length(); i++)  
        { 
            num = num * 10 + ((long long)(element[i]) - 48);  
            num = num * -1; 
        } 
      
    return num;  
}  
  
// This function receives a node of the syntax tree  
// and recursively evaluates it  
long double eval(node* root)  
{  
    // empty tree  
    if (!root)  
        return 0;  
  
    // leaf node i.e, an integer  
    if (!root->left && !root->right)  
        return toInt(root->element);  
  
    // Evaluate left subtree  
    long double leftValue = eval(root->left);  
  
    // Evaluate right subtree  
    long double rightValue = eval(root->right);  
  
    // Check which operator to apply  
    if (root->element == "+")  
        return leftValue + rightValue;  
  
    if (root->element == "-")  
        return leftValue - rightValue;  
  
    if (root->element == "*")  
        return leftValue * rightValue;  
// There is a problem when preforming a modulus '%' operator on a double number (need to be fixed !)    
    if(root->element == "%")
//        return leftValue % rightValue;
        return 0; // exception has been handled !
    if(root->element == "^")
        return std::pow(leftValue, rightValue);

    return leftValue / rightValue;  
} 

short getType(char x){
	if(x >= '0' && x <= '9')
		return NUM;
	else if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return CH;
	else if(x == '+' || x == '-' || x == '/' || x == '*' || x == '%' || x == '^')
		return OP;
	else
		return -1;
}



bool isOperator(std::string element) 
{ 
     if(element == "+" || element == "-"
        || element == "*" || element == "/"
        || element == "%" || element == "^"
        || element == "(" || element == ")")
     	return true;
     else
     	return false;
} 

bool isOperand(std::string element) 
{ 
    if(!isOperator(element) && element != "(" && element != ")")
     	return true;
    else
        return false;
     
}   

int getPriority(std::string element) 
{ 
    if (element == "-" || element == "+") 
        return 1; 
    else if (element == "*" || element == "/" || element == "%") 
        return 2; 
    else if (element == "^") 
        return 3; 
    return 0; 
} 
  
Exp infixToPostfix(Exp infix) 
{ 
    infix.insert(infix.begin(), "("); infix.push_back(")"); 
    int _Size = infix.size(); 
    std::stack<std::string> elementStack; 
    Exp output; 
  
    for (int i = 0; i <_Size; i++) { 
  
        // If the scanned character is an  
        // operand, add it to output. 
        if (isOperand(infix[i])) 
            output.push_back(infix[i]); 
  
        // If the scanned character is an 
        // ‘(‘, push it to the stack. 
        else if (infix[i] == "(") 
            elementStack.push("("); 
  
        // If the scanned character is an 
        // ‘)’, pop and output from the stack  
        // until an ‘(‘ is encountered. 
        else if (infix[i] == ")") { 
  
            while (elementStack.top() != "(") { 
                output.push_back(elementStack.top()); 
                elementStack.pop(); 
            } 
  
            // Remove '(' from the stack 
            elementStack.pop();  
        } 
  
        // Operator found  
        else { 
              
            if (isOperator(elementStack.top())) { 
                while (getPriority(infix[i]) 
                   <= getPriority(elementStack.top())) { 
                    output.push_back(elementStack.top()); 
                    elementStack.pop(); 
                } 
  
                // Push current Operator on stack 
                elementStack.push(infix[i]); 
            } 
        } 
    } 
    return output; 
} 
  
Exp infixToPrefix(Exp infix) 
{  
    int _Size = infix.size(); 
  
    // Reverse infix 
    std::reverse(infix.begin(), infix.end()); 
  
    // Replace ( with ) and vice versa 
    for (int i = 0; i < _Size; i++) { 
  
        if (infix[i] == "(") { 
            infix[i] = ")"; 
            i++; 
        } 
        else if (infix[i] == ")") { 
            infix[i] = "("; 
            i++; 
        } 
    } 
  
    Exp prefix = infixToPostfix(infix); 
  
    // Reverse postfix 
    std::reverse(prefix.begin(), prefix.end()); 
  
    return prefix; 
} 
  
Exp split(std::string perform){
	Exp Perform;
	std::string temp;
	if(perform[0] == '-'){
		temp += "-";
		perform = perform.substr(1, perform.size() - 1);
	}
	for(int i = 0; i < perform.size(); ++i){
		if(getType(perform[i]) == NUM){
			temp += perform[i];
		}
		else if(getType(perform[i] == OP)){
			Perform.push_back(temp);
			temp.clear();
			temp = perform[i];
			Perform.push_back(temp);
			temp.clear();
            if(i != perform.size() - 1 && perform[i + 1] == '-'){
                temp += "-";
                ++i; 
            }
		}	
	}
	Perform.push_back(temp);
	return Perform;
}

long double evaluate(std::string perform){
	Exp Perform = split(perform);
    Perform = infixToPrefix(Perform);
    node* root = NULL;
    std::queue<std::string>* elementQueue = new (std::queue<std::string>);
    for(int i = 0; i < Perform.size(); ++i){
        std::cout << Perform[i] << ' ';    
        elementQueue->push(Perform[i]);
    }
    std::cout << '\n';
    root = addExpTree(root, elementQueue);
    delete elementQueue;
    elementQueue = NULL;
    infixExp(root);
    std::cout << "\n\n";
    return eval(root);
}



