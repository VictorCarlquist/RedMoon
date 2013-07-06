#ifndef _STACK_
#define _STACK_

#include <cstdlib>
#include <iostream>

template <class T> class Rstack{

	public:
        T *items;
        unsigned int max;
		int ind;
        Rstack(){
            max = 1200;
            items = (T* ) malloc(sizeof(T) * max);
			ind = 0;

		}
        ~Rstack(){}
		
		void push(T a)
		{
			items[ind++] = a;
            if(ind == max)
            {
                   items = (T* ) realloc(items,sizeof(T) * max+10);
                   max+=10;
            }
            return;
		} 
		T pop()
		{
            if(ind == max - 10)
            {
                 items = (T* ) realloc(items,sizeof(T) * max-10);
            }
            if(ind > 0)
                return items[--ind];

		}
        int size()
        {
             return ind;

        }
        bool empty()
        {
            return (ind == 0)? true:false;
        }
};

#endif
