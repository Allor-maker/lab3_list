#include <iostream>


class List
{
public:
	class Iterator;
private:
	class Node
	{
		friend class List::Iterator;
		friend class List;
		Node* Next;
		int value;
	public:
		Node(int value, Node* next):Next(next),value(value) { };
	};
public:
	class Iterator
	{
	private:
		Node* ptr = nullptr;
	public:
		Iterator() :ptr(0) {}
		Iterator(Node* p) : ptr(p) {}

		int& operator*()
		{
			return ptr->value;
		}
		Node* operator->()
		{
			return ptr;
		}

		Iterator& operator++()
		{
			if(ptr)ptr = ptr->Next;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator cp = *this;
			if (ptr) ptr = ptr->Next;
			return cp;
		}
		Iterator operator+(int j) const
		{	
			Node* curr = ptr;
			while (curr && j > 0)
			{
				curr = curr->Next;
				j--;
			}
			if (j > 0)
			{
				throw 0;
			}
			return Iterator(curr);
		}
		bool operator==(const Iterator& it) const
		{
			return (ptr == it.ptr);
		}
		bool operator!=(const Iterator& it) const
		{
			return (ptr != it.ptr);
		}
	};
	public:
	Iterator begin()
	{
		return Iterator(first);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}

	Node* first = nullptr;

	List(int n = 0)
	{
		if (n < 0) throw 0;
		while(n--)
		{
			Node* temp = new Node(0, first);
			first = temp;
		}
	}
	~List()
	{
		Node* curr;
		while (first != nullptr)
		{
			curr = first->Next;
			delete first;
			first = curr;
		}
	}
	List(const List& other)
	{
		Node* curr1 = other.first;
		Node* curr2 = new Node(curr1->value, nullptr);
		first = curr2;
		while (curr1)
		{
			Node* next1 = curr1->Next;
			if (!next1) break;
			curr2->Next = new Node(next1->value, nullptr);
			curr2 = curr2->Next;
			curr1 = curr1->Next;
		}
	}
	void print()
	{
		Node* tmp = first;
		while (tmp)
		{
			std::cout << tmp->value;
			tmp = tmp->Next;
		}
		std::cout << std::endl;
	}
	size_t size() const
	{
		size_t sz = 0;
		Node* curr = first;
		while (curr)
		{
			sz++;
			curr = curr->Next;
		}
		return sz;
	}
	List(List&& other)
	{
		this->first = other.first;
		other.first = nullptr;
	}
	int& operator[](int i)
	{
		if (i < 0)
		{
			throw 0;
		}
		Node* curr = first;
		int count = 0;
		while (curr != nullptr)
		{
			if (count == i)
				return curr->value;
			curr = curr->Next;
			count++;
		}
		throw 0;
	}
	Node* operator[](Iterator it)
	{
		Node* curr = first;
		Iterator it2 = begin();
		while (curr != nullptr)
		{
			if (it2 == it)
				return curr;
			curr = curr->Next;
			it2++;
		}
		throw 0;
	}
	Node* insert_after(int data,Node* prev)
	{
		
		Node* tmp = new Node(data, nullptr);
		tmp->Next = prev->Next;
		prev->Next = tmp;
		return tmp;
	}
	Node* insert_front(int data)
	{
		return(first = new Node(data, first));
	}
	void erase_after(Node* prev)
	{
		if (prev == nullptr) return;
		Node* tmp = prev->Next;
		if (tmp)
		{
			prev->Next = prev->Next->Next;
			delete tmp;
		}
	}
	void erase_front()
	{
		if (first == nullptr)
			return;
		Node* tmp = first;
		first = first->Next;
		delete tmp;
	}
	Iterator find(int value)
	{
		Node* curr = first;
		while (curr)
		{
			if (curr->value == value)
				return Iterator(curr);
			curr = curr->Next;
		}
		return end();
	}
};