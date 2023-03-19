#include "dynarr.h"

template <typename T>
void dynarr<T>::append()
{
	changeLength(1);
}

template <typename T>
void dynarr<T>::append(T elem)
{
	changeLength(1);
	arr[count - 1] = elem;
}

template <typename T>
void dynarr<T>::decrease()
{
	changeLength(-1);
}