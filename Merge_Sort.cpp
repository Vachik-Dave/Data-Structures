/*
This is simple mergesort program where, first split is done in main().

Created By: Vachik Dave
*/

#include <iostream>
#include <vector>
//#include <algorithm>
#include <math.h>
using namespace std;

vector<int> get_vector(vector<int> old, int start,int end)
{
	vector<int> result;
	for(int i= start;i<end;i++)
	{
		result.push_back(old[i]);
	}
	return result;
}

vector<int> merge(vector<int>one, vector<int> two)
{
	vector<int> result;
	int i =0,j=0;

	while(i < one.size() && j<two.size())
	{
		if(one[i] <= two[j])
		{
			result.push_back(one[i]);
			i++;
		}
		else
		{
			result.push_back(two[j]);
			j++;
		}
	}
	while(i < one.size())
	{
		result.push_back(one[i]);
		i++;
	}
	while(j < two.size())
	{
		result.push_back(two[j]);
		j++;
	}
	return result;
}

vector<int> merge_sort(vector<int> one,vector<int> two)
{
	int len1 = one.size();
	int len2 = two.size();
	vector<int> result_one;
	vector<int> result_two;
	if(len1 > 2)
	{
		double t1 =  ceil((double)len1/2.0);
		vector<int> new_one = get_vector(one,0,t1);
		vector<int> new_two = get_vector(one,t1,len1);
		result_one = merge_sort(new_one,new_two);
	}
	else
	{
		if(one[0] > one[1])
		{
			result_one.push_back(one[1]);
			result_one.push_back(one[0]);
		}
		else
		{
			result_one.push_back(one[0]);
			result_one.push_back(one[1]);
		}
	}
	if(len2 > 2)
	{
		int t1 = ceil((double)len2/2.0);
		vector<int> new_one = get_vector(two,0,t1);
		vector<int> new_two = get_vector(two,t1,len1);
		result_two = merge_sort(new_one,new_two);
	}
	else if(len2 == 2)
	{
		if(two[0] > two[1])
		{
			result_two.push_back(two[1]);
			result_two.push_back(two[0]);
		}
		else
		{
			result_two.push_back(two[0]);
			result_two.push_back(two[1]);
		}
	}
	else
		result_two.push_back(two[0]);

	return merge(result_one,result_two);
}

int main()
{
	
	vector<int> first,second,result;

	first.push_back(8);
	first.push_back(4);
	first.push_back(3);
	first.push_back(14);
	first.push_back(12);

	second.push_back(2);	
	second.push_back(9);	
	second.push_back(2);	
	second.push_back(6);	
	second.push_back(16);	

	result = merge_sort(first,second);
	cout << endl ;	
	for(int i = 0; i < result.size(); i++)
	{
		cout << result[i] << "  ";
	}	
	cout << endl << endl;
	return 0;
}
