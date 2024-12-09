#ifndef EXAMCPP_VLVECTOR_HPP
#define EXAMCPP_VLVECTOR_HPP

#include <exception>
#include <iterator>
#include <vector>

#define STATIC_CAPACITY 16

/**
 * this class represents the Virtual Length Vector class.
 * @tparam T the Type of the elements in the vector.
 * @tparam C the initial capacity of the vector.
 */
template<class T, size_t C = STATIC_CAPACITY>
class VLVector
{
public:
	/**
	 * this class represents the VLVector's Iterator.
	 */
	class Iterator
	{
		T *_cur;
	public:
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef int difference_type;
		typedef std::random_access_iterator_tag iterator_category;

		explicit Iterator(value_type *value) : _cur(value)
		{}

		Iterator(const Iterator &other) : _cur(other._cur)
		{}

		~Iterator()
		= default;

		Iterator &operator=(const Iterator &other)
		{
			if (this == &other)
			{
				return *this;
			}
			_cur = other._cur;
			return *this;
		}

		reference operator*() const
		{
			return *_cur;
		}

		Iterator &operator++()
		{
			++_cur;
			return *this;
		}

		const Iterator operator++(int)
		{
			Iterator temp(*this);
			++_cur;
			return temp;
		}

		Iterator &operator--()
		{
			--_cur;
			return *this;
		}

		const Iterator operator--(int)
		{
			Iterator temp = *this;
			--_cur;
			return temp;
		}

		Iterator &operator+=(difference_type rhs)
		{
			_cur += rhs;
			return *this;
		}

		Iterator &operator-=(difference_type rhs)
		{
			_cur -= rhs;
			return *this;
		}

		pointer operator->() const
		{
			return _cur;
		}

		reference operator[](difference_type rhs) const
		{
			return _cur[rhs];
		}

		difference_type operator-(const Iterator &rhs) const
		{
			return (difference_type) (_cur - rhs._cur);
		}

		Iterator operator+(difference_type rhs) const
		{
			return Iterator(_cur + rhs);
		}

		Iterator operator-(difference_type rhs) const
		{
			return Iterator(_cur - rhs);
		}

		friend Iterator operator-(difference_type lhs, const Iterator &rhs)
		{
			return Iterator(lhs - rhs._cur);
		}

		friend Iterator operator+(difference_type lhs, const Iterator &rhs)
		{
			return Iterator(lhs + rhs._cur);
		}

		bool operator==(const Iterator &other) const
		{
			return this->_cur == other._cur;
		}

		bool operator!=(const Iterator &other) const
		{
			return this->_cur != other._cur;
		}

		bool operator>(const Iterator &rhs) const
		{
			return _cur > rhs._cur;
		}

		bool operator<(const Iterator &rhs) const
		{
			return _cur < rhs._cur;
		}

		bool operator>=(const Iterator &rhs) const
		{
			return _cur >= rhs._cur;
		}

		bool operator<=(const Iterator &rhs) const
		{
			return _cur <= rhs._cur;
		}
	};

	/**
	 * this class represents the VLVector's const Iterator.
	 */
	class ConstIterator
	{
		const T *_cur;
	public:
		typedef T value_type;
		typedef const T &reference;
		typedef const T *pointer;
		typedef int difference_type;
		typedef std::random_access_iterator_tag iterator_category;

		explicit ConstIterator(const T *value) : _cur(value)
		{}

		ConstIterator(ConstIterator &other) : _cur(other._cur)
		{}

		~ConstIterator()
		= default;

		ConstIterator &operator=(const ConstIterator &other)
		{
			if (this == &other)
			{
				return *this;
			}
			_cur = other._cur;
			return *this;
		}

		value_type operator*() const
		{
			return *_cur;
		}

		ConstIterator &operator++()
		{
			++_cur;
			return *this;
		}

		const ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			++_cur;
			return temp;
		}

		ConstIterator &operator--()
		{
			--_cur;
			return *this;
		}

		const ConstIterator operator--(int)
		{
			ConstIterator temp = *this;
			--_cur;
			return temp;
		}

		ConstIterator &operator+=(difference_type rhs)
		{
			_cur += rhs;
			return *this;
		}

		ConstIterator &operator-=(difference_type rhs)
		{
			_cur -= rhs;
			return *this;
		}

		pointer operator->() const
		{
			return _cur;
		}

		reference operator[](difference_type rhs) const
		{
			return _cur[rhs];
		}

		difference_type operator-(const ConstIterator &rhs) const
		{
			return (difference_type) (_cur - rhs._cur);
		}

		ConstIterator operator+(difference_type rhs) const
		{
			return ConstIterator(_cur + rhs);
		}

		ConstIterator operator-(difference_type rhs) const
		{
			return ConstIterator(_cur - rhs);
		}

		friend ConstIterator operator-(difference_type lhs, const ConstIterator &rhs)
		{
			return ConstIterator(lhs - rhs._cur);
		}

		friend ConstIterator operator+(difference_type lhs, const ConstIterator &rhs)
		{
			return ConstIterator(lhs + rhs._cur);
		}

		bool operator==(const ConstIterator &other) const
		{
			return this->_cur == other._cur;
		}

		bool operator!=(const ConstIterator &other) const
		{
			return this->_cur != other._cur;
		}

		bool operator>(const ConstIterator &rhs) const
		{
			return _cur > rhs._cur;
		}

		bool operator<(const ConstIterator &rhs) const
		{
			return _cur < rhs._cur;
		}

		bool operator>=(const ConstIterator &rhs) const
		{
			return _cur >= rhs._cur;
		}

		bool operator<=(const ConstIterator &rhs) const
		{
			return _cur <= rhs._cur;
		}
	};

private:
	typedef Iterator iterator;
	typedef ConstIterator const_iterator;
	T _stackVector[C];
	T *_heapVector;
	size_t _size = 0;
	size_t _capacity = C;

	/**
	 * this function gives the new size after adding values.
	 * @param size the size the new capacity.
	 * @param n the number of the values to add.
	 */
	void _getNewSize(size_t *size, int n)
	{
		while ((this->_size + n) > this->_capacity)
		{
			(*size) = _capC(this->_size);
			--n;
		}
		this->_capacity = (*size);
	}

	/**
	 * this function calculates the new capacity by the given formula in the pdf.
	 * @param size the size to help in calculation.
	 * @return the new capacity.
	 */
	size_t _capC(size_t size)
	{
		return (3 * (size + 1)) / 2;
	}

	/**
	 * this function resize the given vector.
	 * @param vector the vector to resize.
	 * @param size the size to help in calculation.
	 */
	void _resizeVector(T *vector, size_t size)
	{
		T *temp = new(std::nothrow) T[size];
		std::copy(vector, vector + this->_size, temp);
		vector = new(std::nothrow) T[size];
		std::copy(temp, temp + this->_size, vector);
		delete[] temp;
	}

public:
	/**
	 * the default Constructor.
	 */
	VLVector() : _stackVector(), _heapVector()
	{}

	/**
	 * the copy constructor.
	 * @param other the other object to copy.
	 */
	VLVector(const VLVector &other) : VLVector()
	{
		this->operator=(other);
	}

	/**
	 * constructor that adds all the given range to the current vector.
	 * @tparam InputIterator the type of the given iterators.
	 * @param first the first iterator.
	 * @param last the last iterator.
	 */
	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last):_stackVector(), _heapVector()
	{
		for (auto it = first; it != last; it++)
		{
			this->push_back(*it);
		}
	}

	/**
	 * the destructor.
	 */
	~VLVector()
	{
		if (this->_capacity > C && this->_heapVector != nullptr)
		{
			delete[] this->_heapVector;
		}
	}

	/**
	 * this function returns the current number of elements in the vector.
	 * @return the current number of elements in the vector.
	 */
	size_t size() const noexcept
	{
		return this->_size;
	}

	/**
	 * the current capacity.
	 * @return the current capacity.
	 */
	size_t capacity() const noexcept
	{
		return this->_capacity;
	}

	/**
	 * this function checks if the current vector is empty or not.
	 * @return true if it is empty, false otherwise.
	 */
	bool empty() const noexcept
	{
		return this->_size == 0;
	}

	/**
	 * this function returns the element in the given index.
	 * @param i the index.
	 * @return the element in the given index.
	 */
	T &at(int i)
	{
		if (i > (int) this->_size || i < 0)
		{
			throw std::out_of_range("index out of range");
		}
		return (*this)[i];
	}

	/**
	 * this function returns the element in the given index.
	 * @param i the index.
	 * @return the element in the given index.
	 */
	const T &at(int i) const
	{
		return at(i);
	}

	/**
	 * this function adds the given element to the end of the vector.
	 * @param value the value to add.
	 */
	void push_back(const T &value)
	{
		if (this->_capacity > C) //we were in dynamic
		{
			if (this->_size + 1 > this->_capacity)
			{
				this->_capacity = _capC(this->_size);
				_resizeVector(this->_heapVector, this->_capacity);
			}
			this->_heapVector[this->_size] = value;
		}
		else //stack
		{
			if (this->_size + 1 > this->_capacity)
			{
				this->_capacity = _capC(this->_size);
				this->_heapVector = new(std::nothrow) T[this->_capacity];
				std::copy(this->_stackVector, this->_stackVector + this->_size, this->_heapVector);
				this->_heapVector[this->_size] = value;
			}
			else
			{
				this->_stackVector[this->_size] = value;
			}
		}
		this->_size++;
	}
	
	/**
	 * this function adds the given elements to the given position in the vector.
	 * @param position the position to add the element in.
	 * @param value the value to add.
	 * @return the position of the added element.
	 */
	iterator insert(const_iterator &position, const T &value)
	{
		return this->insert(position, value);
	}

	/**
	 * this function adds the given elements to the given position in the vector.
	 * @param position the position to add the element in.
	 * @param value the value to add.
	 * @return the position of the added element.
	 */
	iterator insert(iterator position, T value)
	{
		int place = position - begin();
		if (this->_capacity > C && this->_size + 1 > this->_capacity)
		{
			this->_capacity = _capC(this->_size);
			_resizeVector(this->_heapVector, this->_capacity);
		}
		else if (this->_size + 1 > this->_capacity)
		{
			this->_capacity = _capC(this->_size);
			this->_heapVector = new(std::nothrow) T[this->_capacity];
			std::copy(this->_stackVector, this->_stackVector + this->_size, this->_heapVector);
		}
		std::move_backward(position, end(), end() + 1);
		(*this)[place] = value;
		this->_size++;
		return position;
	}

	/**
	* this function adds the given elements to the given position in the vector.
	* @param position the position to add the element in.
	* @param value the value to add.
	* @return the position of the added element.
	*/
	iterator insert(const_iterator &position, T &value)
	{
		return this->insert(position, value);
	}

	/**
	 * this functions adds the given range of elements to the current vector in the given position.
	 * @tparam InputIterator the type of the given iterators.
	 * @param position the position to add the elements in.
	 * @param first the first iterator.
	 * @param last the last iterator.
	 * @return an iterator to the first added element.
	 */
	template<class InputIterator>
	iterator insert(const_iterator &position, InputIterator first, InputIterator last)
	{
		iterator result = insert(position, first, last);
		return result;
	}

	/**
	 * this functions adds the given range of elements to the current vector in the given position.
	 * @tparam InputIterator the type of the given iterators.
	 * @param position the position to add the elements in.
	 * @param first the first iterator.
	 * @param last the last iterator.
	 * @return an iterator to the first added element.
	 */
	template<class InputIterator>
	iterator insert(iterator &position, InputIterator first, InputIterator last)
	{
		int firstInd = position - begin();
		size_t n = last - first;
		if (this->_capacity > C && this->_size + n > this->_capacity)
		{
			size_t size;
			_getNewSize(&size, n);
			_resizeVector(this->_heapVector, size);
		}
		else if (this->_size + n > this->_capacity)
		{
			size_t size;
			_getNewSize(&size, n);
			this->_heapVector = new(std::nothrow) T[size];
			std::copy(this->_stackVector, this->_stackVector + this->_size, this->_heapVector);
		}
		std::move_backward(position, end(), end() + (int) n);
		auto it = first;
		int i = firstInd;
		while (it != last)
		{
			(*this)[i] = *it;
			i++;
			it++;
		}
		this->_size += n;
		return iterator(&(*this)[firstInd]);
	}

	/**
	 * this function remove the last elements in the vector.
	 */
	void pop_back()
	{
		this->_size--;
	}

	/**
	 * this function removes the elements in hte given position.
	 * @param position the position that we want to remove.
	 * @return an iterator to the element that take the place of the removed one.
	 */
	iterator erase(const_iterator position)
	{
		return erase(position);
	}

	/**
	 * this function removes the elements in hte given position.
	 * @param position the position that we want to remove.
	 * @return an iterator to the element that take the place of the removed one.
	 */
	iterator erase(iterator position)
	{
		if (this->_capacity > C && this->_size - 1 < C)
		{
			int i = 0;
			for (auto it = begin(); it != end(); it++)
			{
				if (it != position)
				{
					this->_stackVector[i] = (*it);
					i++;
				}
			}
			delete[] this->_heapVector;
		}
		else
		{
			std::move(position + 1, end(), position);
		}
		this->_size--;
		return position;
	}

	/**
	 * this function removes the given range of elements from the current vector.
	 * @param first the first iterator.
	 * @param last the last iterator.
	 * @return an iterator to the element that take the place of the removed one.
	 */
	iterator erase(const_iterator first, const_iterator last) //todo
	{
		iterator pos = last;
		for (auto it = first; it != last; it++)
		{
			pos = this->erase(it);
		}
		return pos;
	}

	/**
	 * this function removes the given range of elements from the current vector.
	 * @param first the first iterator.
	 * @param last the last iterator.
	 * @return an iterator to the element that take the place of the removed one.
	 */
	iterator erase(iterator first, iterator last)
	{
		int n = last - first;
		int firstInd = first - begin();
		int lastInd = end() - last;
		iterator position = first;
		if (this->_capacity > C && this->_size - n < C)
		{
			for (int i = 0; i < firstInd; ++i)
			{
				this->_stackVector[i] = this->_heapVector[i];
			}
			for (int j = lastInd; j < this->_capacity; ++j)
			{
				this->_stackVector[j] = this->_heapVector[j];
			}
			delete[] this->_heapVector;
		}
		else
		{
			std::move(position + n, end(), position);
		}
		this->_size -= n;
		return Iterator(&(*this)[firstInd]);
	}

	/**
	 * this function clears all the datat in the current vector.
	 */
	void clear() noexcept
	{
		this->_size = 0;
		this->_capacity = C;
		(*this).~VLVector();
		this->_heapVector = nullptr;
	}

	/**
	 * this function returns the data structure that we are using now.
	 * @return the data structure that we are using now.
	 */
	T *data() noexcept
	{
		if (this->_capacity > C)
		{
			return this->_heapVector;
		}
		return this->_stackVector;
	}

	/**
	 * this function returns the data structure that we are using now.
	 * @return the data structure that we are using now.
	 */
	const T *data() const noexcept
	{
		if (this->_capacity > C)
		{
			return this->_heapVector;
		}
		return this->_stackVector;
	}

	/**
	 * this function returns the element in the given index.
	 * @param i the given index.
	 * @return the element in the given index.
	 */
	T &operator[](int i)
	{
		return this->data()[i];
	}

	/**
	 * this function returns the element in the given index.
	 * @param i the given index.
	 * @return the element in the given index.
	 */
	const T &operator[](int i) const
	{
		return this->data()[i];
	}

	/**
	 * this function checks if the given VLVector is equal to the current vector.
	 * @param other the other VLVector.
	 * @return true if they are equal, false otherwise.
	 */
	bool operator==(const VLVector<T, C> &other)
	{
		if (this->_size == other._size)
		{
			for (int i = 0; i < (int) this->_size; ++i)
			{
				if ((*this)[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	/**
	 * this function checks if the given VLVector is equal to the current vector.
	 * @param other the other VLVector.
	 * @return false if they are equal, true otherwise.
	 */
	bool operator!=(const VLVector<T, C> &other)
	{
		return !this->operator==(other);
	}

	/**
	 * this function copy all the members of the given VLVector to the current vector.
	 * @param other the other vector.
	 * @return VLVector Object.
	 */
	VLVector<T, C> &operator=(const VLVector<T, C> &other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete[] this->_heapVector;
		VLVector();
		this->_capacity = other._capacity;
		for (int i = 0; i < (int) other._size; ++i)
		{
			this->push_back(other[i]);
		}
		return *this;
	}

	/**
	 * this function returns iterator on the begin of the vector.
	 * @return iterator on the begin of the vector.
	 */
	iterator begin() noexcept
	{
		iterator it(&(*this)[0]);
		return it;

	}

	/**
	 * this function returns iterator on the begin of the vector.
	 * @return iterator on the begin of the vector.
	 */
	const_iterator begin() const noexcept
	{
		return this->begin();
	}

	/**
	 * this function returns iterator on the begin of the vector.
	 * @return iterator on the begin of the vector.
	 */
	const_iterator cbegin() const noexcept
	{
		const_iterator it(&(*this)[0]);
		return it;
	}

	/**
	 * this function returns iterator on the end of the vector.
	 * @return iterator on the end of the vector.
	 */
	iterator end() noexcept
	{
		iterator it(&(*this)[this->_size]);
		return it;
	}

	/**
	 * this function returns iterator on the end of the vector.
	 * @return iterator on the end of the vector.
	 */
	const_iterator end() const noexcept
	{
		return this->end();
	}

	/**
	 * this function returns iterator on the end of the vector.
	 * @return iterator on the end of the vector.
	 */
	const_iterator cend() const noexcept
	{
		const_iterator it(&(*this)[this->_size]);
		return it;
	}
};

#endif //EXAMCPP_VLVECTOR_HPP
