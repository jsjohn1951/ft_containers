/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:32:02 by wismith           #+#    #+#             */
/*   Updated: 2023/03/05 00:38:44 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "../utils/iterator_traits.hpp"
# include "../utils/utility.hpp"
# include "tree.hpp"
# include "node_def.hpp"
# include <iostream>

namespace ft
{
	template <class T, class Compare >
	class node_iter
	{
		public :
			typedef Compare											key_compare;
			typedef ft::iterator<ft::bidirectional_iterator_tag, T>	trait_type;
			typedef typename trait_type::value_type					value_type;
			typedef typename trait_type::difference_type			difference_type;
			typedef typename trait_type::pointer					data_ptr;
			typedef typename trait_type::const_pointer				const_pointer;
			typedef typename trait_type::reference					reference;
			typedef typename trait_type::iterator_category			iterator_category;
			typedef ft::node_def<T>*								pointer;

		private	:
			key_compare	key_cmp;
			
		public :
			node_iter() : key_cmp() {}
			node_iter(const node_iter &iter) : key_cmp(iter.key_cmp) {}

			node_iter	&operator=(const node_iter &iter)
			{
				(void) iter;
				return (*this);
			}

			pointer increment(pointer ptr)
			{
				pointer	tmp = ptr;
				if (ptr->rChld)
					ptr = this->min_value(ptr->rChld);
				else
				{
					if (tmp->data)
						while (key_cmp(ptr->prev->data->first, tmp->data->first))
							ptr = ptr->prev;
					ptr = ptr->prev;
				}
				return (ptr);
			}

			pointer decrement(pointer ptr)
			{
				pointer	tmp = ptr;
				if (ptr->lChld)
					ptr = this->max_value(ptr->lChld);
				else
				{
					if (tmp->data)
						while (key_cmp(tmp->data->first, ptr->prev->data->first))
							ptr = ptr->prev;
					ptr = ptr->prev;
				}
				return (ptr);
			}

			private :

			pointer min_value(pointer node)
			{
				pointer tmp = node;
				while (tmp && tmp->lChld && tmp->lChld->data)
					tmp = tmp->lChld;
				return (tmp);
			}

			pointer max_value(pointer node)
			{
				pointer tmp = node;
				while (tmp && tmp->rChld && tmp->rChld->data)
					tmp = tmp->rChld;
				return (tmp);
			}
	};
	
	template <class T, class Compare >
	class mapIterator
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
			mapIterator(): iter(), ptr() {}
			template <class A, class Comp>
			mapIterator(const mapIterator<A, Comp> &map) : iter(), ptr(map.base()) {}
			mapIterator(pointer p) : iter(), ptr(p) {}
			~mapIterator(){}

			mapIterator	&operator=(const mapIterator &map)
			{
				if (this != &map)
					this->ptr = map.ptr;
				return (*this);
			}

			data_ref operator*() const { return (*this->ptr->data); }
			data_ptr operator->() const {return (this->ptr->data);}

			mapIterator &operator++()
			{
				this->ptr = this->iter.increment(this->ptr);
				return (*this);
			}

			mapIterator operator++(int)
			{
				mapIterator iter = *this;
				this->operator++();
				return (iter);
			}

			mapIterator &operator--()
			{
				(!this->ptr->data ?
					this->ptr = this->ptr->prev :
					this->ptr = this->iter.decrement(this->ptr));
				return (*this);
			}

			mapIterator operator--(int)
			{
				mapIterator iter = *this;
				this->operator--();
				return (iter);
			}

			pointer base() const { return (this->ptr); }

			iterator	getIter() const
			{
				return (this->iter);
			}
	};

	template <class T, class Compare = std::less<T> >
	class constMapIterator
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

			typedef ft::mapIterator<value_type, Compare>			map_iter;

		private :
			iterator	iter;
			pointer		ptr;

		public :
			constMapIterator(): iter(), ptr() {}
			template <class A, class Comp>
			constMapIterator(const constMapIterator<A, Comp> &map) : iter(), ptr(map.base()) {}
			constMapIterator(pointer p) : iter(), ptr(p) {}

			constMapIterator(const map_iter &m) : iter(m.getIter()), ptr(m.base()) {}
			
			~constMapIterator(){}

			constMapIterator	&operator=(const constMapIterator &map)
			{
				if (this != &map)
					this->ptr = map.ptr;
				return (*this);
			}

			data_ref operator*() const { return (*this->ptr->data); }
			data_ptr operator->() const { return (this->ptr->data); }

			constMapIterator &operator++()
			{
				this->ptr = this->iter.increment(this->ptr);
				return (*this);
			}

			constMapIterator operator++(int)
			{
				constMapIterator iter = *this;
				this->operator++();
				return (iter);
			}

			constMapIterator &operator--()
			{
				(!this->ptr->data ?
					this->ptr = this->ptr->prev :
					this->ptr = this->iter.decrement(this->ptr));
				return (*this);
			}

			constMapIterator operator--(int)
			{
				constMapIterator iter = *this;
				this->operator--();
				return (iter);
			}

			pointer base() const { return (this->ptr); }

			iterator	getIter() const
			{
				return (this->iter);
			}
	};

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() != mp2.base());
	}

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.base() == mp2.base());
	}
};


#endif