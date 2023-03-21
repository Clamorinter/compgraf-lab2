#pragma once

template <typename T>
class dynarr
{
public:
	dynarr() {
		arr = new T;
		count = 0;
	}
	dynarr(int n) {
		arr = new T[n];
		count = n;
	}
	~dynarr()
	{
		delete[] arr;
	}
	T* arr;
	void append()
	{
		changeLength(1);
	}
	void append(T elem)
	{
		changeLength(1);
		arr[count - 1] = elem;
	}
	void decrease()
	{
		changeLength(-1);
	}
	int getLength()
	{
		return count;
	}
private:
	int count;
	void changeLength(int i) // возможен баг при удалении массива
	{
		if (i >= 0)
		{
			T* buff = new T[count + i];
			if (count != 0)
			{
				memcpy(buff, arr, sizeof(T) * count);
				delete[] arr;
			}
			arr = buff;
			count += i;
		}
		else
		{
			if (count != 0)
			{
				T* buff = new T[count + i];
				memcpy(buff, arr, sizeof(T) * (count+i));
				delete[] arr;
				arr = buff;
				count += i;
			}
		}
	}
};