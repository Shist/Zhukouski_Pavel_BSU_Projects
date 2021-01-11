#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct DataItem {
    const char* data;
    int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    return key % SIZE;
}

struct DataItem* search(int key) {
    //get the hash 
    int hashIndex = hashCode(key);

    //move in array until an empty 
    while (hashArray[hashIndex] != NULL) {

        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}

void insert(const char* data, int key) {

    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash 
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

int main() {
    dummyItem = (struct DataItem*)malloc(sizeof(struct DataItem));

    //char* Str = { "125.25.1.0" }; //Строка для преобразования
    //int Num = 0;    //Преобразование строки в число типа int
    //for (int i = 0; Str[i] != '\0'; i++)
    //{
    //    Num = atoi(Str);
    //    printf("%d\n", Num);
    //}


    insert("somestr1", 20);
    insert("somestr2", 70);
    insert("somestr3", 80);
    insert("somestr4", 25);
    insert("somestr5", 44);
    insert("somestr6", 32);
    insert("somestr7", 11);
    insert("somestr8", 78);
    insert("somestr9", 97);

    item = search(70);

    if (item != NULL) {
        printf("Element found: %s\n", item->data);
    }
    else {
        printf("Element not found\n");
    }
}