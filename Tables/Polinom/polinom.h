#ifndef __POLINOM___H
#define __POLINOM___H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class Monom
{
public:
	int deg; //deg < 1000;
	float fact;
	Monom* prev;
	Monom* next;
};

class Polinom
{
private:
	Monom* head;

public:
	Polinom()
	{
		Monom* _monom = new Monom;
		_monom->next = NULL;
		_monom->prev = NULL;
		_monom->deg = -1;
		_monom->fact = 0;
		head = _monom;
	}

	Polinom(Polinom& _oth):Polinom()
	{
		Monom* _monom1 = _oth.head->next;
		Monom* _monom2 = head;
		while (_monom1 != NULL)
		{
			Monom* _monom3 = new Monom;
			_monom3->next = NULL;
			_monom3->prev = _monom2;
			_monom3->deg = _monom1->deg;
			_monom3->fact = _monom1->fact;
			_monom2->next = _monom3;
			_monom1 = _monom1->next;
			_monom2 = _monom2->next;
		}
	}

	~Polinom()
	{
		delall();
		delete head;
	}

	bool operator == (const Polinom& _oth)
	{
		Monom* _monom1 = head->next;
		Monom* _monom2 = _oth.head->next;

		while (_monom1 != NULL && _monom2 != NULL)
		{
			if (_monom1 == NULL)
			{
				if (_monom2 != NULL)
				{
					return false;
				}
			}
			else
			{
				if (_monom2 == NULL)
				{
					return false;
				}
				else
				{
					if (_monom1->deg != _monom2->deg || _monom1->fact != _monom2->fact)
					{
						return false;
					}
					else
					{
						_monom1 = _monom1->next;
						_monom2 = _monom2->next;
					}
				}
			}
		}
		return true;
	}

	bool operator != (const Polinom& _oth)
	{
		return !(*this == _oth);
	}

	Monom* find(int _deg)
	{
		if (_deg < 0 || _deg > 999)
		{
			return NULL;
		}
		Monom* _monom1 = head->next;
		while (_monom1 != NULL)
		{
			if (_monom1->deg == _deg)
			{
				return _monom1;
			}
			else
			{
				_monom1 = _monom1->next;
			}
		}
		return NULL;
	}

	bool boolfind(int _deg)
	{
		return NULL == !(find(_deg));
	}

	void insert(int _deg, float _fact)
	{
		if (fabs(_fact) < 0.00000001)
		{
			return;
		}
		if (_deg < 0 || _deg > 999)
		{
			throw (string)"degree entered incorrectly";
		}
		if (head->next == NULL)
		{
			Monom* _monom1 = new Monom;
			_monom1->next = NULL;
			_monom1->prev = head;
			_monom1->deg = _deg;
			_monom1->fact = _fact;
			head->next = _monom1;
		}
		else
		{
			Monom* _monom1 = head;
			while ((_monom1->next != NULL) && (_monom1->next->deg > _deg))
			{
				_monom1 = _monom1->next;
			}
			if (_monom1->next == NULL)
			{
				Monom* _monom2 = new Monom;
				_monom2->next = NULL;
				_monom2->prev = _monom1;
				_monom2->deg = _deg;
				_monom2->fact = _fact;
				_monom1->next = _monom2;
			}
			else
			{
				if (_monom1->next->deg == _deg)
				{
					if (fabs(_monom1->next->fact + _fact) < 0.00000001)
					{
						del(_monom1->next->deg, _monom1->next->fact);
					}
					else
					{
						_monom1->next->fact = _monom1->next->fact + _fact;
					}
				}
				else
				{
					Monom* _monom2 = new Monom;
					_monom2->prev = _monom1;
					_monom2->next = _monom1->next;
					_monom2->deg = _deg;
					_monom2->fact = _fact;
					_monom1->next->prev = _monom2;
					_monom1->next = _monom2;
				}
			}
		}
	}

	void del(int _deg, float _fact)
	{
		Monom* _monom1 = find(_deg);
		if (_monom1 != NULL)
		{
			if (_monom1->next == NULL)
			{
				_monom1->prev->next = NULL;
			}
			else
			{
				_monom1->prev->next = _monom1->next;
				_monom1->next->prev = _monom1->prev;
			}
			delete _monom1;
		}
	}

	void delall()
	{
		if (head->next == NULL)
		{
			return;
		}
		Monom* _monom1 = head->next;
		while (_monom1->next != NULL)
		{
			_monom1 = _monom1->next;
		}
		while (_monom1 != head)
		{
			Monom* _monom2 = _monom1;
			_monom1 = _monom1->prev;
			delete _monom2;
		}
		head->next = NULL;
	}

	Polinom& operator = (const Polinom& _oth)
	{
		if (head != _oth.head)
		{
			delall();
			Monom* _monom1 = _oth.head->next;
			while (_monom1 != NULL)
			{
				Monom* _monom2 = head;
				while (_monom2->next != NULL)
				{
					_monom2 = _monom2->next;
				}
				Monom* _monom3 = new Monom;
				_monom3->next = NULL;
				_monom3->prev = _monom2;
				_monom3->deg = _monom1->deg;
				_monom3->fact = _monom1->fact;
				_monom2->next = _monom3;
				_monom1 = _monom1->next;
			}
		}
		return *this;
	}

private:
	void bringingsimilar(Polinom& _oth) const
	{
		Monom* _monom1 = _oth.head->next;
		while (_monom1 != NULL && _monom1->next != NULL)
		{
			if (_monom1->deg == _monom1->next->deg)
			{
				float _fact = _monom1->fact + _monom1->next->fact;
				if (fabs(_fact) < 0.00000001)
				{
					Monom* _monom2 = _monom1->next->next;
					_oth.del(_monom1->next->deg, _monom1->fact);
					_oth.del(_monom1->deg, _monom1->fact);
					_monom1 = _monom2;
				}
				else
				{
					_monom1->fact = _fact;
					_oth.del(_monom1->next->deg, _monom1->next->fact);
					_monom1 = _monom1->next;
				}
			}
			else
			{
				_monom1 = _monom1->next;
			}
		}
	}

public:
	Polinom operator + (const Polinom& _oth) const
	{
		Polinom _pol1;
		Monom* _monom1 = head->next;
		Monom* _monom2 = _oth.head->next;

		while (true)
		{
			if (_monom1 == NULL && _monom2 != NULL)
			{
				while (_monom2 != NULL)
				{
					_pol1.insert(_monom2->deg, _monom2->fact);
					_monom2 = _monom2->next;
				}
				break;
			}
			else
			{
				if (_monom1 != NULL && _monom2 == NULL)
				{
					while (_monom1 != NULL)
					{
						_pol1.insert(_monom1->deg, _monom1->fact);
						_monom1 = _monom1->next;
					}
					break;
				}
				else
				{
					if (_monom1->deg >= _monom2->deg)
					{
						while (_monom1 != NULL)
						{
							_pol1.insert(_monom1->deg, _monom1->fact);
							_monom1 = _monom1->next;
						}
					}
					else
					{
						while (_monom2 != NULL)
						{
							_pol1.insert(_monom2->deg, _monom2->fact);
							_monom2 = _monom2->next;
						}
					}
				}
			}
		}
		bringingsimilar(_pol1);
		return _pol1;
	}

	Polinom operator * (float _fact) const
	{
		Polinom _pol1;
		if (fabs(_fact) >= 0.00000001)
		{
			_pol1 = *this;
			Monom* _monom1 = _pol1.head->next;
			while (_monom1 != NULL)
			{
				_monom1->fact = _monom1->fact * _fact;
				_monom1 = _monom1->next;
			}
		}
		return _pol1;
	}

	Polinom operator - (const Polinom& _oth) const
	{
		Polinom pol1;
		pol1 = *this + _oth * (-1.0);
		return pol1;
	}

	Polinom operator * (const Polinom& _oth) const
	{
		Polinom _pol1;
		Monom* _monom1 = head->next;
		Monom* _monom2 = _oth.head->next;
		while (_monom1 != NULL)
		{
			_monom2 = _oth.head->next;
			while (_monom2 != NULL)
			{
				if ((_monom2->deg / 100 + _monom1->deg / 100 > 9)
					|| (_monom2->deg / 10 % 10 + _monom1->deg / 10 % 10 > 9)
					|| (_monom2->deg % 10 + _monom1->deg % 10 > 9))
				{
					throw (string)"Degree > 9";
				}
				_pol1.insert(_monom2->deg + _monom1->deg, _monom2->fact * _monom1->fact);
				_monom2 = _monom2->next;
			}
			_monom1 = _monom1->next;
		}
		bringingsimilar(_pol1);
		return _pol1;
	}

	friend ostream& operator<<(ostream& os, const Polinom& _oth)
	{
		if (_oth.head->next == NULL)
		{
			os << 0;
			return os;
		}
		Monom* _monom1 = _oth.head->next;
		while (_monom1 != NULL)
		{
			if (_monom1->fact > 0)
			{
				os << _monom1->fact;
			}
			else
			{
				os << "(" << _monom1->fact << ")";
			}
			if (_monom1->deg / 100 != 0)
			{
				os << " * x^" << _monom1->deg / 100 << " ";
			}
			if (_monom1->deg / 10 % 10 != 0)
			{
				os << " * y^" << _monom1->deg / 10 % 10 << " ";
			}
			if (_monom1->deg % 10 != 0)
			{
				os << " * z^" << _monom1->deg % 10 << " ";
			}
			if (_monom1->next != NULL)
			{
				os << "+ ";
			}
			_monom1 = _monom1->next;
		}
		return os;
	}

	friend istream& operator>>(istream& is, Polinom& _oth)
	{
		int monom_num;
		cout << "input monom's number:" << endl;
		is >> monom_num;
		cout << endl;
		for (int i = 0; i < monom_num; i++)
		{
			int _deg;
			float _fact;
			cout << "Monom number: " << i + 1 << endl;
			cout << "Input factor: ";
			is >> _fact;
			cout << endl;
			cout << "Input degrees:";
			is >> _deg;
			cout << endl;
			if ((_deg / 100 < 0) || (_deg / 100 > 9)
				|| (_deg / 10 % 10 < 0) || (_deg / 10 % 10 > 9)
				|| (_deg % 10 < 0) || (_deg % 10 > 9))
			{
				throw (string)"incorrect degree";
			}
			if (fabs(_fact) > 0.00000001)
			{
				_oth.insert(_deg, _fact);
			}
		}
		return is;
	}
};

#endif