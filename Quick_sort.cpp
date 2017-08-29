/*
This is simple quicksort program.

Created By: Vachik Dave
*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> quick_sort(vector<int> input,int first, int last)
{
	int pivot = first;
	vector<int> result,res_left,res_right;
	if(last - first == 1)
	{	result.push_back(input[first]);
		return result;
	}
	else if (last - first == 2)
	{
		if(input[first] > input [first+1])
		{
			result.push_back(input[first+1]);
			result.push_back(input[first]);
		}
		else
		{	
			result.push_back(input[first]);
			result.push_back(input[first+1]);
		}
		return result;
	}
	int i = first+1;	//
	int j = last-1;
	cout << "pivot-" << input[pivot]<<endl;
//	cout << "i" << input[i] << endl;
//	cout << "j" << input[j] << endl;
	
	while(i < j)
	{
		while(input[i] < input[pivot] && i < last)
			i++;
		while(input[j] > input[pivot] && j >= i)
			j--;
		cout << i << "--" << j << "  ";
		if(i<=j)
		{
			//vector<int>:: iterator it = input.begin();
			int temp = input[i];
			input[i] = input[j]; 
			input[j] = temp;
		}
	}
	int temp = input[j];
	input[j] = input[pivot];
	input[pivot] = temp;

	if(first < j)
	{	res_left = quick_sort(input,first,j);
		cout << endl ;	
		for(int i = 0; i < res_left.size(); i++)
		{
			cout << res_left[i] << "  ";
		}	
	
	}
	if(i < last)
	{	res_right = quick_sort(input,i,last);
				cout << endl ;	
		for(int i = 0; i < res_right.size(); i++)
		{
			cout << res_right[i] << "  ";
		}	
	}
	vector<int>::iterator it = res_left.begin();

	if(!res_left.empty())	
	{
		result.insert(result.begin(),it,it+res_left.size());
		
	}
	result.push_back(input[j]);
	if(!res_right.empty())		
	{
		result.insert(result.begin()+result.size(),res_right.begin(),res_right.begin()+res_right.size());


	}
	return result;
}

int main()
{
	vector<int> input,second,result;

	input.push_back(8);
	input.push_back(4);
	input.push_back(14);	
	input.push_back(3);
	input.push_back(12);
	input.push_back(2);	
	input.push_back(9);	
	input.push_back(2);	
	input.push_back(6);	
	input.push_back(16);	

	result = quick_sort(input,0,input.size());
	cout << endl ;	
	for(int i = 0; i < result.size(); i++)
	{
		cout << result[i] << "  ";
	}	
	cout << endl << endl;
	return 0;
}
