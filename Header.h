#pragma once
#include <iostream>
#include <string>
#include <list>
#include <random>

std::string RandomKey()
{
	std::string newKey = "123456";
	for (int i = 0; i < 6; i++)
	{
		std::random_device rd;
		std::default_random_engine e{ rd() };
		std::uniform_int_distribution <unsigned> u(97, 122);
		newKey[i] = char(u(e));
	}
	return newKey;
}

int RandomNumber(int from, int to)
{
	std::random_device rd;
	std::default_random_engine e{ rd() };
	std::uniform_int_distribution <unsigned> u(from, to);
	return u(e);
}

class Data
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Data* data)
	{
		os << data->value;
		return os;
	}
	Data(int& v)
	{
		value = v;
	};
	int value;
};



class IfEven
{
public:
	bool operator()(const Data* d1, const Data* d2) const
	{
		if (d1->value == d2->value)
		{
			return true;
		}
		else
			return false;
	}
};


template <typename V>
class Pair
{
	public:
	Pair(const std::string& k, V*& v) : key(k), value(v) {}
	std::string key;
	V* value;

};


template <typename V>
class List
{	

public:
	friend std::ostream& operator<<(std::ostream& os, List<V>* lista)
	{
		typename List<V>::Node* temp = lista->head;
		while (temp != nullptr)
		{
			os << temp->data->key << "-> " << temp->data->value;
			temp = temp->next;
			if (temp != nullptr && lista->size > 1) {
				os << ", ";
			}
		}
		return os;
	}
	class Node
	{
	public:
		Node(Pair<V>*& pair) : data(pair), next(nullptr) {}
		Pair<V>* data;
		Node* next;
		~Node()
		{
			delete data;
		}

	};

	List() : head(nullptr), size(0) {};
	~List() 
	{
		while (head)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		size = 0;
	}	

	Node* head;
	int size;

};


template <typename V>
class HashTable
{	
public:
	HashTable()
	{
		current_size = 0;
		max_size = 10;
		lists = new List<V>*[max_size];
		for (int i = 0; i < max_size; i++)
		{
			lists[i] = nullptr;
		}

	}
	~HashTable()
	{
		deleteAll();
		delete[] lists;
	}
	List<V>& operator[](int index)
	{
		return *lists[index];
	};
	const double a = 0.75; //max space
	int current_size;
	int max_size;
	IfEven even;

	List<V>** lists;

	void deleteAll();
	void addNewElement(std::string key, V*& value);
	Pair<V>* returnElement(std::string key);
	bool deleteElement(std::string key);
	void deleteAllElements();
	void displayAll();
	size_t HashFunction(std::string key);
	void reHashOpertaion();
};

std::string RandomKey();
void displayMenu();

