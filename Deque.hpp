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

typedef struct Deque
{
	int ** data;
	size_t length;
	size_t (*size)(struct Deque *dp);
	bool (*empty)(struct Deque *dp);
	int (*at)(struct Deque *dp, int i);


} Deque;

char[] Deque_type_name(struct Deque *dp)
{
	int length = 7 + strlen("int"); //strlen(#t) //should get the string version of the type name for the macro version
}

bool Deque_empty(struct Deque *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_int_size(struct Deque *dp)
{
	return dp->length;
}

int Deque_int_at(struct Deque *dp, int i)
{
	assert(i < dp->length && i >= 0);
	return dp->data[i];
}

typedef struct Iterator
{



} Iterator;




#endif
