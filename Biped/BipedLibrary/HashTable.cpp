#include "Biped\bpd\HashTable.h"

BPD_BEGIN
BPD_TEMPLATE_CLASS HashTable<BPD_TEMPLATE_TYPE>::HashTable(const int size)
	: m_size(size) {
	m_hash = new u_int[size];
	m_values = new BPD_TEMPLATE_TYPE*[size];
	for (int i = 0; i < size; i++) {
		m_hash[i] = NULL;
		m_values[i] = nullptr;
	}
}
BPD_TEMPLATE_CLASS HashTable<BPD_TEMPLATE_TYPE>::HashTable()
	: m_size(0) {
	m_hash = new u_int[0];
	m_values = new BPD_TEMPLATE_TYPE*[0];
}
BPD_TEMPLATE_CLASS HashTable<BPD_TEMPLATE_TYPE>::~HashTable() {
	BPD_SAFE_ARRAY_DELETE(m_hash);
	BPD_SAFE_ARRAY_DELETE(m_values);
}
BPD_TEMPLATE_CLASS void HashTable<BPD_TEMPLATE_TYPE>::SetSize(const int size) {
	BPD_SAFE_ARRAY_DELETE(m_hash);
	BPD_SAFE_ARRAY_DELETE(m_values);
	m_hash = new u_int[size];
	m_values = new BPD_TEMPLATE_TYPE*[size];
	for (int i = 0; i < size; i++) {
		m_hash[i] = NULL;
		m_values[i] = nullptr;
	} m_size = size;
}
BPD_TEMPLATE_CLASS u_int HashTable<BPD_TEMPLATE_TYPE>::add(char * key, T* value) {
	if (m_size == 0) return 0;
	if (m_hash == nullptr || m_values == nullptr) return 0;
	for (int i = 0; i < m_size; i++) {
		if (m_hash[i] == NULL) {
			m_hash[i] = hash(key, BPD_SIZEOF(key));
			if (value != nullptr) m_values[i] = value;
			return m_hash[i];
		}
	} return 0;
}
BPD_TEMPLATE_CLASS u_int HashTable<BPD_TEMPLATE_TYPE>::add(char * key, T value) {
	if (m_size == 0) return 0;
	BPD_TEMPLATE_TYPE* temp = new BPD_TEMPLATE_TYPE;
	*temp = value;
	if (m_hash == nullptr || m_values == nullptr) return 0;
	for (int i = 0; i < m_size; i++) {
		if (m_hash[i] == NULL) {
			m_hash[i] = hash(key, BPD_SIZEOF(key));
			m_values[i] = temp;
			return m_hash[i];
		}
	} return 0;
}
BPD_TEMPLATE_CLASS bool HashTable<BPD_TEMPLATE_TYPE>::remove(char * key) {
	if (m_size == 0) return false;
	for (int i = 0; i < m_size; i++) {
		if (m_hash[i] == hash(key, BPD_SIZEOF(key))) {
			m_hash[i] = NULL;
			m_values[i] = nullptr;
			return true;
		}
	} return false;
}
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE* HashTable<BPD_TEMPLATE_TYPE>::get(char * key) {
	if (m_size == 0) return nullptr;
	for (int i = 0; i < m_size; i++) {
		if (m_hash[i] == hash(key, BPD_SIZEOF(key))) {
			if (m_values[i] == nullptr) return nullptr;
			return m_values[i];
		}
	} return nullptr;
}
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE* HashTable<BPD_TEMPLATE_TYPE>::get(u_int key) {
	if (m_size == 0) return nullptr;
	for (int i = 0; i < m_size; i++) {
		if (m_hash[i] == key) {
			if (m_values[i] == nullptr) return nullptr;
			return m_values[i];
		}
	} return nullptr;
}
BPD_TEMPLATE_CLASS void HashTable<BPD_TEMPLATE_TYPE>::clear() {
	for (int i = 0; i < m_size; i++) {
		m_hash[i] = NULL;
		m_values[i] = nullptr;
	}
}
BPD_TEMPLATE_CLASS u_int HashTable<BPD_TEMPLATE_TYPE>::hash(char * key) {
	u_int hash = 0, x = 0;
	for (u_int i = 0; (int)i < BPD_SIZEOF(key); i++) {
		hash = (hash << 4) + key[i];
		if ((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
			hash &= ~x;
		}
	} return (hash & 0x7FFFFFFF);
}

BPD_TEMPLATE_CLASS u_int HashTable<BPD_TEMPLATE_TYPE>::hash(char * key, int size, u_int seed) {
	u_int hash = seed;
	while (*key)
		hash = fnv1a((unsigned char)*key++, hash);
	return hash;
}

// Fowler-Noll-Vo Hash (FNV1a)
BPD_TEMPLATE_CLASS u_int HashTable<BPD_TEMPLATE_TYPE>::fnv1a(unsigned char oneByte, u_int hash) {
	return (oneByte ^ hash) * m_prime;
}

BPD_TEMPLATE_DEFAULT_P(HashTable)
BPD_END