#include "mythread.h"
#include "list.h"
#include <stdbool.h>
#define SZ 4096

struct hashmap_element_s {
  char *key;
  void *data;
};

struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};

int hashfn(const char* key)
{
    int val = 0;
    for(int i=0;key[i]!='\0';i++)
    {
        int x = key[i];
        val = (val + x*31)%SZ;
    }
    return val;
}

int hashmap_create(struct hashmap_s *const out_hashmap)
{
    for(int i=0;i<SZ;i++)
    {
        out_hashmap->table[i] = list_new();
    }
    return 0;
};   // Initialize a hashmap

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data)
{
    int hashval = hashfn(key);
    struct hashmap_element_s* e = (struct hashmap_element_s*) malloc(sizeof(struct hashmap_element_s));
    int count = 0;
    while(key[count]!='\0') count++;
    e->key = (char*)malloc((count+1)*sizeof(char));
    for(int i=0;i<count;i++) e->key[i] = key[i];
    e->key[count] = '\0';
    e->data = data;
    list_add(hashmap->table[hashval],e);
    return 0;
};   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

void* hashmap_get(struct hashmap_s *const hashmap, const char* key)
{
    int hashval = hashfn(key);
    struct listentry* it = hashmap->table[hashval]->head;
    while(it!=NULL)
    {
        struct hashmap_element_s* temp = (struct hashmap_element_s*)(it->data);
        if(temp != NULL)
        {
            int i=0;
            while(temp->key[i]!='\0'&&temp->key[i]==key[i]) i++;
            if(temp->key[i] == '\0' && key[i] == '\0')
            { 
                void* data = temp->data;
                list_rm(hashmap->table[hashval],it);
                return data;  
            } 
        }
        it = it->next;
    }
    return NULL;
};    // Fetch value of a key from hashmap

void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const))
{
    for(int i=0;i<SZ;i++)
    {
        int count = 0;
        struct listentry* it = hashmap->table[i]->head;
        while(it!=NULL)
        {
            struct hashmap_element_s* temp = (struct hashmap_element_s*)(it->data);
            if(temp!=NULL){ int t = f(temp);}
            it = it->next;
        }
    }
};  // Execute argument function on each key-value pair in hashmap

int acquire_bucket(struct hashmap_s *const hashmap, const char* key)
{

};   // Acquire lock on a hashmap slot

int release_bucket(struct hashmap_s *const hashmap, const char* key)
{

};   // Release acquired lock
