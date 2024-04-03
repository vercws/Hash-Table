#include <iostream>
#include <cassert>
#include <random>
#include <string>

#include "Header.h"


template <typename V>
size_t HashTable<V>::HashFunction(std::string key)
{
    assert(!key.empty());
    size_t h = 0;
    size_t q = key.length();
    for (size_t i = 0; i < q; i++)
    {
        h += key[i] * pow(31, q - 1 - i);
    }
    return (h % max_size);
}

template <typename V>
Pair<V>* HashTable<V>::returnElement(std::string key)
{
    size_t hash = HashFunction(key);

    if (lists[hash] != nullptr)
    {
        typename List<V>::Node* current = lists[hash]->head;

        while (current != nullptr)
        {
            if (current->data->key == key) return current->data;
            current = current->next;
        }
    }

    return nullptr;
}

template <typename V>
void HashTable<V>::deleteAllElements()
{
    deleteAll();
}

template <typename V>
void HashTable<V>::reHashOpertaion()
{
    int oldMaxSize = max_size;
    int oldCurrentSize = current_size;
    List<V>** oldLists = lists;

    max_size = 2 * oldMaxSize; 
    current_size = 0;
    lists = new List<V>*[max_size];

    for (int i = 0; i < max_size; i++)
    {
        lists[i] = nullptr;
    }

    for (int i = 0; i < oldMaxSize; i++)
    {
        if (oldLists[i] != nullptr)
        {
            typename List<V>::Node* temp = oldLists[i]->head; //temp to go through the elements of the oldList[i]
            while (temp != nullptr)
            {
                size_t newIndex = HashFunction(temp->data->key);

                if (lists[newIndex] == nullptr)
                {
                    List<V>* newList = new List<V>(); 
                    
                    
                    newList->head = temp;
                    temp = temp->next;
                    newList->head->next = nullptr;
                    newList->size = 1;
                    lists[newIndex] = newList;

                }
                else // When there is collision (there is already a list at the generated index)
                {
                    typename List<V>::Node* current = lists[newIndex]->head; // currenet to go through the elements of lists[newIndex]
                    while (current != nullptr)
                    {
                        if (current->data->key == temp->data->key) // if the keys are the same, change value
                        {
                            current->data->value = temp->data->value;
                            delete temp; 
                            temp = nullptr;
                            break;
                        }
                        if (current->next == nullptr)// if that's the last element of the list
                        {
                            Pair<V>* nPair = new Pair<V>(temp->data->key, temp->data->value);
                            typename List<V>::Node* Nnode = new typename List<V>::Node(nPair);
                            current->next = Nnode;
                            current->next->next = nullptr;
                            lists[newIndex]->size++; 
                            typename List<V>::Node* nextNode = temp->next;
                            temp = nullptr;
                            temp = nextNode;
                            break;

                        }
                        current = current->next;
                    }
                }

                
            }
        }
    }

    current_size = oldCurrentSize;
    delete[] oldLists;
}


template <typename V>
void HashTable<V>::addNewElement(std::string key, V*& value)
{
    
    if (current_size + 1 < a * max_size)
    {
        Pair<V>* newElement = new Pair<V>(key, value); // making a new pair
        typename List<V>::Node* newNode = new typename List<V>::Node(newElement); // making a new element
        size_t hash = HashFunction(key); // generating index

        // If the index is available
        if (lists[hash] == nullptr)
        {
            List<V>* newList = new List<V>(); // Creating a new list with only one element - pair(key, value)
            newList->head = newNode;
            newList->size++;
            lists[hash] = newList;            
          
        }
        else // When there is collision (there is already a list at the generated index)
        {
            typename List<V>::Node* current = lists[hash]->head; 
            while (current != nullptr)
            {
                if (current->data->key == newElement->key) // if the keys are the same, change value
                {
                    current->data->value = newElement->value;
                    delete current;
                    return;
                }
                if (current->next == nullptr) // if that's the last element of the list
                {
                    current->next = newNode;
                    lists[hash]->size++;
                    current_size++;
                    current = nullptr;
                    return;

                }
                current = current->next;
            }
        }
        current_size++;
    }
    else
    {   
        reHashOpertaion();

        Pair<V>* newElement = new Pair<V>(key, value); // making a new pair
        typename List<V>::Node* newNode = new typename List<V>::Node(newElement); // making a new element
        size_t hash = HashFunction(key); // generating index

        // If the index is available
        if (lists[hash] == nullptr)
        {
            List<V>* newList = new List<V>(); // Creating a new list with only one element - pair(key, value)
            newList->head = newNode;
            newList->size++;
            lists[hash] = newList;

        }
        // When there is collision (there is already a list at the generated index)
        else 
        {
            typename List<V>::Node* current = lists[hash]->head;
            while (current != nullptr)
            {
                if (current->data->key == newElement->key) // if the keys are the same, change value
                {
                    current->data->value = newElement->value;
                    delete current;
                    return;
                }
                if (current->next == nullptr) // if that's the last element of the list
                {
                    current->next = newNode;
                    lists[hash]->size++;
                    current_size++;
                    current = nullptr;
                    return;

                }
                current = current->next;
            }
        }
        current_size++;
    }
}
template <typename V>
void HashTable<V>::deleteAll()
{
    for (size_t i = 0; i < max_size; ++i)
    {
        if (lists[i] != nullptr)
        {
            delete lists[i];
            lists[i] = nullptr;
        }
    }
    current_size = 0;
}

template <typename V>
bool HashTable<V>::deleteElement(std::string key)
{
    size_t hash = HashFunction(key);

    if (lists[hash] != nullptr)
    {
        typename List<V>::Node* current = lists[hash]->head;
        typename List<V>::Node* previous = nullptr;

        while (current != nullptr)
        {
            if (current->data->key == key)
            {
                if (current == lists[hash]->head && lists[hash]->size == 1)
                {
                    delete current;
                    lists[hash] = nullptr;
                    current_size--;
                    return true;
                }
                else if (current == lists[hash]->head && lists[hash]->size > 1)
                {
                    lists[hash]->head = current->next;
                    delete current;
                    lists[hash]->size--;
                    current_size--;
                    return true;
                }
                else if (current->next != nullptr)
                {
                    if (previous != nullptr)
                    { 
                        previous->next = current->next;
                        delete current;
                        lists[hash]->size--;
                        current_size--;
                        return true;

                    }
                    else
                    {
                        return false;
                    }
                }
                else if (current->next == nullptr) // deleting tail
                {
                    if (previous != nullptr)
                    {
                        delete current;
                        previous->next = nullptr;
                        lists[hash]->size--;
                        current_size--;
                        return true;
                    }
                    else
                    {
                        return false;
                    }

                }
            }
            previous = current;
            current = current->next;
        }
    }
    return false;
}

template <typename V>
void HashTable<V>::displayAll()
{
    std::cout << "Current size: " << current_size << std::endl;
    std::cout << "Maximum size (without rehashing): " << max_size << std::endl << std::endl;
    std::cout << "Hash table: " << std::endl;
    int biggestList = 0;
    int nullListsCounter = 0;
    for (size_t i = 0; i < max_size; i++)
    {
        if (lists[i] != nullptr)
        {
            std::cout << "Index " << i << ": " << *&lists[i] << std::endl;
        }
        else 
        {
            nullListsCounter++;
        }
        if (lists[i] != nullptr && lists[i]->size > biggestList)
        {
            biggestList = lists[i]->size;
        }
    }
    std::cout << "\n\n Stats: " << std::endl;
    if (current_size > 0) std::cout << "    Lists min size: 1" << std::endl;
    else std::cout << "    Lists min size: 0" << std::endl;
    std::cout << "    Lists max size: " << biggestList << std::endl;
    std::cout << "    Null lists: " << nullListsCounter << std::endl << std::endl;
}

void displayMenu()
{
    HashTable<Data> Htab;

    clock_t t1 = clock();
    for (int i = 0; i < 20; i++)
    {
        int envalue = RandomNumber(0, 10);
        //char echaracter = RandomNumber(33, 126);
        Data* enewData = new Data(envalue);
        std::string eKey = RandomKey();
        Htab.addNewElement(eKey, enewData);
    }
   

    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "\n" << time << "\n\n";
    bool showMenu = true;
    int choice = 0;

    do
    {

        std::cout << "----------Menu----------\n\n";
        std::cout << "1. Add a new elements\n";
        std::cout << "2. Delete all elements\n";
        std::cout << "3. Find the element using its key\n";
        std::cout << "4. Display all elements\n";
        std::cout << "5. Delete the element using its key\n";
        std::cout << "6. Close the program\n";

        std::cout << " \n\n";
        std::cout << "Choose the option: ";
        std::cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
        {
            int envalue = RandomNumber(0, 10000000);
            char echaracter = RandomNumber(33, 126);
            Data* enewData = new Data(envalue);
            std::string eKey = RandomKey();
            Htab.addNewElement(eKey, enewData);
        }
            break;
        case 2:
            Htab.deleteAll();
            break;
        case 3:
        {
            std::string enKey;
            std::cout << "Enter the key of the element you want to find: ";
            std::cin >> enKey;
            Pair<Data>* foundPair = Htab.returnElement(enKey);
            if (foundPair == nullptr)
            {
                std::cout << "No such element\n " << std::endl;
            }
            else
            {
                std::cout << "Value at key "<< enKey << " is " << Htab.returnElement(enKey)->value << std::endl;
            }
            break;
        }
        case 4:
            Htab.displayAll();
            break;
        case 5:
        {
            std::string enKey;
            std::cout << "Enter the key of the element you want to delete: ";
            std::cin >> enKey;
            bool wynik = Htab.deleteElement(enKey);
            if (wynik)
            {
                std::cout << "Element deleted" << std::endl;
            }
            else
            {
                std::cout << "Error while deleting " << std::endl;
            }
            break;
        }
        case 6:
            showMenu = false;
            break;
        default:
            std::cout << "Error!\n\n";
        }
    } while (showMenu);
}


int main()
{
    setlocale(LC_ALL, "");
    displayMenu();
    return 0;
}

