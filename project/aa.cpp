#include<bits/stdc++.h>
using namespace std;
vector<double>lagrange(vector<double>x, vector<double>y, vector<double>input_x)
{
	vector<double>output_y;
	for (int u = 0; u < input_x.size(); u++)
	{
		double output = 0;
		for (int i = 0; i < x.size(); i++)
		{
			double tmp = y[i];
			for (int j = 0; j < x.size(); j++)
			{
				if (i == j)continue;
				tmp *= (input_x[u] - x[j]) / (x[i] - x[j]);
			}
			output += tmp;
		}
		output_y.push_back(output);
	}
	return output_y;
}
signed main()
{
    cout<<log(10)<<endl;
    vector<double>a;
    vector<double>b;
    vector<double>c;
    a.push_back(8);b.push_back(7.885);
    a.push_back(9);b.push_back(8.652);
    a.push_back(10);b.push_back(9.260);
  
    c.push_back(11);
    c.push_back(12);
    vector<double>ans=lagrange(a,b,c);
    cout<<a[-1];
}