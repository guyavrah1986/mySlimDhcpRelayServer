// ============================================================================
// ============================================================================
// Hash table:
// -----------
// This header file defines the API for the hash table library. Be it a user
// implmeneted one in C (for example) or just using the std::unordered_map
// of C++.
// The idea here is that the header file is common and the source file(s) are
// per implementation.
//
// 1) The API is as follows:
//     - hashTableInit() - initialize the hash table
//     - hashTableSet() - set a value in the hash table
//     - hashTableGet() - get a value from the hash table
//     - hashTableRemove() - remove a value from the hash table
//     - hashTableClear() - clear the hash table
//
// 2) Desgin considerations:
//     - The hash table is implemented as an array of hashTableEntry
//     - The hash table has a fixed capacity
//     - The hash table is not resizable
//     - The hash table is not thread safe
//     - The hash table is not re-entrant
//     - The hash table is not thread safe
//     - The hash table is allocated in an address given by the caller

// ============================================================================
// ============================================================================
#pragma once    

#define IN
#define OUT
#define INOUT

// Hash table entry
typedef struct
{
    const char* key;
    void* value;
} hashTableEntry;

// Hash table
typedef struct 
{
    hashTableEntry* entries;     // hash slots
    size_t capacity;            // size of _entries array
    size_t length;             // number of items in hash table
} hashTable;

// Initializes the hash table with the specified max capacity.
void* hashTableInit(IN const size_t capacity);

// Sets a value in the hash table
// Returns 0 on success and -1 on failure to insert the value
int hashTableSet(IN void* hashTable, IN const void* key, IN const void* value);

// Gets a value from the hash table
// Returns 0 on success and -1 on failure to get the value
int hashTableGet(IN void* hashTable, IN const void* key, OUT void** value);

// Removes a value from the hash table
// Returns 0 on success and -1 on failure to remove the value
int hashTableRemove(IN void* hashTable, IN const void* key);

// Clears the hash table
void hashTableClear(IN void* hashTable);
