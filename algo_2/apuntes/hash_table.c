#include <stdlib.h>
#include <stdio.h>

#define INITIAL_SIZE 20

typedef struct kv_pair {
	char* key;
	void* value;
} kv_pair_t;

typedef struct hash_table {
	kv_pair_t* data;
	size_t size;
} hash_table_t;

hash_table_t* hash_table_create(size_t initial_size)
{
	hash_table_t* ht = malloc(sizeof(hash_table_t));

	if (!ht)
		return NULL;

	ht->size = initial_size;
	ht->data = calloc(initial_size, sizeof(kv_pair_t));

	return ht;
}

size_t hash(const char* key)
{
	size_t hash_value = 0;

	while (*key)
		hash_value += *(key++);
	
	return hash_value;
}

hash_table_t* hash_table_insert(hash_table_t* ht, const char* key, void* value)
{
	if (!ht)
		return NULL;

	size_t hash_value = hash(key);
	size_t key_index = hash_value % ht->size;

	kv_pair_t kv_pair = {.key = (char*)key, .value = value};

	ht->data[key_index] = kv_pair;

	return ht;
}

void* hash_table_obtain(hash_table_t* ht, const char* key)
{
	if (!ht)
		return NULL;

	size_t hash_value = hash(key);
	size_t key_index = hash_value % ht->size;

	kv_pair_t kv_pair = ht->data[key_index];

	return kv_pair.value;
}

size_t hash_table_size(hash_table_t* ht)
{
	if (!ht)
		return 0;

	return ht->size;
}

void* hash_table_delete(hash_table_t* ht)
{
	return NULL;
}

void* hash_table_contains(hash_table_t* ht)
{
	return NULL;
}

void hash_table_free(hash_table_t* ht)
{
	if (!ht)
		return;

	free(ht->data);
	free(ht);
}

int main(void)
{
	hash_table_t* ht = hash_table_create(INITIAL_SIZE);

	int item_1 = 10, item_2 = 25;

	ht = hash_table_insert(ht, "first", &item_1);
	ht = hash_table_insert(ht, "second", &item_2);

	int obtained_item_1 = *(int*)hash_table_obtain(ht, "first");
	int obtained_item_2 = *(int*)hash_table_obtain(ht, "second");

	printf("Obtained Item 1: %i\n", obtained_item_1);
	printf("Obtained Item 2: %i\n", obtained_item_2);

	hash_table_free(ht);
	return 0;
}
