#pragma once
#include <iostream>

template<class K, class V>
class table
{
private:
	K* arrKey;
	V* arrVal;
	size_t MaxSizeTable, countUsed;

public:
	table(size_t size);
	~table();

	void add(K k, V v);

	void remove(K k);

	V& operator[](K k);

	table& operator = (table& vt);


	void resize(size_t newsized);


	friend std::ostream& operator<<(std::ostream& os, table<K, V>& t)
	{
		for (size_t i = 0; i < t.countUsed; i++)
		{
			os << t.arrKey[i] << " | " << t.arrVal[i] << std::endl;
		}

		return os;
	}

};

template<class K, class V>
table<K, V>::table(size_t size)
{
	MaxSizeTable = size;
	arrKey = new K[size];
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		arrKey[i] = NULL;
	}
	arrVal = new V[size];
	countUsed = 0;
}

template<class K, class V>
table<K, V>::~table()
{
	delete[]arrKey;
	delete[]arrVal;
}

template<class K, class V>
void table<K, V>::add(K k, V v)
{
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		if (arrKey[i] == NULL || arrKey[i] >= k)
		{
			arrKey[countUsed] = k;
			arrVal[countUsed++] = v;

			for (size_t x = i; i < countUsed - 1; i++)
			{
				K tk = arrKey[x];
				V tv = arrVal[x];

				arrKey[x] = arrKey[countUsed - 1];
				arrVal[x] = arrVal[countUsed - 1];
				arrKey[countUsed - 1] = tk;
				arrVal[countUsed - 1] = tv;
			}
			return;

		}
	}

	throw string("Table is full");

}

template<class K, class V>
void table<K, V>::remove(K k)
{
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		if (arrKey[i] == k)
		{
			for (size_t x = i; i < countUsed; i++)
			{
				arrKey[x] = arrKey[countUsed - 1];
				arrVal[x] = arrVal[countUsed - 1];
			}
			arrKey[countUsed--] = NULL;
			break;
		}
	}
}

template<class K, class V>
V & table<K, V>::operator[](K k)
{

	{
		for (size_t i = 0; i < MaxSizeTable; i++)
			if (arrKey[i] == k)
				return arrVal[i];

		throw string("Not found index");
	}
}

template<class K, class V>


table<K, V> & table<K, V>::operator=(table & vt)
{
	MaxSizeTable = vt.MaxSizeTable;
	arrKey = new K[MaxSizeTable];
	arrVal = new V[MaxSizeTable];
	countUsed = vt.countUsed;
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		arrKey[i] = vt.arrKey[i];
		arrVal[i] = vt.arrVal[i];
	}

	return *this;
}

template<class K, class V>
void table<K, V>::resize(size_t newsized)
{
	if (newsized == MaxSizeTable)
		return;
	if (newsized < countUsed)
		throw string("Need clear table");

	K* Tkey = new K[newsized];
	V* Tval = new V[newsized];
	size_t insertindex = 0;
	for (int i = 0; i < MaxSizeTable; i++)
	{
		Tkey[insertindex] = arrKey[i];
		Tval[insertindex] = arrVal[i];
		++insertindex;
		if (arrKey[i] == NULL)
			break;
	}
	delete[]arrKey, arrVal;
	arrKey = Tkey;
	arrVal = Tval;
	MaxSizeTable = newsized;
}
