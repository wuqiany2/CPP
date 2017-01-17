#pragma once
#include <allocators>
#include <utility>
#include <memory>
#include <initializer_list>

template <typename T> class Vector {
public:
	typedef T value_type;

	//default constructor
	Vector() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	Vector(std::initializer_list<T> il) : elements(nullptr), first_free(nullptr), cap(nullptr) 
	{
		for (auto x : il) {
			this->push_back(x);
		}
	};
	//copy constructor
	Vector(const Vector<T>&);

	~Vector();

	Vector<T> &operator=(const Vector<T>&); // copy assignment
	//Vector<T> &operator=(Vector<T>&&); //move assignment

	T &operator[](size_t pos);
	const T &operator[](size_t pos) const;

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T* begin() const { return elements; }
	T* end() const { return first_free; }

	void push_back(const T&);
	T pop_back();



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

//define the static member allocator
template <typename T>
std::allocator<T> Vector<T>::alloc = std::allocator<T>();

//copy constructor
template<typename T>
inline Vector<T>::Vector(const Vector<T> &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

//destructor
template<typename T>
inline Vector<T>::~Vector()
{
	free();
}

//copy assignment
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
inline T & Vector<T>::operator[](size_t pos)
{
	if (pos >= size()) throw std::out_of_range("position out of range!");

	return *(elements + pos);
}

template<typename T>
inline const T & Vector<T>::operator[](size_t pos) const
{
	if (pos >= size()) throw std::out_of_range("position out of range!");

	return *(elements + pos);
}

//push_back
template<typename T>
inline void Vector<T>::push_back(const T & v)
{
	chk_n_alloc();
	alloc.construct(first_free++, v);
}

template<typename T>
inline T Vector<T>::pop_back()
{
	if (!size()) throw std::out_of_range("popping elements from empty vector");
	auto ret = *(--first_free);
	alloc.destroy(first_free);
	return ret;
}


template<typename T>
inline std::pair<T*, T*> Vector<T>::alloc_n_copy(const T *b, const T *e)
{
	auto data = alloc.allocate(e - b);
	return{ data, uninitialized_copy(b, e, data) };
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
