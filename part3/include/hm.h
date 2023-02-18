#include "mythread.h"
#include "list.h"
#define SZ 4096

/*! 
    @brief Elements consisting of key and value pairs that are to be stored in the Hashmap.
*/
struct hashmap_element_s {
  char *key;
  void *data;
};

/*! 
    @brief Hashmap consisting of linked lists with locks. 
*/
struct hashmap_s {
  struct list* table[SZ]; ///< Array of linked list pointers
  struct lock* lk[SZ]; ///< Array of lock pointers corresponding to the linked lists of the hashtable
};

/*! 
    @brief Initialises the hashmap.
    @param out_hashmap : The pointer to the hashmap.
*/
int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap

/*! 
    @brief Adds the key value pair to the hashmap.
    @param hashmap : The pointer to the hashmap.
    @param key : Key of the element to be added.
    @param data : Corresponding value of the key.
*/
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

/*! 
    @brief Removes and returns the value corresponding to the key in hashmap.
    @param hashmap : The pointer to the hashmap.
    @param key : Key corresponding to which value is to be found.
    @return Value corresponding to the key in argument (if key exists), NULL otherwise.

    If the key exists in the hashmap then it returns the corresponding value of the key.
    Otherwise, returns NULL.
*/
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);    // Fetch value of a key from hashmap

/*! 
    @brief Executes argument function on each Key Value pair in the hashmap.
    @param hashmap : The pointer to the hashmap.
    @param f : The function which is going to be executed on all of the key value pairs in the hashmap.
*/
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap

/*! 
    @brief Acquire lock on a hashmap slot.
    @param hashmap : The pointer to the hashmap.
    @param key : The key for which the lock has to be set.
*/
int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot

/*! 
    @brief Releases the lock on acquired slot.
    @param hashmap : The pointer to the hashmap.
    @param key : The key for which the lock has to be removed.
*/
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock
