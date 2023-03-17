/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revMapIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:10:43 by wismith           #+#    #+#             */
/*   Updated: 2023/03/17 23:37:52 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef REVMAPITERATOR_HPP
# define REVMAPITERATOR_HPP

# include "mapIterator.hpp"


namespace ft
{
	// template <class T, class Compare >
	// class constRevMapIterator;

	template <class T, class Compare >
	class revMapIterator
	{
		public :
			typedef ft::iterator<ft::bidirectional_iterator_tag, T>	trait_type;
			typedef typename trait_type::value_type					value_type;
			typedef typename trait_type::difference_type			difference_type;
			typedef T*												data_ptr;
			typedef T&												data_ref;
			typedef typename trait_type::const_pointer				const_pointer;
			typedef typename trait_type::reference					reference;
			typedef typename trait_type::iterator_category			iterator_category;
			typedef ft::node_def<T>*								pointer;
			typedef ft::node_iter<T, Compare>						iterator;

			typedef ft::mapIterator<value_type, Compare>			map_iter;

		private :
			iterator	iter;
			pointer		ptr;

		public :
			revMapIterator(): iter(), ptr() {}
			template <class A, class Comp>
			revMapIterator(const mapIterator<A, Comp> &map) : iter(), ptr(map.base()){}
			revMapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			revMapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.base()) {}
			~revMapIterator(){}

			revMapIterator	&operator=(const revMapIterator &map)
			{
				if (this != &map)
					this->ptr = map.ptr;
				return (*this);
			}

			data_ref operator*() const { return (*this->ptr->data); }
			data_ptr operator->() const { return (this->ptr->data); }

			revMapIterator &operator--()
			{
				this->ptr = this->iter.increment(this->ptr);
				return (*this);
			}

			revMapIterator operator--(int)
			{
				revMapIterator iter = *this;
				this->operator--();
				return (iter);
			}

			revMapIterator &operator++()
			{
				(!this->ptr->data ?
					this->ptr = this->ptr->prev :
					this->ptr = this->iter.decrement(this->ptr));
				return (*this);
			}

			revMapIterator operator++(int)
			{
				revMapIterator iter = *this;
				this->operator++();
				return (iter);
			}

			pointer base() const { return (this->ptr); }

			iterator	getIter() const
			{
				return (this->iter);
			}
	};

	template <class T, class Compare >
	class constRevMapIterator
	{
		public :
			typedef ft::iterator<ft::bidirectional_iterator_tag, T>	trait_type;
			typedef typename trait_type::value_type					value_type;
			typedef typename trait_type::difference_type			difference_type;
			typedef const T*										data_ptr;
			typedef const T&										data_ref;
			typedef typename trait_type::const_pointer				const_pointer;
			typedef typename trait_type::reference					reference;
			typedef typename trait_type::iterator_category			iterator_category;
			typedef ft::node_def<T>*								pointer;
			typedef ft::node_iter<T, Compare>						iterator;

			typedef ft::mapIterator<value_type, Compare>            map_iter;

		private :
			iterator	iter;
			pointer		ptr;

		public :
			constRevMapIterator(): iter(), ptr() {}
			template <class A, class Comp>
			constRevMapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.base()){}
			template <class A, class Comp>
			constRevMapIterator(const constMapIterator<A, Comp> &map) : iter(), ptr(map.base()){}
			template <class A, class Comp>
			constRevMapIterator(const mapIterator<A, Comp> &map) : iter(), ptr(map.base()){}
			constRevMapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			constRevMapIterator(const constRevMapIterator<A, Comp> &map) : iter(), ptr(map.base()) {}

			constRevMapIterator(const map_iter &m) : iter(m.getIter()), ptr(m.base()) {}
			
			~constRevMapIterator(){}

			constRevMapIterator	&operator=(const constRevMapIterator &map)
			{
				if (this != &map)
					this->ptr = map.ptr;
				return (*this);
			}

			data_ref operator*() const { return (*this->ptr->data); }
			data_ptr operator->() const { return (this->ptr->data); }

			constRevMapIterator &operator--()
			{
				this->ptr = this->iter.increment(this->ptr);
				return (*this);
			}

			constRevMapIterator operator--(int)
			{
				constRevMapIterator iter = *this;
				this->operator--();
				return (iter);
			}

			constRevMapIterator &operator++()
			{
				(!this->ptr->data ?
					this->ptr = this->ptr->prev :
					this->ptr = this->iter.decrement(this->ptr));
				return (*this);
			}

			constRevMapIterator operator++(int)
			{
				constRevMapIterator iter = *this;
				this->operator++();
				return (iter);
			}

			pointer base() const { return (this->ptr); }

			iterator	getIter() const
			{
				return (this->iter);
			}
	};

//* ------------------------------ revMapIter ------------------------------------------
	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

//* ------------------------------ End revMapIter ---------------------------------------

//* ------------------------------ constRev / Rev ---------------------------------------

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

//* ------------------------------ End constRev / Rev -----------------------------------

//* ------------------------------ Rev / constRev ---------------------------------------

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

//* ------------------------------ End Rev / constRev -----------------------------------

//* ------------------------------ constRev / constRev ----------------------------------

template<class T1, class Compare>
bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
{
	return (mp.base() != mp2.base());
}

template<class T1, class Compare>
bool	operator==(const constRevMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
{
	return (mp.base() == mp2.base());
}

//* ------------------------------ End constRev / constRev ------------------------------

//! Compare with revIter with mapIter

//* ------------------------------ mapIter / revIter ------------------------------------

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End mapIter / revIter --------------------------------

//* ------------------------------ const mapIter / revIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End const mapIter / revIter ---------------------------

//* ------------------------------ mapIter / const revIter -------------------------------

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End mapIter / const revIter ---------------------------

//* ------------------------------ const mapIter / const revIter -------------------------

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End const mapIter / const revIter ---------------------

//!	Compare revIter with mapIter

//* ------------------------------ revIter / mapIter ------------------------------------

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End revIter / mapIter --------------------------------

//* ------------------------------ const revIter / mapIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End const revIter / mapIter --------------------------

//* ------------------------------ revIter / const mapIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End revIter / const mapIter --------------------------

//* ------------------------------ const revIter / const mapIter ------------------------

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

//* ------------------------------ End const revIter / const mapIter --------------------

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const typename revMapIterator<T1, Compare>::pointer ptr)
	{
		return (mp.base() == ptr);
	}

};

#endif