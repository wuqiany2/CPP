#pragma once
#include <allocators>
#include <utility>
#include <memory>
#include <initializer_list>

template <typename T> class Vector {
public:

	//default constructor
	Vector() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	//Vector(initializer_list<T>);
	//copy constructor
	Vector(const Vector<T>&);

	~Vector();

	Vector<T> &operator=(const Vector<T>&); // copy assignment

	//Vector<T> &operator[](size_t pos);
	//const Vector<T> &operator[](size_t pos) const;

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T* begin() const { return elements; }
	T* end() const { return first_free; }

	void push_back(const T&);
	//void pop_back();



private:
	static std::allocator<T> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<T*, T*> alloc_n_copy(const T*, const T*);
	void free();
	void reallocate();
	T* elements;
	T* first_free;
	T* cap;
};


template <typename T>
std::allocator<T> Vector<T>::alloc = std::allocator<T>();
//template<typename T>
//inline Vector<T>::Vector(initializer_list<T> ilist)
//{

//}

template<typename T>
inline Vector<T>::Vector(const Vector<T> &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template<typename T>
inline Vector<T>::~Vector()
{
	free();
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T> &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template<typename T>
inline void Vector<T>::push_back(const T & v)
{
	chk_n_alloc();
	alloc.construct(first_free++, v);
}

template<typename T>
inline std::pair<T*, T*> Vector<T>::alloc_n_copy(const T *b, const T *e)
{
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copty(b, e, data) };
}

template<typename T>
inline void Vector<T>::free()
{
	if (elements) {
		for (auto p = first_free; p != elements; ) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

template<typename T>
inline void Vector<T>::reallocate()
{
	auto newcap = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcap);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcap;
}
