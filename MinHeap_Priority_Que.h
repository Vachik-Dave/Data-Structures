//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Min Heap ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Author: Vachik Dave
//
// All function are logical modification of MaxHeap of CLRS(Introduction to Algorithms).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <class T>
class MinHeap
{
private:
	// heap is container object where first element is key for Min Heap and second could be any identification
	vector<pair<int,T> > heap;
	// it is used to directly access specific identifier already exist in heap
	map<T,int> index;

	inline int Parent(int i)
	{	return (i-1)/2;}
	inline int Left(int i)
	{	return (2*(i+1) - 1);}
	inline int Right(int i)
	{ 	return 2*(i+1);}
	void Min_Heapify(int i)
	{
		int l = Left(i);
		int r = Right(i);
		int smallest;
		if(l < this->heap.size() && this->heap[l].first < this->heap[i].first)
			smallest = l;
		else
			smallest = i;
		if(r < this->heap.size() && this->heap[r].first < this->heap[smallest].first)
			smallest = r;

		if(smallest != i)
		{
			pair<int,T> temp = this->heap[smallest];
			this->heap[smallest] = this->heap[i];
			this->heap[i] = temp;

			//index change
			this->index[this->heap[smallest].second] = smallest;	
//			Print_here(this->heap[smallest].second);
			this->index[this->heap[i].second] = i;
//			Print_here(this->heap[i].second);

			Min_Heapify(smallest);
		}
	}
	void Build_MinHeap()
	{
		int start = this->heap.size()/2;
		for(int i = start ; i >= 0 ;i--)
		{
			Min_Heapify(i);
		}
	}

public:

	MinHeap(){};
	MinHeap(vector<pair<int,T> > vec)
	{
		for(int i =0; i < vec.size();i++)
		{
			this->heap.push_back(vec[i]);
			this->index[this->heap[i].second] = i;
		}
		Build_MinHeap();
	}
	pair<int,T> Heap_Min()
	{
		return this->heap[0];
	}
	pair<int,T> Heap_Extract_Min()
	{
		pair<int,T> ret;
		if(this->heap.size() == 0)
		{
			cout<<"Error: Heap Underflow: No elements in Heap. Returning empty object." <<endl;
			return ret; 
		}
		ret = this->heap[0];
		this->heap[0] = this->heap[this->heap.size()-1];
		this->heap.pop_back();

		//index change
		this->index.erase(this->index.find(ret.second));
		this->index[this->heap[0].second] = 0;


		Min_Heapify(0);
		return ret;
	}
	void Heap_Decrease_Key(pair<int,T> new_key)
	{
//		Print_here(new_key.second);
		int id = this->index[new_key.second];
		if(this->heap[id].first < new_key.first)
		{
			cout<<"Error: Heap Decrease Key: new key is larger than current key. No change." <<endl;
			cout.flush();
			return;
		}
		// Update as per new key
		this->heap[id].first = new_key.first;

		while(id > 0 && this->heap[Parent(id)].first > this->heap[id].first)
		{
			pair<int,T> temp = this->heap[Parent(id)];
			this->heap[Parent(id)] = this->heap[id];
			this->heap[id] = temp;

			//index change
			this->index[this->heap[Parent(id)].second] = Parent(id);	
			this->index[this->heap[id].second] = id;

			id = Parent(id);
		}
	}
	void Heap_insert(pair<int,T> new_key)
	{
//		if(this->index.find(new_key.second)!= this->index.end())
//		{
//			Print_here(new_key.second);
//			cout << "Error: Insertion: element with the given id already exist"<<endl;
//			Heap_Decrease_Key(new_key);
//		}
		pair<int,T> temp = new_key;
		temp.first = -1;
		this->heap.push_back(new_key);
		this->index[new_key.second] = this->heap.size()-1;
		Heap_Decrease_Key(new_key);
	}
	inline int size()
	{
		return this->heap.size();
	}
	inline bool Is_empty()
	{
		return this->heap.empty();
	}
	inline void Print_here(int i)
	{
		cout << "index[" <<i<<"] = "<< index[i] <<endl;
	}
};


class Priority_Q
{
private:
	MinHeap<int> que;
public:
	inline int size()
	{
		return this->que.size();
	}
	inline bool empty()
	{
		return this->que.Is_empty();
	}
	void push(pair<int,int> p)
	{
		this->que.Heap_insert(p);
	}
	inline pair<int,int> top()
	{
		return this->que.Heap_Min();
	}
	inline pair<int,int> pop()
	{
		return this->que.Heap_Extract_Min();
	}
	inline void change_priority(pair<int,int> p)
	{
		this->que.Heap_Decrease_Key(p);
	}
};
