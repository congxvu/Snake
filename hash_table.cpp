//=================================================================
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*
 Student Name: Khoa Nguyen
 Date: 10/26/2020

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    HashTableEntry* hte = (HashTableEntry*)malloc(sizeof(HashTableEntry)); //allocate space
    hte->key = key; // assign struct's variables
    hte->value = value;
    hte->next = NULL;
    return hte;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key)
{
    unsigned int buckNum = hashTable -> hash(key); //call the hash(key) function to get bucket number
    HashTableEntry *currentNode = hashTable->buckets[buckNum]; //current Node = current bucket number
    while(currentNode != NULL) // if the node is not NULL
    {
      if(key == currentNode -> key)
          return currentNode; // if the keys match, return bucknum
      currentNode = currentNode->next; //if not, go to next bucket
    }
    return currentNode; // return bucknum, will return null if not found.
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
    for (int i = 0; i < (hashTable -> num_buckets); i++) //Go thru all buckets
    {
      if(hashTable -> buckets[i]) // delete all entries if bucket[i] isn't NULL
      {
        HashTableEntry* currentNode = hashTable -> buckets[i];
        HashTableEntry* nextNode = currentNode -> next;

        while(nextNode != NULL)  //if next node isn't null
        {
          free(currentNode -> value); //empty current node
          free(currentNode);
          currentNode = nextNode; //update current node
          nextNode = nextNode -> next;
        }
        
        free(currentNode); // delete the tail
      }
    }
    free(hashTable);     //destroy hashTable
    return;
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value)
{
    int buckNum = hashTable -> hash(key); // get bucket number from key
    
    HashTableEntry *oldNode = findItem(hashTable,key); //call finditem to see if oldNode has a value
    
    if(oldNode != NULL)  //if there is an entry associated with the key, change its value
    {
        void *oldValue = oldNode -> value; // make a copy of existing value
        oldNode -> value = value; //replace it with new value
        return oldValue; //return the old value that was replaced
    }

    HashTableEntry *currentNode = createHashTableEntry(key,value); //else, create new entry
    if(currentNode == NULL) //edge case
        return NULL;

    currentNode -> next = hashTable->buckets[buckNum]; //move current number to the next node of current node
    hashTable->buckets[buckNum] = currentNode; // make the new entry point to the changed head
    return NULL;
}

void* getItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* node = findItem(hashTable,key);
    if(node != NULL) //if the item exists
    {
      return node -> value; //return its value
    }
    return NULL;//otherwise return nukll
}

void* removeItem(HashTable* hashTable, unsigned int key) {

     int buckNum = hashTable -> hash(key); //which bucket?
     HashTableEntry *currentNode = hashTable -> buckets[buckNum]; //get first node of bucket

     if(currentNode != NULL && currentNode -> key == key) //if it isnt null and the keys match
     {
       void* oldValue = currentNode -> value; // get a copy of the value
       hashTable -> buckets[buckNum] = currentNode ->next; //update first node
       free(currentNode); // delete first node's value
       return oldValue; // retrieve old value that was deleted
     }

     while(currentNode != NULL && currentNode -> next != NULL) //if it's not the first node of the bucket
     {
       if((*currentNode).next -> key == key) // check if the keys match
       {
         HashTableEntry* tbr = currentNode -> next; // to be removed value is in next node
         void* oldValue1 = tbr -> value; // make a copy of it
         currentNode -> next = (*currentNode).next -> next;  // move next node of current node to next next node
         free(tbr); //remove value
         return oldValue1; //return removed value
       }
       currentNode = currentNode -> next; //go to next entry
     }
     return NULL; //if entry doesn't exist return null
   }


void deleteItem(HashTable* hashTable, unsigned int key) {

     
     int buckNum = hashTable -> hash(key); //which bucket?
     HashTableEntry *currentNode = hashTable -> buckets[buckNum]; //first node of bucket
     //if (findItem(hashTable,key) == NULL) // if key doesn't exist
       //  return;

     if (currentNode != NULL && currentNode ->key == key)
     {
       hashTable -> buckets[buckNum] = currentNode -> next; // move next node to current node
       free(currentNode -> value); //delete its value
       free(currentNode); // free entry
       return;
     }

     while(currentNode != NULL && currentNode -> next != NULL) //not the first node
     {
       //check if next entry is one to delete
         if((*currentNode).next -> key == key) // check if the keys match
       {
         HashTableEntry* tbd = currentNode -> next; // save a copy of to be deleted value
         currentNode -> next = (*currentNode).next  -> next; // move next node of current node to next next node
         free(tbd -> value); //delete value
         free(tbd); //delete entry
         return;
       }
       currentNode = currentNode -> next; //next entry
     }
}
