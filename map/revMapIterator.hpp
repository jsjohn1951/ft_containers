/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revMapIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:10:43 by wismith           #+#    #+#             */
/*   Updated: 2023/03/21 13:12:43 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef REVMAPITERATOR_HPP
# define REVMAPITERATOR_HPP

# include "mapIterator.hpp"


namespace ft
{
	template <class T, class Compare >
	class revMapIterator
	{
		private :
			typedef ft::iterator<ft::bidirectional_iterator_tag, T>	trait_type;
			typedef T*												data_ptr;
			typedef T&												data_ref;
			typedef ft::node_iter<T, Compare>						iterator;
			
		public :
			typedef typename trait_type::value_type					value_type;
			typedef typename trait_type::difference_type			difference_type;
			typedef typename trait_type::reference					reference;
			typedef typename trait_type::iterator_category			iterator_category;
			typedef ft::node_def<T>*								pointer;

		private :
			iterator	iter;
			pointer		ptr;

		public :
			revMapIterator(): iter(), ptr() {}

			// template <class A, class Comp>
			revMapIterator(const mapIterator<T, Compare> &map) : iter()
			{
				mapIterator<T, Compare>	other(map);
				this->ptr = (--other).get_node();
			}

			revMapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			revMapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}

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

			mapIterator<T, Compare > base() const 
			{
				return (++mapIterator<T, Compare >(this->ptr));
			}

			pointer	get_node() const { return (this->ptr); }
	};

	template <class T, class Compare >
	class constRevMapIterator
	{
		private :
			typedef ft::iterator<ft::bidirectional_iterator_tag, T>	trait_type;
			typedef const T*										data_ptr;
			typedef const T&										data_ref;
			typedef ft::node_iter<T, Compare>						iterator;
			
		public :
			typedef typename trait_type::value_type					value_type;
			typedef typename trait_type::difference_type			difference_type;
			typedef typename trait_type::reference					reference;
			typedef typename trait_type::iterator_category			iterator_category;
			typedef ft::node_def<T>*								pointer;

		private :
			iterator	iter;
			pointer		ptr;

		public :
			constRevMapIterator(): iter(), ptr() {}
	
			template <class A, class Comp>
			constRevMapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()){}

			template <class A, class Comp>
			constRevMapIterator(const constMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()){}

			template <class A, class Comp>
			constRevMapIterator(const mapIterator<A, Comp> &map) : iter()
			{
				mapIterator<A, Comp>	other(map);
				this->ptr = (--other).get_node();
			}

			constRevMapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			constRevMapIterator(const constRevMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}
			
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

			mapIterator<T, Compare > base() const
			{
				return (++mapIterator<T, Compare >(this->ptr));
			}

			pointer					get_node() const { return (this->ptr); }

	};

//* ------------------------------ revMapIter ------------------------------------------
	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

//* ------------------------------ End revMapIter ---------------------------------------

//* ------------------------------ constRev / Rev ---------------------------------------

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

//* ------------------------------ End constRev / Rev -----------------------------------

//* ------------------------------ Rev / constRev ---------------------------------------

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

//* ------------------------------ End Rev / constRev -----------------------------------

//* ------------------------------ constRev / constRev ----------------------------------

template<class T1, class Compare>
bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
{
	return (mp.get_node() != mp2.get_node());
}

template<class T1, class Compare>
bool	operator==(const constRevMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
{
	return (mp.get_node() == mp2.get_node());
}

//* ------------------------------ End constRev / constRev ------------------------------

//! Compare with revIter with mapIter

//* ------------------------------ mapIter / revIter ------------------------------------

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End mapIter / revIter --------------------------------

//* ------------------------------ const mapIter / revIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const revMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End const mapIter / revIter ---------------------------

//* ------------------------------ mapIter / const revIter -------------------------------

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End mapIter / const revIter ---------------------------

//* ------------------------------ const mapIter / const revIter -------------------------

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const constRevMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End const mapIter / const revIter ---------------------

//!	Compare revIter with mapIter

//* ------------------------------ revIter / mapIter ------------------------------------

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End revIter / mapIter --------------------------------

//* ------------------------------ const revIter / mapIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End const revIter / mapIter --------------------------

//* ------------------------------ revIter / const mapIter ------------------------------

	template<class T1, class Compare>
	bool	operator==(const revMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const revMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End revIter / const mapIter --------------------------

//* ------------------------------ const revIter / const mapIter ------------------------

	template<class T1, class Compare>
	bool	operator==(const constRevMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constRevMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

//* ------------------------------ End const revIter / const mapIter --------------------

};

#endif