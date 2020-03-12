// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.
#include <vector>
#include <list>
#include <iostream>
#include <functional>
template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

	unsigned int getBucketNumber(const KeyType& key) const;
private:
	struct Node {
		KeyType key;
		ValueType value;
	};

	std::vector<std::list<Node>> m_hashTable;
	int m_nBuckets;
	int m_nUsedBuckets;
	double m_maxLoad;
	
	
	
	//return current load factor
	double calculateLoad() const;
	
	
};

//pg spec. 17
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
	m_nBuckets = 8;
	m_nUsedBuckets = 0;


	m_maxLoad = maximumLoadFactor;
	m_hashTable.resize(8);

}

//does nothing as it doesn't dynamically allocate anything
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap()
{
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset()
{
	m_hashTable.clear();
	m_hashTable.resize(8);
}
template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
    return m_nUsedBuckets;  // Delete this line and implement this function correctly
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	
	
	//check if it still within the loadFactor

	
	
	//first calculate the bucket number
	unsigned int bLoc;
	Node temp = { key, value };
	ValueType* valuePtr = find(key);
	//update if there already exist a key
	if (valuePtr != nullptr) {
		bLoc = getBucketNumber(key);
		*valuePtr = value;
	}
	else{
		//check if adding a new bucket will cause load factor to be too small
		m_nUsedBuckets++;

		if (calculateLoad() > m_maxLoad) {
			//create new hash table
			std::vector<std::list<Node>> tempHashTable(2 * m_nBuckets);
			
			m_nBuckets = 2 * m_nBuckets;

			//rehash everything into the new table
			for (int i = 0; i < m_hashTable.size(); i++) {
				if (!m_hashTable[i].empty()) {
					for (auto it = m_hashTable[i].begin(); it != m_hashTable[i].end(); it++) {
						bLoc = getBucketNumber(it->key);
						tempHashTable[bLoc].push_back(*it);
					}
				}
			}
			m_hashTable = tempHashTable;

		}

		bLoc = getBucketNumber(key);
		m_hashTable[bLoc].push_back(temp);
		
	}


	//std::cerr << "Key: " << key << " Value: " << value << std::endl;
	//std::cerr << "Current Load: " << calculateLoad() << " Current Buckets " << m_hashTable.size() << std::endl;
	//std::cerr << "Current items: " << m_nUsedBuckets << " Bucket Location: " << bLoc <<  std::endl;

}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const
{
	//get the bucket location
	unsigned int bLoc = getBucketNumber(key);

	//check if there is anything inside that bucket
	if (m_hashTable[bLoc].empty()) {
		return nullptr;
	}


	for (auto it = m_hashTable[bLoc].begin(); it != m_hashTable[bLoc].end(); it++) {
		if (it->key == key) {
			return &(it->value);
		}
	}
	
    return nullptr;  
}

template<typename KeyType, typename ValueType>
double ExpandableHashMap<KeyType, ValueType>::calculateLoad() const{
	return static_cast<double>(m_nUsedBuckets) / m_nBuckets;
}

template<typename KeyType, typename ValueType>
unsigned int ExpandableHashMap<KeyType, ValueType>:: getBucketNumber(const KeyType& key) const {
	unsigned int hasher(const KeyType & k);
	unsigned int h = hasher(key);
	return h % m_nBuckets;
}

