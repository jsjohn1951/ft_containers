/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:29:25 by wismith           #+#    #+#             */
/*   Updated: 2023/03/09 00:59:31 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>

# include "vectorIterator.hpp"
# include "revIterator.hpp"
# include "../utils/type_traits.hpp"

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

			// explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): Alloc(alloc), Size(n), Capacity(n)
			// {
			// 	this->Data = Alloc.allocate(n);
			// 	for (size_type i = 0; i < this->size(); i++)
			// 		this->Alloc.construct(this->Data + i, val);
			// }

			// template <class InputIterator>
			// explicit vector(InputIterator start, InputIterator end, const allocator_type& allocator = allocator_type(),
			// 	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : Data(NULL), Alloc(allocator), Size(0), Capacity(0)
			// {
			// }

			// vector(const vector &vec) : Data(NULL), Alloc(vec.get_allocator()), Size(vec.size()), Capacity(vec.size())
			// {
			// }

			//! End Constructors

			//! Desturctor

			~vector(){this->destroyData();}

			//! End Destructor
	
		//? ------------------------------------------- Operators ------------------------------------------- ?//

			// vector		&operator=(const vector &vec)
			// {
			// 	if (this != &vec)
			// 	{
			// 	}
			// 	return (*this);
			// }

			reference	operator[](size_type n)
			{
				return (*(this->Data + n));
			}

			const_reference	operator[](size_type n) const
			{
				return (*(this->Data + n));
			}

		//? ------------------------------------------- End Operators ------------------------------------------- ?//


			//* ---------- Getters ---------- *//

			size_type	size() const
			{
				return (this->Size);
			}

			size_type	max_size() const
			{
				return (this->Alloc.max_size());
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
				return (this->end() - 1);
			}

			const_reverse_iterator rbegin() const
			{
				return (this->end() - 1);
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
				return (this->Data - 1);
			}

			const_reverse_iterator rend() const
			{
				return (this->Data - 1);
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
				return (this->operator[](n));
			}

			const_reference at(size_type n) const
			{
				return (this->operator[](n));
			}

			bool		empty()
			{
				return (!this->size() ? true : false);
			}

		private :

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
				if (current)
					while (current < required)
						current *= 2;
				else
					current = 1;
				return (current);
			}
			
		public :

			/*
			*	@required :
			*		resize
			*		swap
			*/
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
				if (this->size())
				{
					this->Size--;
					this->Alloc.destroy(this->Data + this->size());
				}
			}

			void		reserve(size_type n)
			{
				if (this->capacity() < n)
				{
					if (!this->capacity())
					{
						this->Data = this->Alloc.allocate(n);
						this->Capacity = n;
						return ;
					}
					pointer tmp = this->Alloc.allocate(n);
					for (int i = 0; i < this->size(); i++)
						this->Alloc.construct(tmp + i, *(this->Data + i));
					this->Data = this->destroyData();
					this->Data = tmp;
					this->Capacity = n;
				}
			}
			

			void		assign(size_type n, const value_type& val)
			{
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
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
				for (; (last - 1) != first; last--)
					this->erase((last - 1));
				this->erase(first);
				return (first);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				if (position == this->end())
					this->push_back(val);
				else
				{
					this->reserve(vector_arithmatic(this->capacity(), this->size() + 1));
					for (iterator it = this->end(); it != position; it--)
						*it = *(it - 1);
					*position = val;
					this->Size++;
				}
				return (position);
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
						this->operator[](nEnd) = (bOffset > 0 ?
							this->operator[](fOffset + bOffset - 1) : val);
					this->Size += n;
				}
			}

			/*
			*	@brief : Range insert inserts a range of elements using the first and last iterators
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
			*		
			*/
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				bool			atEnd = ( position == this->end() ? true : false );
				difference_type	fOffset = position - this->begin();
				difference_type	bOffset = this->end() - position;
				size_type		n = static_cast<size_type>(last - first);

				this->reserve(vector_arithmatic(this->capacity(), this->size() + n));
				if (atEnd)
					for (; n; n--, first++)
						this->push_back(*first);
				else
				{
					difference_type	nEnd = this->size() - 1 + n;
					for (; nEnd >= fOffset; nEnd--, bOffset--)
						this->operator[](nEnd) = (bOffset > 0 ?
							this->operator[](fOffset + bOffset - 1) : *(--last));
					this->Size += n;
				}
			}
	};
		/*
		* @required :
		*	relational operators
		*	swap
		*/
};

#endif