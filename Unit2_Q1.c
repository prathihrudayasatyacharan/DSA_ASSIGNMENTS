#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }

    stack[++top] = ch;
}

char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

int precedence(char ch)
{
    switch (ch)
    {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;

        default:
            return 0;
    }
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, k = 0;
    char ch;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (ch == ' ' || ch == '\t')
            continue;

        
        if (isalnum(ch))
        {
            postfix[k++] = ch;
        }

        /* Opening parenthesis */
        else if (ch == '(')
        {
            push(ch);
        }

        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();

            if (top != -1 && peek() == '(')
                pop();
        }

        
        else if (isOperator(ch))
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
               
                if (ch == '^' && peek() == '^')
                    break;

                postfix[k++] = pop();
            }

            push(ch);
        }
    }

    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
