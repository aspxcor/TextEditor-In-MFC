#include "stdafx.h"
#include<iostream>  
using namespace std;
struct linkStack {
	char* data;
	linkStack* next;
};
//链栈的初始化  
linkStack* initStack()
{
	linkStack* top = new linkStack;
	top = NULL;
	return top;
}
//判断链栈是否为空  
bool isEmpty(linkStack* stack)
{
	if (NULL == stack)
		return true;
	return false;
}
//链栈入栈  
linkStack* push(linkStack * stack, char* data)
{
	linkStack* node = new linkStack;
	node->data = data;
	node->next = stack;
	stack = node;
	return stack;
}
//链栈出栈  
linkStack* pop(linkStack * stack)
{
	if (stack != NULL)
	{
		//cout<<stack->data;
		stack = stack->next;
	}
	else
		cout << "是空栈!";
	return stack;
}
//链栈的长度  
int getLength(linkStack * stack)
{
	int length = 0;
	if (stack == NULL)
		return 0;
	while (stack != NULL)
	{
		length++;
		stack = stack->next;
	}
	return length;
}
//取出栈顶元素  
char* getTop(linkStack * stack)
{
	char* temp;
	temp = stack->data;
	return temp;
}