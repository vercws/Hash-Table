# Hash Table Implementation in C++

This repository contains an implementation of a hash table data structure in C++. Hash tables are widely used for their efficiency in data retrieval operations. This implementation provides functionalities to add elements, delete elements, find elements by their key, and display all elements.

## Features

- **RandomKey()**: Generates a random string key of length 6.
- **RandomNumber(from, to)**: Generates a random number within the specified range.
- **HashTable**: Implements the hash table data structure with dynamic resizing to maintain efficiency.
- **Data Class**: Represents the data stored in the hash table.
- **List Class**: Represents a linked list used for collision resolution in the hash table.
- **Pair Class**: Associates a key with its corresponding value.
- **IfEven Functor**: Defines a functor to check if two values are even.
- **displayMenu()**: Provides a menu-driven interface for interacting with the hash table.
- **main()**: Demonstrates the usage of the implemented hash table by providing a menu for user interaction.

## Usage

To use the hash table implementation, follow these steps:

1. Include the "Header.h" header file in your C++ code.
2. Instantiate a `HashTable` object with the desired data type.
3. Use the provided methods to interact with the hash table, such as adding elements, deleting elements, finding elements, and displaying all elements.

Example usage:
```cpp
HashTable<Data> Htab;
Htab.addNewElement("key1", new Data(10));
Htab.displayAll();
