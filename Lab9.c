#include <stdio.h>
#include <stdlib.h>

struct RecordType {
    int id;
    char name;
    int order;
};

struct HashNode {
    struct RecordType data;
    struct HashNode* next;
};

struct HashTable {
    int size;
    struct HashNode** data;
};

// Compute the hash function
int hash(int x) {
    return x % 10;
}

int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;

    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);

        if (*ppData == NULL) {
            printf("Cannot allocate memory");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;

            fscanf(inFile, "%d\n ", &n);
            pRecord->id = n;

            fscanf(inFile, "%c\n ", &c);
            pRecord->name = c;

            fscanf(inFile, "%d\n ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t\n%d %c %d", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

void displayRecordsInHash(struct HashTable* table, int hashSz) {
    int i, j;

    for (i = 0; i < hashSz; i++) {
        printf("Index %d:", i);
      
    
    struct HashNode* curr = table->data[i];
        while (curr != NULL) {
            printf(" -> %d, %c, %d", curr->data.id, curr->data.name, curr->data.order);
            curr = curr->next;
        }

        printf("\n");
    }
}

void insertToTable(struct HashTable* table, struct RecordType data) {
    int loc = hash(data.id);

    struct HashNode* newNode = malloc(sizeof(struct HashNode));
    newNode->data = data;
    newNode->next = NULL;

    if (table->data[loc] == NULL) {
        table->data[loc] = newNode;
    } else {
        struct HashNode* curr = table->data[loc];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

int main(void) {
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    int hashSize = 10;
    
    struct HashTable table;
    table.size = hashSize;
    table.data = malloc(sizeof(struct HashNode*) * hashSize);
    
    if (table.data == NULL) {
        fprintf(stderr, "Insufficient memory to create hash");
        return -1;
    }

    int i;
    for (i = 0; i < hashSize; ++i) {
        table.data[i] = NULL;
    }
for (i = 0; i < recordSz; ++i) {
        insertToTable(&table, pRecords[i]);
    }

    displayRecordsInHash(&table, hashSize);
}
