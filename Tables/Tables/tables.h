#ifndef ___PT_____H__
#define ___PT_____H__

#include <iostream>
#include "../Polinom/polinom.h"
#include <cmath>

struct t_str
{
	char key;
	Polinom pol;
};

class Table
{
public:
	t_str tab[256];
	Table()
	{
		for (int i = 0; i < 256; i++)
		{
			tab[i].key = 0;
		}
	}
};

class NPT : Table
{
private:
	int size;
public:
	NPT()
	{
		size = 0;
	}

	void insert(t_str _el)
	{
		if (size != 256)
		{
			tab[size] = _el;
			size++;
		}
		else
		{
			cout << "Table is full" << endl;
		}
		cout << "Insert in unordered table, 1 operation" << endl;
	}

	Polinom find(char _key)
	{
		for (int i = 0; i < size; i++)
		{
			if (tab[i].key == _key)
			{
				cout << "Find polinom in unordered table, " << i + 1 << " operations" << endl;
				return tab[i].pol;
			}
		}
		cout << "Polinom unfinded" << endl;
		throw ("Unfinded polinom");
	}

	void del(char _key)
	{
		for (int i = 0; i < size; i++)
		{
			if (tab[i].key == _key)
			{
				for (int j = i; j < size - 1; j++)
				{
					tab[j] = tab[j + 1];
				}
				cout << "Delete polinom in unordered table, " << i + 1 << " operations" << endl;
				size--;
				break;
			}
		}
	}
};

class PT : Table
{
private:
	int size;
public:
	PT()
	{
		size = 0;
	}

	void insert(t_str _el)
	{
		if (size == 256)
		{
			cout << "PT is full" << endl;
			throw ("PT is full");
		}
		int left = 0, right = size - 1, mid = 0;
		int flag_b_i = 0, flag_n_o = 0;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (tab[mid].key < _el.key)
			{
				left = mid + 1;
				flag_b_i = 1;
			}
			else
			{
				right = mid - 1;
				flag_b_i = 0;
			}
			flag_n_o++;
		}
		
		for (int i = size - 1; i >= mid + flag_b_i; i--)
		{
			tab[i + 1] = tab[i];
			flag_n_o++;
		}
		tab[mid + flag_b_i] = _el;
		size++;
		cout << "Insert in ordered table, " << flag_n_o + 1 << " operations" << endl;
	}

	Polinom find(char _key)
	{
		int left = 0, right = size - 1, mid = 0;
		int flag_n_o = 0;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (tab[mid].key == _key)
			{
				cout << "Find polinom in ordered table, " << flag_n_o + 1 << " operations" << endl;
				return tab[mid].pol;
			}
			if (tab[mid].key < _key)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
			flag_n_o++;
		}
		cout << "Polinom unfinded" << endl;
		throw ("Unfinded polinom");
	}

	void del(char _key)
	{
		int left = 0, right = size - 1, mid = 0;
		int flag_n_o = 0;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (tab[mid].key == _key)
			{
				for (int i = mid; i < size - 1; i++)
				{
					tab[i] = tab[i + 1];
					flag_n_o++;
				}
				cout << "Delete polinom in ordered table, " << flag_n_o + 1 << " operations" << endl;
				size--;
				break;
			}
			if (tab[mid].key < _key)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
			flag_n_o++;
		}
	}
};

class HT : Table
{
private:
	bool t[256];
public:
	HT()
	{
		for (int i = 0; i < 256; i++)
		{
			t[i] = false;
		}
	}

	int HF(char _key)
	{
		return (int)(_key * 10 / 31 * 97) % 256;
	}

	void insert(t_str _el)
	{
		int _key = HF(_el.key);
		int flag_n_o = 0;
		while (t[_key] == true)
		{
			_key = _key * 45 % 256;
			flag_n_o++;
		}
		tab[_key] = _el;
		t[_key] = true;
		cout << "Insert in ordered table, " << flag_n_o + 1 << " operations" << endl;
	}
	
    Polinom find(char _key)
	{
		int n_key = HF(_key), o_key = n_key;
		int flag_n_o = 0;
		while (tab[n_key].key != _key)
		{
			n_key = n_key * 45 % 256;
			flag_n_o++;
			if (n_key == o_key)
			{
				cout << "Polinom unfinded" << endl;
				throw ("Unfinded polinom");
			}
		}
		cout << "Find polinom in ordered table, " << flag_n_o + 1 << " operations" << endl;
		return tab[n_key].pol;
	}

	void del(char _key)
	{
		int n_key = HF(_key);
		int flag_n_o = 0;
		while (tab[n_key].key != _key)
		{
			n_key = n_key * 45 % 256;
			flag_n_o++;
		}
		t[n_key] = false;
		cout << "Delete polinom in ordered table, " << flag_n_o + 1 << " operations" << endl;
	}
};
#endif