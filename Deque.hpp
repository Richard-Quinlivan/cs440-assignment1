#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define Deque_DEFINE(t)														\
	struct Deque_##t##_Iterator;			\
	typedef struct Deque_##t			\
	{			\
		t * data;			\
		size_t usedLength;			\
		size_t length;			\
		int frontIndex;			\
		int backIndex;			\
		char type_name [strlen(#t) + 7] = "Deque_";			\
		bool (*empty)(struct Deque_##t *dp);			\
		size_t (*size)(struct Deque_##t *dp);			\
		void (*clear)(struct Deque_##t * dp);			\
		t & (*at)(struct Deque_##t *dp, int i);			\
		t & (*front)(struct Deque_##t *dp);			\
		t & (*back)(struct Deque_##t *dp);			\
		void (*push_back)(struct Deque_##t * dp, t val);			\
		void (*push_front)(struct Deque_##t * dp, t val);			\
		void (*pop_front)(struct Deque_##t * dp);			\
		void (*pop_back)(struct Deque_##t * dp);			\
		void (*resize)(struct Deque_##t *dp, size_t oldLength);			\
		void (*sort)(struct Deque_##t * dp, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);			\
		bool (*compare)(const t &, const t &);			\
		Deque_##t##_Iterator (*begin)(struct Deque_##t *dp);			\
		Deque_##t##_Iterator (*end)(struct Deque_##t *dp);			\
		void (*dtor)(struct Deque_##t * dp);			\
	} Deque_##t;										\
	bool Deque_##t##_empty(Deque_##t *dp);			\
	size_t Deque_##t##_size(Deque_##t *dp);			\
	void Deque_##t##_clear(Deque_##t *dp);			\
	t & Deque_##t##_at(Deque_##t *dp, int i);			\
	t & Deque_##t##_back(Deque_##t *dp);			\
	t & Deque_##t##_front(Deque_##t *dp);			\
	void Deque_##t##_push_back(Deque_##t *dp, t val);			\
	void Deque_##t##_push_front(Deque_##t *dp, t val);			\
	void Deque_##t##_pop_back(Deque_##t *dp);			\
	void Deque_##t##_pop_front(Deque_##t *dp);			\
	void Deque_##t##_resize(Deque_##t *dp, size_t oldLength);			\
	void Deque_##t##_sort(Deque_##t *dp, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);			\
	void Deque_##t##_sort_helper(Deque_##t *dp, int index);		\
	bool Deque_##t##_Is_Used(Deque_##t *dp, int index);		\
	int Deque_##t##_sort_compare(const void * a, const void * b, void *c);		\
	Deque_##t##_Iterator Deque_##t##_Begin(Deque_##t *dp);		\
	Deque_##t##_Iterator Deque_##t##_End(Deque_##t *dp);		\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);		\
	void Deque_##t##_dtor(Deque_##t *dp);		\
	void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it, Deque_##t *dp, int index);		\
	typedef struct Deque_##t##_Iterator		\
	{		\
		int index;			\
		Deque_##t * deque;			\
		t & (*deref)(struct Deque_##t##_Iterator *it);			\
		void (*inc)(struct Deque_##t##_Iterator *it);			\
		void (*dec)(struct Deque_##t##_Iterator *it);			\
	} Deque_##t##_Iterator;			\
	void Deque_##t##_ctor(Deque_##t *dp, bool (*compare)(const t &, const t &))			\
	{			\
		dp->compare = compare;			\
		dp->data = (t *) malloc(sizeof(t) * 10);			\
		strcat(dp->type_name, #t);							\
		dp->length = 10;			\
		dp->usedLength = 0;			\
		dp->frontIndex = 9;			\
		dp->backIndex = 0;			\
		dp->empty = &Deque_##t##_empty;			\
		dp->size = &Deque_##t##_size;			\
		dp->at = &Deque_##t##_at;			\
		dp->push_back = &Deque_##t##_push_back;			\
		dp->push_front = &Deque_##t##_push_front;			\
		dp->pop_back = &Deque_##t##_pop_back;			\
		dp->pop_front = &Deque_##t##_pop_front;			\
		dp->resize = &Deque_##t##_resize;			\
		dp->sort = &Deque_##t##_sort;			\
		dp->clear = &Deque_##t##_clear;			\
		dp->front = &Deque_##t##_front;			\
		dp->back =  &Deque_##t##_back;			\
		dp->begin = &Deque_##t##_Begin;			\
		dp->end = &Deque_##t##_End;			\
		dp->dtor = &Deque_##t##_dtor;			\
	}			\
	bool Deque_##t##_empty(Deque_##t *dp)		\
	{		\
		return dp->size(dp) == 0;		\
	}		\
	size_t Deque_##t##_size(Deque_##t *dp)		\
	{		\
		return dp->usedLength;		\
	}		\
	void Deque_##t##_clear(Deque_##t *dp)		\
	{		\
		dp->usedLength = 0;		\
		dp->frontIndex = 0;		\
		dp->backIndex = 0;		\
	}		\
	t & Deque_##t##_at(Deque_##t *dp, int i)		\
	{		\
		return dp->data[(dp->frontIndex+1 + i) % dp->length];		\
	}		\
	t & Deque_##t##_front(Deque_##t *dp)		\
	{		\
		return dp->data[(dp->frontIndex+1)%dp->length];		\
	}		\
	t & Deque_##t##_back(Deque_##t *dp)		\
	{		\
		return dp->data[(dp->backIndex-1)%dp->length];		\
	}		\
	void Deque_##t##_push_back(Deque_##t *dp, t val)		\
	{		\
		if(dp->usedLength == dp->length)		\
		{		\
			dp->resize(dp, dp->length);		\
			dp->backIndex = dp->usedLength;		\
		}		\
		dp->data[dp->backIndex] = val;		\
		dp->backIndex = (dp->backIndex+1) % dp->length;		\
		dp->usedLength++;		\
	}		\
	void Deque_##t##_push_front(Deque_##t *dp, t val)		\
	{		\
		if(dp->usedLength == dp->length)		\
		{		\
			dp->resize(dp, dp->length);		\
			dp->frontIndex = dp->length-1;		\
		}		\
		dp->data[dp->frontIndex] = val;		\
		dp->frontIndex = (dp->frontIndex-1 + dp->length) % dp->length;		\
		dp->usedLength++;		\
	}		\
	void Deque_##t##_pop_back(Deque_##t *dp)		\
	{		\
		dp->backIndex = (dp->backIndex-1 + dp->length) % dp->length;		\
		dp->usedLength--;		\
	}		\
	void Deque_##t##_pop_front(Deque_##t *dp)		\
	{		\
		dp->frontIndex = (dp->frontIndex+1) % dp->length;		\
		dp->usedLength--;		\
	}		\
	void Deque_##t##_resize(Deque_##t *dp, size_t oldLength)		\
	{		\
		t * newData = (t *) malloc(sizeof(t *) * oldLength * 2);		\
		for (unsigned int i = 0; i < dp->length; i++)		\
		{		\
			newData[i] = dp->data[(dp->frontIndex+1 + i)%dp->length];		\
		}		\
		free(dp->data);		\
		dp->data = newData;		\
		dp->length = oldLength * 2;		\
		dp->frontIndex = dp->length-1;		\
		dp->backIndex = oldLength-1;		\
	}																						\
	void Deque_##t##_sort(Deque_##t *dp, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2)		\
	{		\
		int frontOffset = it1.index + (dp->length-1 - dp->frontIndex) % dp->length;		\
		int backOffset = it2.index + (dp->length-1 - dp->frontIndex) % dp->length;		\
		if(it1.index > it2.index)		\
		{		\
			Deque_##t##_Iterator iter = dp->begin(dp);		\
			Deque_##t##_Iterator end = dp->end(dp);		\
			int i = 0;		\
			for (; !Deque_##t##_Iterator_equal(iter, end); iter.inc(&iter), i++)		\
			{		\
				if(Deque_##t##_Is_Used(dp, i))		\
				{		\
					Deque_##t##_sort_helper(dp, i);		\
				}		\
				dp->data[i] = iter.deref(&iter);		\
			}		\
		}		\
		qsort_r((void *)(dp->data + frontOffset), backOffset - frontOffset, sizeof(t), Deque_##t##_sort_compare, (void *)dp);		\
	}		\
	void Deque_##t##_sort_helper(Deque_##t *dp, int index)		\
	{		\
		int properIndex;		\
		if(index < dp->frontIndex) properIndex = index + (dp->length - dp->frontIndex);		\
		else properIndex = index - dp->frontIndex;		\
		if(Deque_##t##_Is_Used(dp, properIndex))		\
		{		\
			Deque_##t##_sort_helper(dp, properIndex);		\
		}		\
		dp->data[properIndex] = dp->data[index];		\
	}		\
	bool Deque_##t##_Is_Used(Deque_##t *dp, int index)			\
	{			\
		if(dp->frontIndex < dp->backIndex) return dp->frontIndex <= index && index <= dp->backIndex;			\
		else return dp->frontIndex >= index && index >= dp->backIndex;			\
	}			\
	int Deque_##t##_sort_compare(const void * a, const void * b, void *c)			\
	{			\
	t val1 = *(t *) a;			\
	t val2 = *(t *) b;			\
		Deque_##t * dp = (Deque_##t *)c;			\
		if(dp->compare(val1, val2)) return -1;			\
		if(dp->compare(val2, val1)) return 1;			\
		return 0;			\
	}			\
	Deque_##t##_Iterator Deque_##t##_Begin(Deque_##t *dp)			\
	{			\
		Deque_##t##_Iterator it;			\
		Deque_##t##_Iterator_ctor(&it, dp, (dp->frontIndex+1)%dp->length);			\
		return it;			\
	}			\
	Deque_##t##_Iterator Deque_##t##_End(Deque_##t *dp)			\
	{			\
		Deque_##t##_Iterator it;			\
		Deque_##t##_Iterator_ctor(&it, dp, (dp->backIndex)%dp->length);			\
		return it;			\
	}			\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2)			\
	{			\
		return it1.index == it2.index && it1.deque == it2.deque;			\
	}			\
				\
	void Deque_##t##_dtor(Deque_##t *dp)			\
	{			\
		free(dp->data);			\
	}			\
	t & Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it)			\
	{			\
		return it->deque->data[it->index];			\
	}			\
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it)			\
	{			\
		it->index = (it->index+1) % it->deque->length;			\
	}			\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it)			\
	{			\
		it->index = (it->index-1 + it->deque->length) % it->deque->length;			\
	}			\
	void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it, Deque_##t *dp, int index)			\
	{			\
		it->index = index;			\
		it->deque = dp;			\
		it->deref = &Deque_##t##_Iterator_deref;			\
		it->inc = &Deque_##t##_Iterator_inc;			\
		it->dec = &Deque_##t##_Iterator_dec;			\
	}			\
	bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2)			\
	{			\
		if(deq1.usedLength != deq2.usedLength) return false;			\
		Deque_##t##_Iterator it1 = deq1.begin(&deq1);			\
		Deque_##t##_Iterator end = deq1.end(&deq1);			\
		Deque_##t##_Iterator it2 = deq2.begin(&deq2);			\
	    for(; !Deque_##t##_Iterator_equal(it1, end); it1.inc(&it1), it2.inc(&it2))			\
	    {			\
			if(deq1.compare(it1.deref(&it1), it2.deref(&it2)) || deq1.compare(it2.deref(&it2), it1.deref(&it1)))			\
	        {			\
	            return false;			\
	        }			\
	    }			\
	    return true;			\
	}
#endif
