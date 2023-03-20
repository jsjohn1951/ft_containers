/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:32:02 by wismith           #+#    #+#             */
/*   Updated: 2023/03/21 02:06:24 by wismith          ###   ########.fr       */
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
	class revMapIterator;

	template <class T, class Compare >
	class constRevMapIterator;

	template <class T, class Compare >
	class constMapIterator;

	/*
	*	@brief :
	*			node_iter object used by iterators to iterator through the map.
	*			node_iter uses the Compare object to find the next node.
	*		
	*	@example :
	*			In this example we know that -4 < 3 < 4 < 5 < 6, assume iterator is initially on -4
	*
	*				 			1) Because we're on -4 which has no right children we want to move to the parent of the node.
	*							2) On 3 we see the node has a right child (5) so we move to to the far left child of the right
	*								child (5) , which is 4.
	*							3) 4 has no right children, so we move to the parent.
	*							4) On 5 there are no right child, so we move back until the current is
	*								greater than the node we were on, and eventually get to 6.
	?				 6
	?				/				  2nd  _->	3	        2nd  _-> 3								5th  _->  6
	?			   3					 (	  /	 \	        	(_	 \								   (_	 /
	?			 /	\				1st -> -4	  5	        	  --- 5 __         	    5 <-_  4th		 -- 3 --__
	?		   -4	 5								        		/   __ )	 	  /   __ )			    \    _ )
	?		        /			    		(far left child of 5)  4 <- 	3rd      4 <-	 3rd			 5 <-	 4th
	?			   4				
	*	@note :
	*			form this we can decern 2 rules inorder to make our iterators work:
	*				1) if there no right children: loop to the parents until the current is > than the last node you were on.
	*				2) if current has a right child : move to the far left child of the right child.
	*			
	*/
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
				this->key_cmp = iter.key_cmp;
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
			mapIterator(): iter(), ptr() {}

			template <class A, class Comp>
			mapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}

			mapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			mapIterator(const mapIterator<A, Comp> &map) : iter(), ptr(map.get_node()){}

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

			pointer	get_node() const { return (this->ptr); }
	};

	template <class T, class Compare >
	class constMapIterator
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
			constMapIterator(): iter(), ptr() {}

			template <class A, class Comp>
			constMapIterator(const mapIterator<A, Comp> &map) : iter(), ptr(map.get_node()){}

			template <class A, class Comp>
			constMapIterator(const revMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}

			template <class A, class Comp>
			constMapIterator(const constRevMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}

			constMapIterator(pointer p) : iter(), ptr(p) {}

			template <class A, class Comp>
			constMapIterator(const constMapIterator<A, Comp> &map) : iter(), ptr(map.get_node()) {}
			
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

			pointer	get_node() const { return (this->ptr); }

	};

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const mapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const constMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const constMapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator!=(const mapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() != mp2.get_node());
	}

	template<class T1, class Compare>
	bool	operator==(const mapIterator<T1, Compare> &mp, const constMapIterator<T1, Compare> &mp2)
	{
		return (mp.get_node() == mp2.get_node());
	}
};

# include "revMapIterator.hpp"

#endif