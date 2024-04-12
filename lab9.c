#include <stdio.h>
#include <stdlib.h>

int hashSize = 100;
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct Node *head; // Array of linked lists
};

// Define the node for linked list in separate chaining
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// Compute the hash function
int hash(int x)
{
 	return x % hashSize;
}


// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
			ppData[i] = pRecord;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	printf("\nHash Table:\n");
    for (int i = 0; i < hashSz; ++i)
    {	
        struct Node *current = pHashArray[i].head;

		if(current!=NULL)
			printf("\nIndex %d", i);

        while (current != NULL)
        {
            printf(" -> (%d, %c, %d)", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
    }
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	hashSize = recordSz;
	printRecords(pRecords, recordSz);
	// Your hash implementation

	// Initialize hash table
    struct HashType* hashTable = (struct HashType*) malloc(sizeof(struct HashType) * recordSz);
    for (int i = 0; i < recordSz; ++i)
    {
        hashTable[i].head = NULL;
    }

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = pRecords[i];
        newNode->next = hashTable[index].head;
        hashTable[index].head = newNode;
    }

	// Print records in hash table
    displayRecordsInHash(hashTable, recordSz);
}