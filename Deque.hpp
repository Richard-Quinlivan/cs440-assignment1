#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>
#include <string.h>


#define Deque_DEFINE(t)														\
struct Deque_##t															\
{																			\
																			\
																			\
																			\
};																			\
																			\
struct Iterator_##t															\
{																			\
																			\
																			\
																			\
};																			\

typedef struct Deque_int
{
	int * data;
	size_t usedLength;
	size_t length;
	char * type_name;
	bool (*equal)(const int &, const int &)
	bool (*empty)(struct Deque_int *dp);
	size_t (*size)(struct Deque_int *dp);
	int (*at)(struct Deque_int *dp, int i);
	void (*push_back)(struct Deque_int * dp, int val)

} Deque_int;
void Deque_int_ctor(struct Deque_int *dp, bool 	(*compare)(const int &, const int &))
{
	dp->equal = compare;
	dp->data = (int *) malloc(sizeof((int *) * 10);
	dp->length = 10;
	dp->usedLength = 0;

	int nameLength = 7 + strlen("int"); //strlen(#t) //should get the string version of the type name for the macro version
	dp->type_name = (char *) malloc(sizeof(char * nameLength));
}

bool Deque_int_empty(struct Deque_int *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_int_size(struct Deque_int *dp)
{
	return dp->length;
}

int Deque_int_at(struct Deque_int *dp, int i)
{
	assert(i < dp->length && i >= 0);
	return dp->data[i];
}

void Deque_int_push_back(struct Deque_int *dp, int val)
{
	if(dp->usedLength >= dp->length)
	{
		dp->Deque_int_resize(dp, dp->length);
	}
	dp->data[usedLength] = val;
	usedLength++;
}

void Deque_int_resize(struct Deque_int *dp, int oldLength)
{
	int * newData = (int *) malloc(sizeof((int *) * oldLength * 2);

	for (int i = 0; i < dp->length; i++)
	{
		newData[i] = dp->data[i];
	}
	free(dp->data);
	dp->data = newData;
	dp->length = oldLength * 2;

}

typedef struct Iterator_int
{



} Iterator_int;




#endif
