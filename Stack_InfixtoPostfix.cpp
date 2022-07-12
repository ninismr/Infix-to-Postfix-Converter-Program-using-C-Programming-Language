//C++ Program to Convert Infix to Postfix/Suffix Expression using Stack

#include<iostream>
#include<stack>
using namespace std;

//FUNCTION isOperator(char c)
bool isOperator(char c)
{
    if (c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//FUNCTION precedence(char c)
int precedence(char c)
{
    if (c == '^')
    return 3;
    else if (c == '*' || c == '/')
    return 2;
    else if (c == '+' || c == '-')
    return 1;
    else
    return -1;
}

//FUNCTION InfixToPostfix(stack, infix)
string InfixToPostfix(stack<char> s, string infix)
{
    //STRING postfix
    string postfix;
    
    //LOOP i=0 to i<infix.length
    for (int i=0;i<infix.length();i++)
    {
        //1. IF infix[i] -> OPERAND then postfix+=infix[i]
        if ((infix[i] >= 'a' && infix[i] <= 'z')
        || (infix[i] >= 'A' && infix[i] <= 'Z')
        || (infix[i] >= '0' && infix[i] <= '9'))
        {
            postfix+=infix[i];
        }
        
        //2. ELSE IF infix[i] -> '(' then PUSH to stack
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        
        //3. ELSE IF infix[i] -> ')' then POP & PRINT stack
        //till stack gets empty OR '(' is found 
        //and IF stack.top == '(' then POP or discard the '('
        else if (infix[i] == ')')
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                char temp=s.top();
                postfix+=temp;
                s.pop();
            }
            if (s.top() == '(')
            {
                s.pop();
            }
        }
        
        //4. ELSE IF infix[i] -> OPERATOR(+, -, *, /, ^)
        else if (isOperator(infix[i]))
        {
            //4.1. IF stack -> EMPTY then PUSH infix[i] on stack
            if (s.empty())
            {
                s.push(infix[i]);
            }
            
            //4.2. ELSE IF stack -> NOT EMPTY
            else
            {
                //4.2.1. IF precedence(infix[i]) > precedence(stack.top)
                //then -> PUSH infix[i] on stack
                if (precedence(infix[i]) > precedence(s.top()))
                {
                    s.push(infix[i]);
                }

                //4.2.2. ELSE IF (precedence(infix[i]) == precedence(stack.top)
                //&& (infix[i] == '^'))
                //then -> PUSH infix[i] on stack
                else if ((precedence(infix[i]) == precedence(s.top())) 
                && (infix[i] == '^'))
                {
                    s.push(infix[i]);
                }

                //4.2.3. ELSE
                else
                {
                    //4.2.3.1. WHILE stack -> (NOT EMPTY)
                    //&& precedence(infix[i] <= precedence(stack.top))
                    //then POP and PRINT stack
                    while ((!s.empty()) && (precedence(infix[i]) <= precedence(s.top())))
                    {
                        postfix+=s.top();
                        s.pop();
                    }

                    //4.2.3.2 PUSH current OPERATOR on stack
                    s.push(infix[i]);
                }
            }
        }
    }

    //POP & PRINT remaining OPERATORS in the stack
    while (!s.empty())
    {
        postfix+=s.top();
        s.pop();
    }

    return postfix;
}

int main()
{
    string infix_exp, postfix_exp, choice;
    cout<<endl<<"Please do not use space between the operand and/or operator!"<<endl;
    cout<<"Input example: A+B*C"<<endl;
    cout<<endl<<"Enter the Infix Expression: ";
    cin>>infix_exp;
    stack <char> stack;
    postfix_exp = InfixToPostfix(stack, infix_exp);
    cout<<"The Postfix Expression is: "<<postfix_exp<<endl;
    cout<<endl<<"Do you want to try another Infix Expression? (y/n): ";
    cin>>choice;
    if (choice == "Y" || choice == "y") {
        main();
    }
    else if (choice == "N" || choice == "n") {
        exit(0);
    }
    return 0;
}