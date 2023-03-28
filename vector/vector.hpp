/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:29:25 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 02:49:38 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <limits>
# include <stdexcept>

# include "vectorIterator.hpp"
# include "revIterator.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/valid_it.hpp"

namespace ft
{
	template < class T, class all = std::allocator<T> >
	class vector
	{
		public :
			typedef T													value_type;
			typedef all													allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			typedef typename ft::vectorIterator<value_type>				iterator;
			typedef typename ft::vectorIterator<const value_type>		const_iterator;
			typedef typename ft::revIterator<value_type>              	reverse_iterator;
			typedef typename ft::revIterator<const value_type>        	const_reverse_iterator;

		private:
			pointer			Data;
			allocator_type	Alloc;
			size_type		Size;
			size_type		Capacity;

		public :

			//! Constructors
			explicit vector(const allocator_type& allocator = allocator_type()) : Data(NULL), Alloc(allocator), Size(0), Capacity(0){}

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()): Data(NULL), Alloc(alloc), Size(0), Capacity(0)
			{ this->assign(n, val); }

			template <class InputIterator>
			explicit vector(InputIterator start, InputIterator end, const allocator_type& allocator = allocator_type(),
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type* = 0) : Data(NULL), Alloc(allocator), Size(0), Capacity(0)
			{ this->assign(start, end); }

			vector(const vector &vec) : Alloc(vec.get_allocator()),
				Size(vec.size()), Capacity(vec.size())
			{ this->Data = this->cpy_arr(vec); }

			//! End Constructors

			//! Desturctor

			~vector(){this->destroyData();}

			//! End Destructor

		//? ------------------------------------------- Operators ------------------------------------------- ?//

			vector		&operator=(const vector &vec)
			{
				if (this != &vec)
				{
					size_type	tmp = this->capacity();
					this->destroyData();
					if (vec.size() >= tmp)
						this->Capacity = vec.size();
					else
						this->Capacity = tmp;
					this->Data = this->cpy_arr(vec);
					this->Size = vec.size();
				}
				return (*this);
			}

			reference	operator[](size_type n)
			{
				return (*(this->Data + n));
			}

			const_reference	operator[](size_type n) const
			{
				return (*(this->Data + n));
			}

		//? ------------------------------------------- End Operators ------------------------------------------- ?//


			size_type	size() const
			{
				return (this->Size);
			}

			/*
			*	@brief : returns the min value between the allocator's max_size()
			*		and numeric_limits max with difference_type as template argument.
			*	@note :
			*		difference_type is often synonymous with std::ptrdiff_t which is used for
			*			pointer arithmetic.
			*	@source :
			*		https://en.cppreference.com/w/cpp/types/ptrdiff_t
			*/
			size_type	max_size() const
			{
				return (std::min<size_type>(this->Alloc.max_size(),
					std::numeric_limits<difference_type>::max()));
			}

			size_type	capacity() const
			{
				return (this->Capacity);
			}

			allocator_type	get_allocator() const
			{
				return (this->Alloc);
			}

			iterator begin()
			{
				return (this->Data);
			}

			const_iterator begin() const
			{
				return (this->Data);
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->Data + this->size()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->Data + this->size()));
			}

			iterator end()
			{
				return (this->Data + this->size());
			}

			const_iterator end() const
			{
				return (this->Data + this->size());
			}

			reverse_iterator rend()
			{
				return (this->Data);
			}

			const_reverse_iterator rend() const
			{
				return (reverse_iterator(this->Data));
			}

			reference	front()
			{
				return ((reference) this->operator[](0));
			}

			const_reference	front() const
			{
				return ((const_reference) this->operator[](0));
			}

			reference	back()
			{
				return (*(this->Data + this->size() - 1));
			}

			const_reference	back() const
			{
				return (*(this->Data + this->size() - 1));
			}

			reference at(size_type n)
			{
				if (n >= this->size())
					throw (std::out_of_range(std::string("out of range")));
				return (this->operator[](n));
			}

			const_reference at(size_type n) const
			{
				if (n >= this->size())
					throw (std::out_of_range(std::string("out of range")));
				return (this->operator[](n));
			}

			bool		empty() const
			{
				return (!this->size() ? true : false);
			}

		private :

			pointer		cpy_arr(const vector &x)
			{
				if (!x.capacity())
					return (NULL);
				pointer	tmp_data = x.get_allocator().allocate(this->capacity());
				for (size_type i = 0; i < x.size(); i++)
					x.get_allocator().construct(tmp_data + i, x.operator[](i));
				return (tmp_data);
			}

			pointer		destroyData()
			{
				size_type	n = this->Size;
				for (; n; n--)
					this->Alloc.destroy(this->Data + n - 1);
				this->Alloc.deallocate(this->Data, this->capacity());
				this->Capacity = 0;
				return (NULL);
			}

			size_type	vector_arithmatic(size_type current, size_type required)
			{
				if (required > this->max_size())
					throw (std::length_error("cannot create ft::vector larger than max_size()"));
				if (current)
					while (current < required)
						current *= 2;
				else
					current = 1;
				return (current);
			}

		public :

			void		push_back(const value_type& val)
			{
				if (this->size() == this->capacity())
					(!this->capacity() ? this->reserve(1)
					:	this->reserve(this->capacity() * 2));
				this->Alloc.construct(this->Data + this->size(), val);
				this->Size++;
			}

			void		pop_back()
			{
				this->Alloc.destroy(this->Data + this->size() - 1);
				this->Size--;
			}

			void		reserve(size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("cannot create ft::vector larger than max_size()"));
				if (this->capacity() < n)
				{
					if (!this->capacity())
					{
						this->Data = this->Alloc.allocate(n);
						this->Capacity = n;
						return ;
					}
					pointer tmp = this->Alloc.allocate(n);
					for (size_type i = 0; i < this->size(); i++)
						this->Alloc.construct(tmp + i, *(this->Data + i));
					this->Data = this->destroyData();
					this->Data = tmp;
					this->Capacity = n;
				}
			}


			void		assign(size_type n, const value_type& val)
			{
				this->reserve(n);
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type* = 0)
			{
				unsigned long long		n = 0;
				InputIterator			tmp = first;

				range_check(first, last);
				for (; tmp != last; tmp++)
					n++;
				this->reserve(n);
				this->clear();
				for (; first != last; first++)
					this->push_back(*first);
			}

			void		clear()
			{
				while (!this->empty())
					this->pop_back();
			}

			iterator	erase(iterator position)
			{
				for (iterator it = position; it != this->end() - 1; it++)
					*it = *(it + 1);
				this->pop_back();
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				if (first == last)
					return (first);
				for (; (last - 1) != first; last--)
					this->erase((last - 1));
				this->erase(first);
				return (first);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				bool			atEnd = ( position == this->end() ? true : false );
				difference_type	fOffset = position - this->begin();
				difference_type	bOffset = this->end() - position;

				this->reserve(vector_arithmatic(this->capacity(), this->size() + 1));
				if (atEnd)
						this->push_back(val);
				else
				{
					difference_type	nEnd = this->size();
					this->Alloc.construct(this->Data + nEnd, (bOffset > 0 ?
						this->operator[](fOffset + bOffset - 1) : val));
					for (; nEnd >= fOffset; nEnd--, bOffset--)
						if (static_cast<size_type>(nEnd) < this->size())
							this->operator[](nEnd) = (bOffset > 0 ?
								this->operator[](fOffset + bOffset - 1) : val);
					this->Size++;
				}
				return (iterator(this->Data + fOffset));
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				bool			atEnd = ( position == this->end() ? true : false );
				difference_type	fOffset = position - this->begin();
				difference_type	bOffset = this->end() - position;

				this->reserve(vector_arithmatic(this->capacity(), this->size() + n));
				if (atEnd)
					for (; n; n--)
						this->push_back(val);
				else
				{
					difference_type	nEnd = this->size() - 1 + n;
					for (; nEnd >= fOffset; nEnd--, bOffset--)
					{
						if (static_cast<size_type>(nEnd) >= this->size())
							this->Alloc.construct(this->Data + nEnd, (bOffset > 0 ?
								this->operator[](fOffset + bOffset - 1) : val));
						else
							this->operator[](nEnd) = (bOffset > 0 ?
								this->operator[](fOffset + bOffset - 1) : val);
					}
					this->Size += n;
				}
			}

			/*
			*	@brief : Range insert inserts a range of elements using the first and last iterators
			*	@note :
			*			An iterator contain a pointer that points to an element in the array.
			*	@index :
			*			fOffset - is the offset between position and the begining of the array
			?				@use :
			?					fOffset is to keep track of the index value of position
			*
			*			bOffset - is the offset between the end of the array and the position
			?				@use :
			?					keeps track of how many elements need to be shifted to the back of the array
			*
			*			n - the offset between last and first static casted to size_type
			?				@use :
			?					stores the number of elements that need to be inserted
			*
			*			nEnd - the current vector size() - 1 + n
			?				@Use :
			?					is the index used to iterator through the reallocated array to shift the elements
			?					and to insert the new elements
			*
			*	@note :
			*		because reserve may cause the reallocation of the array, any pre initialized
			*		pointer involvement becomes useless. A solution is to calculate all the indexes before-hand and
			*		use the indexes in the arithmatic. Which also proves to be faster.
			*/
		// typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type* = 0)
			{
				bool			atEnd = ( position == this->end() ? true : false );
				difference_type	fOffset = position - this->begin();
				difference_type	bOffset = this->end() - position;
				size_type		n = 0;
				InputIterator	tmp = first;

				for (; tmp != last; tmp++)
					n++;

				this->reserve(this->vector_arithmatic(this->capacity(), this->size() + n));
				if (atEnd)
					for (; n; n--, first++)
						this->push_back(*first);
				else
				{
					difference_type	nEnd = this->size() - 1 + n;
					for (; nEnd >= fOffset; nEnd--, bOffset--)
					{
						if (static_cast<size_type>(nEnd) >= this->size())
							this->Alloc.construct(this->Data + nEnd, (bOffset > 0 ?
								this->operator[](fOffset + bOffset - 1) : *(--last)));
						else
							this->operator[](nEnd) = (bOffset > 0 ?
								this->operator[](fOffset + bOffset - 1) : *(--last));
					}
					this->Size += n;
				}
			}

			void	resize(size_type n, value_type val = value_type())
			{
				this->reserve(n);
				while (n > this->size())
					this->push_back(val);
				while (n < this->size())
					this->pop_back();
			}

			void	swap(vector& x)
			{
				pointer			tmp_data = this->Data;
				size_type		tmp_size = this->size();
				size_type		tmp_cap = this->capacity();
				allocator_type	tmp_alloc = this->get_allocator();

				this->Data = x.Data;
				this->Size = x.size();
				this->Capacity = x.capacity();
				this->Alloc = x.get_allocator();

				x.Data = tmp_data;
				x.Size = tmp_size;
				x.Capacity = tmp_cap;
				x.Alloc = tmp_alloc;
			}
	};

	template <class T, class Alloc>
	void	swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool	operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
};

#endif