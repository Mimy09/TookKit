#include "Biped\bpd\ObjectPool.h"

BPD_BEGIN
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE* ObjectPool<BPD_TEMPLATE_TYPE>::ReturnObject(T Object){
	int id = CheckObject(Object);
	if(id == -1){
		AddObject(Object);
		return &m_pool[CheckObject(Object)];
	} else{ return &m_pool[id]; }
}
BPD_TEMPLATE_CLASS BPD_TEMPLATE_TYPE* ObjectPool<BPD_TEMPLATE_TYPE>::ReturnObjectIndex(int index){
	return &m_pool[index];
}
BPD_TEMPLATE_CLASS void ObjectPool<BPD_TEMPLATE_TYPE>::AddObject(T Object){
	if(CheckObject(Object) == -1){
		m_pool.push_back(Object);
	}
}
BPD_TEMPLATE_CLASS void ObjectPool<BPD_TEMPLATE_TYPE>::RemoveObejct(T Object){
	int id = CheckObject(Object);
	if(id != -1){
		m_pool.erase(id);
	}
}
BPD_TEMPLATE_CLASS int ObjectPool<BPD_TEMPLATE_TYPE>::CheckObject(T Object){
	for(int i = 0; i < m_pool.size(); i++){
		if(m_pool[i] == Object) return i;
	} return -1;
}
BPD_TEMPLATE_DEFAULT_P(ObjectPool)
BPD_END