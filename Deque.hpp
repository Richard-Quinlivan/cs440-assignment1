#ifndef DEQUE_H
#define DEQUE_H


#define Deque_DEFINE(t)																	\
struct Deque_##t																		\
{																						\
																						\
																						\
																						\
}																						\
																						\
struct Iterator_##t																		\
{																						\
																						\
																						\
																						\
}																						\

typedef struct Deque 
{
	int ** data;
	size_t size;
	size_t &(*size)(struct Deque *dp);
	int &(*at)(struct Deque *dp, int i);


} Deque;

size_t Deque_int_size(struct Deque *dp)
{
	return dp->size;
}

int Array_int_at(struct Deque *dp, int i) 
{
	assert(i < size);
	return ap->data[i];
} 

typedef struct Iterator 
{



} Iterator;




#endif
