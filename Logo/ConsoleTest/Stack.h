#pragma once
struct Stack
{
	char *base;    	
	char *top;
	int stacksize;
};

class CStack  
{
private:
	Stack S;
public:
	CStack();
	virtual ~CStack();
public:
	bool InitStack(int size);
	bool Push(const char c);		
	bool Pop();	
	void DestroyStack();
	bool IsEmpty();
};


