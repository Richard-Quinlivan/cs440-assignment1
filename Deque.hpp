#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define Deque_DEFINE(t)														\
// struct Deque_##t															\
// {																			\
// 																			\
// 																			\
// 																			\
// };																			\
// 																			\
// struct Iterator_##t															\
// {																			\
// 																			\
// 																			\
// 																			\
// };																			\

typedef struct Deque_int
{
	int * data;
	size_t usedLength;
	size_t length;
	char type_name [strlen("Deque_int") + 1] = "Deque_int";
	int frontIndex;
	int backIndex;
	bool (*equal)(const int &, const int &);
	bool (*empty)(struct Deque_int *dp);
	size_t (*size)(struct Deque_int *dp);
	int (*at)(struct Deque_int *dp, int i);
	void (*push_back)(struct Deque_int * dp, int val);
	void (*push_front)(struct Deque_int * dp, int val);
	void (*resize)(struct Deque_int *dp, size_t oldLength);
	int& (*front)(struct Deque_int *dp);
	int& (*end)(struct Deque_int *dp);

} Deque_int;

bool Deque_int_empty(Deque_int *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_int_size(Deque_int *dp)
{
	return dp->usedLength;
}

int Deque_int_at(Deque_int *dp, int i)
{
	assert(i < dp->length && i >= 0);
	return dp->data[i];
}

void Deque_int_push_back(Deque_int *dp, int val)
{
	if(dp->usedLength >= dp->length)
	{
		dp->resize(dp, dp->length);
	}
	dp->data[dp->usedLength] = val;
	dp->usedLength++;
	dp->backIndex++;
}

void Deque_int_push_front(Deque_int *dp, int val)
{
	if(dp->usedLength >= dp->length)
	{
		dp->resize(dp, dp->length);
	}
	dp->data[dp->usedLength] = val;
	dp->usedLength++;
	dp->frontIndex--;
}

void Deque_int_resize(Deque_int *dp, size_t oldLength)
{
	int * newData = (int *) malloc(sizeof(int *) * oldLength * 2);

	for (int i = 0; i < dp->length; i++)
	{
		newData[i] = dp->data[i];
	}
	free(dp->data);
	dp->data = newData;
	dp->length = oldLength * 2;
}

int& Deque_int_front(Deque_int *dp)
{
	return dp->data[dp->frontIndex];
}

int& Deque_int_back(Deque_int *dp)
{
	return dp->data[dp->backIndex];
}


void Deque_int_ctor(Deque_int *dp, bool (*compare)(const int &, const int &))
{
	dp->equal = compare;
	dp->data = (int *) malloc(sizeof(int *)* 10);
	dp->length = 10;
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 0;
	dp->empty = &Deque_int_empty;
	dp->size = &Deque_int_size;
	dp->at = &Deque_int_at;
	dp->push_back = &Deque_int_push_back;
	dp->resize = &Deque_int_resize;
	dp->front = &Deque_int_front;
	dp->end =  &Deque_int_back;
}

typedef struct Iterator_int
{



} Iterator_int;

struct MyClass {
	int id;
	char name[10];
};

typedef struct Deque_MyClass
{
	struct MyClass * data;
	size_t usedLength;
	size_t length;
	int frontIndex;
	int backIndex;
	char type_name [strlen("Deque_MyClass") + 1] = "Deque_MyClass";
	bool (*equal)(const struct MyClass &, const struct MyClass &);
	bool (*empty)(struct Deque_MyClass *dp);
	size_t (*size)(struct Deque_MyClass *dp);
	struct MyClass (*at)(struct Deque_MyClass *dp, int i);
	void (*push_back)(struct Deque_MyClass * dp, struct MyClass val);
	void (*push_front)(struct Deque_MyClass * dp, struct MyClass val);
	void (*resize)(struct Deque_MyClass *dp, size_t oldLength);
	MyClass& (*front)(struct Deque_MyClass *dp);
	MyClass& (*back)(struct Deque_MyClass *dp);

} Deque_MyClass;

bool Deque_MyClass_empty(Deque_MyClass *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_MyClass_size(Deque_MyClass *dp)
{
	return dp->usedLength;
}

struct MyClass Deque_MyClass_at(Deque_MyClass *dp, int i)
{
	assert(i < dp->length && i >= 0);
	return dp->data[i];
}

void Deque_MyClass_push_back(Deque_MyClass *dp, struct MyClass val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		if(dp->usedLength == dp->length) //the deque is full
		{
			dp->resize(dp, dp->length);
		}
		else if(dp->usedLength == 0) //the deque is empty
		{
			dp->backIndex--; //this will offset the increment so they both point to the only element still
		}
	}
	dp->backIndex++;
	if(dp->backIndex >= dp->length)
	{
		dp->backIndex = 0;
	}
	dp->usedLength++;

	dp->data[dp->backIndex] = val;
}

void Deque_MyClass_push_front(Deque_MyClass *dp, MyClass val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		if(dp->usedLength == dp->length) //the deque is full
		{
			dp->resize(dp, dp->length);
		}
		else if(dp->usedLength == 0)
		{
			dp->frontIndex++; //this will offset the increment so they both point to the only element still
		}
	}
	dp->frontIndex--;
	if(dp->frontIndex < 0)
	{
		dp->frontIndex = dp->length - 1;
	}
	dp->usedLength++;

	dp->data[dp->frontIndex] = val;

}

void Deque_MyClass_resize(Deque_MyClass *dp, size_t oldLength)
{
	struct MyClass * newData = (struct MyClass *) malloc(sizeof(struct MyClass *) * oldLength * 2);

	for (int i = 0; i < dp->length; i++)
	{
		newData[i] = dp->data[i];
	}
	free(dp->data);
	dp->data = newData;
	dp->length = oldLength * 2;
}

MyClass& Deque_MyClass_front(Deque_MyClass *dp)
{
	return dp->data[dp->frontIndex];
}

MyClass& Deque_MyClass_back(Deque_MyClass *dp)
{
	return dp->data[dp->backIndex];
}

void Deque_MyClass_ctor(Deque_MyClass *dp, bool (*compare)(const struct MyClass &, const struct MyClass &))
{
	dp->equal = compare;
	dp->data = (struct MyClass *) malloc(sizeof(struct MyClass *) * 10);
	dp->length = 10;
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 0;
	dp->empty = &Deque_MyClass_empty;
	dp->size = &Deque_MyClass_size;
	dp->at = &Deque_MyClass_at;
	dp->push_back = &Deque_MyClass_push_back;
	dp->push_front = &Deque_MyClass_push_front;
	dp->resize = &Deque_MyClass_resize;
	dp->front = &Deque_MyClass_front;
	dp->back =  &Deque_MyClass_back;
}

typedef struct Iterator_MyClass
{



} Iterator_MyClass;


#endif
