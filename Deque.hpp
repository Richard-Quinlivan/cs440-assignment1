#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
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
*/
struct MyClass {
	int id;
	char name[10];
};


struct Deque_MyClass_Iterator;

typedef struct Deque_MyClass
{
	struct MyClass * data;
	size_t usedLength;
	size_t length;
	int frontIndex;
	int backIndex;
	char type_name [strlen("Deque_MyClass") + 1] = "Deque_MyClass";
	bool (*compare)(const struct MyClass &, const struct MyClass &);
	bool (*empty)(struct Deque_MyClass *dp);
	size_t (*size)(struct Deque_MyClass *dp);
	struct MyClass& (*at)(struct Deque_MyClass *dp, int i);
	void (*push_back)(struct Deque_MyClass * dp, struct MyClass val);
	void (*push_front)(struct Deque_MyClass * dp, struct MyClass val);
	void (*pop_front)(struct Deque_MyClass * dp);
	void (*pop_back)(struct Deque_MyClass * dp);
	void (*resize)(struct Deque_MyClass *dp, size_t oldLength);
	void (*sort)(struct Deque_MyClass * dp, Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2);
	void (*clear)(struct Deque_MyClass * dp);
	struct MyClass& (*front)(struct Deque_MyClass *dp);
	struct MyClass& (*back)(struct Deque_MyClass *dp);
	Deque_MyClass_Iterator (*begin)(struct Deque_MyClass *dp);
	Deque_MyClass_Iterator (*end)(struct Deque_MyClass *dp);
	void (*dtor)(struct Deque_MyClass * dp);

} Deque_MyClass;

void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator *it, Deque_MyClass *dp, int index);

typedef struct Deque_MyClass_Iterator
{
	int index;
	Deque_MyClass * deque;
	struct MyClass& (*deref)(struct Deque_MyClass_Iterator *it);
	void (*inc)(struct Deque_MyClass_Iterator *it);
	void (*dec)(struct Deque_MyClass_Iterator *it);

} Deque_MyClass_Iterator;


bool Deque_MyClass_empty(Deque_MyClass *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_MyClass_size(Deque_MyClass *dp)
{
	return dp->usedLength;
}

struct MyClass& Deque_MyClass_at(Deque_MyClass *dp, int i)
{
	return dp->data[(dp->frontIndex+1 + i) % dp->length];
}

void Deque_MyClass_push_back(Deque_MyClass *dp, struct MyClass val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		if(dp->usedLength == dp->length) //the deque is full
		{
			dp->resize(dp, dp->length);
		}
		// else if(dp->usedLength == 0) //the deque is empty
		// {
		// 	dp->backIndex--; //this will offset the increment so they both point to the only element still
		// }
	}

	dp->data[dp->backIndex] = val;

	dp->backIndex++;
	if((unsigned int)dp->backIndex >= dp->length)
	{
		dp->backIndex = 0;
	}
	dp->usedLength++;
}

void Deque_MyClass_push_front(Deque_MyClass *dp, struct MyClass val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		if(dp->usedLength == dp->length) //the deque is full
		{
			dp->resize(dp, dp->length);
		}
		// else if(dp->usedLength == 0)
		// {
		// 	dp->frontIndex++; //this will offset the increment so they both point to the only element still
		// }
	}
	// printf("frontIndex = %d\n", dp->frontIndex);
	dp->data[dp->frontIndex] = val;

	dp->frontIndex--;
	if(dp->frontIndex < 0)
	{
		dp->frontIndex = dp->length-1;
	}
	dp->usedLength++;
}

void Deque_MyClass_pop_back(Deque_MyClass *dp)
{
	if(dp->backIndex == dp->frontIndex && dp->usedLength == dp->length) return;

	dp->backIndex--;
	if(dp->backIndex < 0)
	{
		dp->backIndex = dp->length-1;
	}
	dp->usedLength--;
}

void Deque_MyClass_pop_front(Deque_MyClass *dp)
{
	if(dp->backIndex == dp->frontIndex && dp->usedLength == dp->length) return;

	dp->frontIndex++;
	if((unsigned int)dp->frontIndex >= dp->length)
	{
		dp->frontIndex = 0;
	}
	dp->usedLength--;
}

void Deque_MyClass_resize(Deque_MyClass *dp, size_t oldLength)
{
	struct MyClass * newData = (struct MyClass *) malloc(sizeof(struct MyClass *) * oldLength * 2);

	for (unsigned int i = 0; i < dp->length; i++)
	{
		newData[i] = dp->data[(dp->frontIndex+1 + i)%dp->length];
	}
	free(dp->data);
	dp->data = newData;
	dp->length = oldLength * 2;
	dp->frontIndex = dp->length-1;
	dp->backIndex = oldLength-1;
}

MyClass& Deque_MyClass_front(Deque_MyClass *dp)
{
	return dp->data[(dp->frontIndex+1)%dp->length];
}

MyClass& Deque_MyClass_back(Deque_MyClass *dp)
{
	return dp->data[(dp->backIndex-1)%dp->length];
}

Deque_MyClass_Iterator Deque_MyClass_Begin(Deque_MyClass *dp)
{
	Deque_MyClass_Iterator it;
	Deque_MyClass_Iterator_ctor(&it, dp, (dp->frontIndex+1)%dp->length);
	return it;
}

Deque_MyClass_Iterator Deque_MyClass_End(Deque_MyClass *dp)
{
	Deque_MyClass_Iterator it;
	Deque_MyClass_Iterator_ctor(&it, dp, (dp->backIndex)%dp->length);
	return it;
}

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2)
{
	return it1.index == it2.index && it1.deque == it2.deque;
}

int Deque_MyClass_sort_compare(const void * a, const void * b, void *c)
{
	MyClass val1 = *(MyClass *) a;
	MyClass val2 = *(MyClass *) b;
	Deque_MyClass * dp = (Deque_MyClass *)c;
	if(dp->compare(val1, val2)) return -1;
	if(dp->compare(val2, val1)) return 1;
	return 0;
}

void Deque_MyClass_sort(Deque_MyClass *dp, Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2)
{
	MyClass * newData = (MyClass *) malloc(sizeof(MyClass *) * dp->length);
	Deque_MyClass_Iterator iter = dp->begin(dp);
	Deque_MyClass_Iterator end = dp->end(dp);
	int frontOffset = 0;
	int backOffset = 0;

	int i = 0;
	for (; !Deque_MyClass_Iterator_equal(iter, end); iter.inc(&iter), i++)
	{
		newData[i] = iter.deref(&iter);
		if(Deque_MyClass_Iterator_equal(iter, it1)) frontOffset = i;
		if(Deque_MyClass_Iterator_equal(iter, it2)) backOffset = i;
	}
	free(dp->data);
	dp->frontIndex = dp->length-1;
	dp->backIndex = dp->usedLength-1;
	dp->data = newData;

	qsort_r((void *)(dp->data + frontOffset), backOffset - frontOffset, sizeof(struct MyClass), Deque_MyClass_sort_compare, (void *)dp);
}

void Deque_MyClass_clear(Deque_MyClass *dp)
{
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 0;
}

void Deque_MyClass_dtor(Deque_MyClass *dp)
{
	free(dp->data);
}

void Deque_MyClass_ctor(Deque_MyClass *dp, bool (*compare)(const struct MyClass&, const struct MyClass&))
{
	dp->compare = compare;
	dp->data = (struct MyClass *) malloc(sizeof(struct MyClass *) * 10);
	dp->length = 10;
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 1;
	dp->empty = &Deque_MyClass_empty;
	dp->size = &Deque_MyClass_size;
	dp->at = &Deque_MyClass_at;
	dp->push_back = &Deque_MyClass_push_back;
	dp->push_front = &Deque_MyClass_push_front;
	dp->pop_back = &Deque_MyClass_pop_back;
	dp->pop_front = &Deque_MyClass_pop_front;
	dp->resize = &Deque_MyClass_resize;
	dp->sort = &Deque_MyClass_sort;
	dp->clear = &Deque_MyClass_clear;
	dp->front = &Deque_MyClass_front;
	dp->back =  &Deque_MyClass_back;
	dp->begin = &Deque_MyClass_Begin;
	dp->end = &Deque_MyClass_End;
	dp->dtor = &Deque_MyClass_dtor;
}

MyClass& Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it)
{
	return it->deque->data[it->index];
}

void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it)
{
	it->index++;
	if((unsigned int)it->index >= it->deque->length)
	{
		it->index = 0;
	}
}

void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it)
{
	it->index--;
	if(it->index < 0)
	{
		it->index = it->deque->length-1;
	}
}

void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator *it, Deque_MyClass *dp, int index)
{
	it->index = index;
	it->deque = dp;
	it->deref = &Deque_MyClass_Iterator_deref;
	it->inc = &Deque_MyClass_Iterator_inc;
	it->dec = &Deque_MyClass_Iterator_dec;
}


bool Deque_MyClass_equal(Deque_MyClass deq1, Deque_MyClass deq2)
{
	if(deq1.usedLength != deq2.usedLength) return false;

	Deque_MyClass_Iterator it1 = deq1.begin(&deq1);
	Deque_MyClass_Iterator end = deq1.end(&deq1);
	Deque_MyClass_Iterator it2 = deq2.begin(&deq2);

    for(; !Deque_MyClass_Iterator_equal(it1, end); it1.inc(&it1), it2.inc(&it2))
    {
		if(deq1.compare(it1.deref(&it1), it2.deref(&it2)) || deq1.compare(it2.deref(&it2), it1.deref(&it1)))
        {
            return false;
        }
    }
    return true;
}








struct Deque_int_Iterator;

typedef struct Deque_int
{
	int * data;
	size_t usedLength;
	size_t length;
	int frontIndex;
	int backIndex;
	char type_name [strlen("Deque_int") + 1] = "Deque_int";
	bool (*compare)(const int &, const int &);
	bool (*empty)(struct Deque_int *dp);
	size_t (*size)(struct Deque_int *dp);
	int& (*at)(struct Deque_int *dp, int i);
	void (*push_back)(struct Deque_int * dp, int val);
	void (*push_front)(struct Deque_int * dp, int val);
	void (*pop_front)(struct Deque_int * dp);
	void (*pop_back)(struct Deque_int * dp);
	void (*resize)(struct Deque_int *dp, size_t oldLength);
	void (*clear)(struct Deque_int * dp);
	void (*sort)(struct Deque_int * dp, Deque_int_Iterator it1, Deque_int_Iterator it2);
	int& (*front)(struct Deque_int *dp);
	int& (*back)(struct Deque_int *dp);
	Deque_int_Iterator (*begin)(struct Deque_int *dp);
	Deque_int_Iterator (*end)(struct Deque_int *dp);
	void (*dtor)(struct Deque_int * dp);

} Deque_int;

void Deque_int_Iterator_ctor(Deque_int_Iterator *it, Deque_int *dp, int index);

typedef struct Deque_int_Iterator
{
	int index;
	Deque_int * deque;
	int& (*deref)(struct Deque_int_Iterator *it);
	void (*inc)(struct Deque_int_Iterator *it);
	void (*dec)(struct Deque_int_Iterator *it);

} Deque_int_Iterator;


bool Deque_int_empty(Deque_int *dp)
{
	return dp->size(dp) == 0;
}

size_t Deque_int_size(Deque_int *dp)
{
	return dp->usedLength;
}

int& Deque_int_at(Deque_int *dp, int i)
{
	return dp->data[(dp->frontIndex+1 + i) % dp->length];
}

void Deque_int_push_back(Deque_int *dp, int val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		// if(dp->usedLength == dp->length) //the deque is full
		// {
			dp->resize(dp, dp->length);
		// }
		// else if(dp->usedLength == 0) //the deque is empty
		// {
		// 	dp->backIndex--; //this will offset the increment so they both point to the only element still
		// }
	}
	dp->data[dp->backIndex] = val;

	dp->backIndex++;
	if((unsigned int)dp->backIndex >= dp->length)
	{
		dp->backIndex = 0;
	}
	dp->usedLength++;
}

void Deque_int_push_front(Deque_int *dp, int val)
{
	if(dp->backIndex == dp->frontIndex)
	{
		// if(dp->usedLength == dp->length) //the deque is full
		// {
			dp->resize(dp, dp->length);
		// }
		// else if(dp->usedLength == 0)
		// {
		// 	dp->frontIndex++; //this will offset the increment so they both point to the only element still
		// }
	}

	dp->data[dp->frontIndex] = val;

	dp->frontIndex--;
	if(dp->frontIndex < 0)
	{
		dp->frontIndex = dp->length-1;
	}
	dp->usedLength++;
}

void Deque_int_pop_back(Deque_int *dp)
{
	if(dp->backIndex == dp->frontIndex && dp->usedLength == dp->length) return;

	dp->backIndex--;
	if(dp->backIndex < 0)
	{
		dp->backIndex = dp->length-1;
	}
	dp->usedLength--;
}

void Deque_int_pop_front(Deque_int *dp)
{
	if(dp->backIndex == dp->frontIndex && dp->usedLength == dp->length) return;

	dp->frontIndex++;
	if((unsigned int)dp->frontIndex >= dp->length)
	{
		dp->frontIndex = 0;
	}
	dp->usedLength--;
}

void Deque_int_resize(Deque_int *dp, size_t oldLength)
{
	int * newData = (int *) malloc(sizeof(int *) * oldLength * 2);

	for (unsigned int i = 0; i < dp->length; i++)
	{
		newData[i] = dp->data[(dp->frontIndex+1 + i)%dp->length];
	}
	free(dp->data);
	dp->data = newData;
	dp->length = oldLength * 2;
	dp->frontIndex = dp->length-1;
	dp->backIndex = oldLength-1;
}

int& Deque_int_front(Deque_int *dp)
{
	return dp->data[(dp->frontIndex+1)%dp->length];
}

int& Deque_int_back(Deque_int *dp)
{
	return dp->data[(dp->backIndex-1)%dp->length];
}

Deque_int_Iterator Deque_int_Begin(Deque_int *dp)
{
	Deque_int_Iterator it;
	Deque_int_Iterator_ctor(&it, dp, (dp->frontIndex+1)%dp->length);
	return it;
}

Deque_int_Iterator Deque_int_End(Deque_int *dp)
{
	Deque_int_Iterator it;
	Deque_int_Iterator_ctor(&it, dp, (dp->backIndex)%dp->length);
	return it;
}

bool Deque_int_Iterator_equal(Deque_int_Iterator it1, Deque_int_Iterator it2)
{
	return it1.index == it2.index && it1.deque == it2.deque;
}

int Deque_int_sort_compare(const void * a, const void * b, void *c)
{
	int val1 = *(int *) a;
	int val2 = *(int *) b;
	Deque_int * dp = (Deque_int *)c;
	if(dp->compare(val1, val2)) return -1;
	if(dp->compare(val2, val1)) return 1;
	return 0;
}

void Deque_int_sort(Deque_int *dp, Deque_int_Iterator it1, Deque_int_Iterator it2)
{
	int * newData = (int *) malloc(sizeof(int *) * dp->length);
	Deque_int_Iterator iter = dp->begin(dp);
	Deque_int_Iterator end = dp->end(dp);
	int frontOffset = 0;
	int backOffset = 0;

	int i = 0;
	for (; !Deque_int_Iterator_equal(iter, end); iter.inc(&iter), i++)
	{
		newData[i] = iter.deref(&iter);
		if(Deque_int_Iterator_equal(iter, it1)) frontOffset = i;
		if(Deque_int_Iterator_equal(iter, it2)) backOffset = i;
	}
	free(dp->data);
	dp->frontIndex = dp->length-1;
	dp->backIndex = dp->usedLength-1;
	dp->data = newData;

	qsort_r((void *)(dp->data + frontOffset), backOffset - frontOffset, sizeof(int), Deque_MyClass_sort_compare, (void *)dp);
}

void Deque_int_clear(Deque_int *dp)
{
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 0;
}

void Deque_int_dtor(Deque_int *dp)
{
	free(dp->data);
}

void Deque_int_ctor(Deque_int *dp, bool (*compare)(const int &, const int &))
{
	dp->compare = compare;
	dp->data = (int *) malloc(sizeof(int *) * 10);
	dp->length = 10;
	dp->usedLength = 0;
	dp->frontIndex = 0;
	dp->backIndex = 1;
	dp->empty = &Deque_int_empty;
	dp->size = &Deque_int_size;
	dp->at = &Deque_int_at;
	dp->push_back = &Deque_int_push_back;
	dp->push_front = &Deque_int_push_front;
	dp->pop_back = &Deque_int_pop_back;
	dp->pop_front = &Deque_int_pop_front;
	dp->resize = &Deque_int_resize;
	dp->sort = &Deque_int_sort;
	dp->clear = &Deque_int_clear;
	dp->front = &Deque_int_front;
	dp->back =  &Deque_int_back;
	dp->begin = &Deque_int_Begin;
	dp->end = &Deque_int_End;
	dp->dtor = &Deque_int_dtor;
}

int& Deque_int_Iterator_deref(Deque_int_Iterator *it)
{
	return it->deque->data[it->index];
}

void Deque_int_Iterator_inc(Deque_int_Iterator *it)
{
	it->index++;
	if((unsigned int)it->index >= it->deque->length)
	{
		it->index = 0;
	}
}

void Deque_int_Iterator_dec(Deque_int_Iterator *it)
{
	it->index--;
	if(it->index < 0)
	{
		it->index = it->deque->length-1;
	}
}

void Deque_int_Iterator_ctor(Deque_int_Iterator *it, Deque_int *dp, int index)
{
	it->index = index;
	it->deque = dp;
	it->deref = &Deque_int_Iterator_deref;
	it->inc = &Deque_int_Iterator_inc;
	it->dec = &Deque_int_Iterator_dec;
}
bool Deque_int_equal(Deque_int deq1, Deque_int deq2)
{
	if(deq1.usedLength != deq2.usedLength) return false;

	Deque_int_Iterator it1 = deq1.begin(&deq1);
	Deque_int_Iterator end = deq1.end(&deq1);
	Deque_int_Iterator it2 = deq2.begin(&deq2);

	for(; !Deque_int_Iterator_equal(it1, end); it1.inc(&it1), it2.inc(&it2))
	{
		if(deq1.compare(it1.deref(&it1), it2.deref(&it2)) || deq1.compare(it2.deref(&it2), it1.deref(&it1)))
		{
			return false;
		}
	}
    return true;
}


#endif
