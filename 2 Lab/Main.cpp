#include "StaticMultiset.h"

using namespace std;


void main()
{
	StaticMultiset<float> set;
	set.AddNum(15);
	set.AddNum(16);
	set.AddNum(17);
	cout << set.GetAvg() << "\n";
	cout << set.GetMax() << "\n";
	cout << set.GetMin() << "\n";
	cout << set.GetCountAbove(15.9) << "\n";
	cout << set.GetCountUnder(15.9) << "\n";
	set.AddNum(19.8);
	set.AddNum(17.6);
	set.AddNum(15.4);
	cout << set.GetAvg() << "\n";
	cout << set.GetMax() << "\n";
	cout << set.GetMin() << "\n";
	cout << set.GetCountAbove(15.9) << "\n";
	cout << set.GetCountUnder(15.9) << "\n";
	system("pause");
}
