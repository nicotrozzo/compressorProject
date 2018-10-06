#pragma once
#include <iostream>
#include "image.h"

#define LIST_MAX_SIZE 50

template <typename T> class list
{
public:
	list(int listSize = LIST_MAX_SIZE);
	~list();
	//virtual bool clear();
	virtual int getSize();
	virtual bool moveToPos(int pos);
	virtual bool previous();
	virtual bool next();
	virtual void moveToStart();
	virtual int getCurrentPos();
	//virtual bool append();
	//virtual bool insert();
	virtual const T& getValue();
private:
	//int maxSize;
	int listSize;
	int pos;
	T * array;
	//T nothing;
};

template <typename T> list<T>::list(int listSize)
{
	array = new T[listSize];
	this->listSize = listSize;
	pos = 0;
}

template <typename T> int list<T>::getCurrentPos()
{
	return pos;
}

template <typename T> bool list<T>::moveToPos(int pos)
{
	if (pos >= 0 && pos < listSize)
	{
		this->pos = pos;
		return true;
	}
	return false;
}

template <typename T> void list<T>::moveToStart()
{
	pos = 0;
}

template <typename T> bool list<T>::previous()
{
	if (pos > 0 && pos < (listSize - 1))
	{
		pos--;
		return true;
	}
	return false;
}

template <typename T> bool list<T>::next()
{
	if (pos > 0 && pos < (listSize - 1))
	{
		pos++;
		return true;
	}
	return false;
}

template <typename T> int list<T>::getSize()
{
	return listSize;
}

template <typename T> const T& list<T>::getValue()
{
	return array[pos];
}

template <typename T> list<T>::~list()
{
	delete[] array;
}