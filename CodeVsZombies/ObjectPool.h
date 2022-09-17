#pragma once
#include <list>

/*
 * Объектный пулл: https://habr.com/ru/post/205316/, https://ru.wikipedia.org/wiki/%D0%9E%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D0%BD%D1%8B%D0%B9_%D0%BF%D1%83%D0%BB
 *
 * Порождающий шаблон проектирования, набор готовых к использованию объектов.
 * Когда системе требуется объект, он не создается, а берется из пула.
 * Когда объект больше не нужен, он не уничтожается, а возвращается в пул.
 */

template<class T, unsigned int chunk_size = 1024>
class ObjectPool
{
	std::list<T> buffer;
	std::list<T*> free_ptrs;
public:
	template<typename... Args>
	inline T* get()
	{
		if (free_ptrs.empty())
			CreateObjectsAndFillFreePtrs();

		T* res = free_ptrs.back();
		free_ptrs.pop_back();
		return res;
	}

	template<typename... Args>
	inline T* get(Args&&...args) {
		T* obj = get();
		new (obj) T(args...);
		return obj;
	}

	inline void free(T* obj)
	{
		free_ptrs.push_back(obj);
	}

private:
	void CreateObjectsAndFillFreePtrs();
};

template <class T, unsigned int chunk_size>
void ObjectPool<T, chunk_size>::CreateObjectsAndFillFreePtrs()
{
	for (unsigned int i = 0; i < chunk_size; ++i) {
		buffer.emplace_back();
		free_ptrs.emplace_back(&buffer.back());
	}
}