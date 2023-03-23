#pragma once
#include <iostream>
#include <iterator>
using namespace std;

template <class T>
class Container
{
private:
	T* Arr;
	T* head;
	T* tail;
	int size;
public:

	Container() : Arr(0), size(0), head(0), tail(0) {}
	Container(int size, T value);
	Container(const Container<T>& vec);

	~Container() 
	{
		delete[] this->Arr; 
	}

	void add(const T& obj);
	void del(int index);
	void sort();
	int findMax();

	void clear();
	int getSize() { return this->size; }
	T* getArray() { return this->Arr; }

	T& operator[](int index) { return this->Arr[index]; }
	void operator=(const Container<T>& vec);

	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() { m_ptr++; return *this; }

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; m_ptr++; return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};
	Iterator begin() { return Iterator(head); }
	Iterator end() 
	{ 
		if (head)
			return Iterator(tail + 1);
		else
			return nullptr;
	}
};

template<class T>
inline Container<T>::Container(int size, T value)
{
	this->size = size;
	this->Arr = new T[size];

	for (register int i = 0; i < size; i++)
		Arr[i] = value;

	this->head = this->Arr;
	this->tail = this->Arr + size - 1;
}

template<class T>
inline Container<T>::Container(const Container<T>& vec)
{
	this->size = vec.size;
	this->Arr = new T[this->size];
	for (register int i = 0; i < size; i++)
		this->Arr[i] = vec.Arr[i];

	this->head = this->Arr;
	this->tail = this->Arr + size - 1;
}

template <class T>
inline void Container<T>::add(const T& obj)
{
	if (size > 0)
	{
		T* buf_ms;
		buf_ms = new T[size];
		for (register int i = 0; i < size; i++)
			buf_ms[i] = this->Arr[i];
		delete[] this->Arr;
		size++;
		this->Arr = new T[size];
		this->head = this->Arr;

		for (register int i = 0; i < (size - 1); i++)
			this->Arr[i] = buf_ms[i];
		delete[] buf_ms;
		this->Arr[size - 1] = obj;
		this->tail = this->Arr + size - 1;
	}
	else
	{
		this->size = 1;
		this->Arr = new T[size];
		this->Arr[0] = obj;
		this->head = this->tail = this->Arr;
	}
}

template<class T>
inline void Container<T>::del(int index)
{
	if (size > 1)
	{
		T* buf_ms = new T[this->size - 1];
		register int j = 0;
		for (register int i = 0; i < this->size; i++)
		{
			if (i != index)
			{
				buf_ms[j] = this->Arr[i];
				j++;
			}
		}
		delete[] this->Arr;
		this->size--;
		this->Arr = new T[this->size];
		for (register int i = 0; i < this->size; i++)
			this->Arr[i] = buf_ms[i];
		delete[] buf_ms;

		this->head = this->Arr;
		this->tail = this->Arr + size - 1;
	}
	else if (size == 1)
	{
		this->size--;
		delete[] this->Arr;

		this->head = this->tail = nullptr;
	}
}

template<class T>
inline void Container<T>::sort()
{
	if (this->size > 1)
	{
		for (int s = this->size / 2; s > 0; s /= 2)
		{
			for (int i = 0; i < this->size; i++)
			{
				for (int j = i + s; j < this->size; j += s)
				{
					if (this->Arr[i] < this->Arr[j])
					{
						T temp;
						temp = Arr[j];
						this->Arr[j] = this->Arr[i];
						this->Arr[i] = temp;
					}
				}
			}
		}
		this->head = this->Arr;
		this->tail = this->Arr + size - 1;
	}
}

template<class T>
inline int Container<T>::findMax()
{
	int index = 0;
	for (register int i = 0; i < this->size; i++)
	{
		if (this->Arr[index] < this->Arr[i])
			index = i;
	}
	return index;
}

template<class T>
inline void Container<T>::clear()
{
	delete[] this->Arr;
	this->head = this->tail = this->Arr = nullptr;
	this->size = 0;
}

template<class T>
inline void Container<T>::operator=(const Container<T>& vec)
{
	delete[] this->Arr;
	this->size = vec.size;
	this->Arr = new T[this->size];
	for (register int i = 0; i < this->size; i++)
		this->Arr[i] = vec.Arr[i];

	if (size)
	{
		this->head = this->Arr;
		this->tail = this->Arr + size - 1;
	}
	else
		this->head = this->tail = nullptr;
}