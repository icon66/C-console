#include "Stack.h"

CStack::CStack()
{
	S.base = nullptr;
	S.top = nullptr;
	S.stacksize = 0;
}

CStack::~CStack()
{
	//ÊÍ·ÅÖ¸Õë
	DestroyStack();
}


bool CStack::InitStack(int stack_size)
{
	S.base = new char[stack_size*sizeof(char)];
	if (!S.base)
		return false;
	S.top = S.base;
	S.stacksize = stack_size;
	return true;
}


bool CStack::Push(const char c)
{
	if (S.top - S.base >= S.stacksize)
		return false;
	*S.top++ = c;
	return true;
}

bool CStack::Pop()
{
	if (S.top == S.base)
		return false;
	S.top--;
	return true;
}

void CStack::DestroyStack()
{
	if (S.base)
	{
		delete []S.base;
		S.base = nullptr;
	}
	S.top = nullptr;
}


bool CStack::IsEmpty()
{
	if (S.top == S.base)
		return true;
	return false;
}