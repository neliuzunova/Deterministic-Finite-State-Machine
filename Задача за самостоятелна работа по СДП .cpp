#include<iostream>

template <typename T>
struct Node
{
	T data;
	Node<T>* next = nullptr;
};
template <typename T>
Node<T>* reverseFib(Node<T>* node)
{
	int copiedCount = 0;
	T copied[3];
	Node<T>* newList = new Node<T>();
	newList->data = node->data;
	while (node != nullptr)
	{
		if (copiedCount < 3)
		{
			copied[copiedCount] = node->data;
			copiedCount++;
		}
		else
		{
			copied[0] = copied[1];
			copied[1] = copied[2];
			copied[2] = node->data;
		}
		if (copiedCount > 1)
		{
			Node<T>* newNode = new Node<T>();
			newNode->data = node->data;
			newNode->next = newList;
			//newList->next = newNode;
		}
		if (copiedCount == 3)
		{
			if (copied[0] + copied[1] != copied[2])
			{
				return nullptr;
			}
		}
		node = node->next;
	}
	if (copiedCount >= 3)
	{
		return newList;
	}
	else
	{
		return nullptr;
	}
}

template <typename T>
Node<T>* AddNode(Node<T>* prev, T data)
{
	prev->next = new Node<T>();
	prev->next->data = data;
	return prev->next;
}

template <typename T>
void PrintList(Node<T>* start)
{
	while (start->next != nullptr)
	{
		std::cout << start->data << std::endl;
		start = start->next;
	}
}

int main()
{
	Node<int>* start = new Node<int>();
	start->data = 0;
	Node<int>* last = AddNode(start, 1);
	last = AddNode(last, 1);
	last = AddNode(last, 2);
	last = AddNode(last, 3);
	last = AddNode(last, 5);
	last = AddNode(last, 8);
	last = AddNode(last, 13);
	last = AddNode(last, 21);
	last = AddNode(last, 34);
	last = AddNode(last, 55);
	PrintList(reverseFib(start));
	system("pause");
	return 0;
}