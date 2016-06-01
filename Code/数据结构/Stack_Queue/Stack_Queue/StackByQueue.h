#include<iostream>
#include<queue>
using namespace std;

template<class T>
class StackByQueue
{
public:
	StackByQueue()
	{}

	~StackByQueue()
	{}

	void Push(const T& x)
	{

	}

	void Pop();
	bool Empty();
	size_t Size();
	T& Top();




private:
	std::queue<T> _q1;
	std::queue<T> _q2;

};