#include <iostream>
#include "../Polinom/polinom.h"
#include "../Tables/tables.h"

using namespace std;

int main()
{
	int key_c = 0;
	int D_num;
	NPT table1;
	PT table2;
	HT table3;
	t_str _el;

	while (true)
	{
		cout << "1. Create new Polinom" << endl;
		cout << "2. Find Polinom" << endl;
		cout << "3. Delete Polinom" << endl;
		cout << "4. Operations" << endl;
		cout << ". Exit" << endl;
		cin >> D_num;
		switch (D_num)
		{
		case(1):
		{
			cout << "Rules:" << endl;
			cout << "1. Polinom sum(a(u) * x^i * y^j * z^k)" << endl;
			cout << "2. a(u) - real number" << endl;
			cout << "3. deg(xyz) - integer number, 0 <= deg(xyz) < 1000" << endl;
			cout << "4. Polinom have name (Any 0 to 255)" << endl;
			bool w = true;
			Polinom pol1;
			int k;
			while (w)
			{
				cout << "Input name" << endl;
				cin >> k;

				w = false;
				try
				{
					cin >> pol1;
				}
				catch (string)
				{
					cout << "Incorrect degree" << endl;
					w = true;
				}
				if (w == false)
				{
					break;
				}
			}
			cout << "Polinom: " << pol1 << endl;
			_el.key = k;
			_el.pol = pol1;

			table1.insert(_el);
			table2.insert(_el);
			table3.insert(_el);
			break;
		}
		case(2):
		{
			cout << "Input polinom name" << endl;
			int k;
			cin >> k;

			cout << table1.find(k) << endl;
			cout << table2.find(k) << endl;
			cout << table3.find(k) << endl;
			break;
		}
		case(3):
		{
			cout << "Input polinom name" << endl;
			int u;
			cin >> u;

			table1.del(u);
			table2.del(u);
			table3.del(u);
			break;
		}
		case(4):
		{
			cout << "Input polinom 1 name" << endl;
			int a;
			cin >> a;
			cout << "Input polinom 2 name" << endl;
			int b;
			cin >> b;
			Polinom result;
			int ch;
			int w = true;
			while (w)
			{
				w = false;
				cout << "Choice operation" << endl;
				cout << "1 - (pol_1 + pol_2), 2 - (pol_1 * pol_2), 3 - (pol_1 - pol_2), 4 - (pol_2 - pol_1)" << endl;
				cin >> ch;
				if (ch < 1 || ch > 4)
				{
					cout << "Choice num 1 - 4" << endl;
					w = true;
				}
			}
			try
			{
				if (ch == 1)
				{
					result = table1.find(a) + table1.find(b);
					cout << table1.find(a) + table1.find(b) << endl;
				}
				if (ch == 2)
				{
					result = table1.find(a) * table1.find(b);
					cout << result << endl;
				}
				if (ch == 3)
				{
					result = table1.find(a) - table1.find(b);
					cout << result << endl;
				}
				if (ch == 4)
				{
					result = table1.find(b) - table1.find(a);
					cout << result << endl;
				}
			}
			catch (string)
			{
				cout << "degree > 9" << endl;
			}
			cout << "Save result? 1 - y, 0 - n" << endl;
			int k;
			cin >> k;
			if (k == 1)
			{
				cout << "Input polinom name" << endl;
				int k_1;
				cin >> k_1;
				_el.key = k_1;
				_el.pol = result;
				table1.insert(_el);
				table2.insert(_el);
				table3.insert(_el);
			}
			break;
		}
		default:
			exit(0);
		}
	}
}