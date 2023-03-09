/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:28:53 by wismith           #+#    #+#             */
/*   Updated: 2023/03/05 00:14:36 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAP_HPP
# define MAP_HPP

# include "../utils/algorithm.hpp"
# include "../utils/utility.hpp"
# include "../utils/exceptions.hpp"
# include "../utils/functional.hpp"
# include "mapIterator.hpp"
# include "revMapIterator.hpp"
# include "../vector/vector.hpp"
# include "tree.hpp"
# include <memory>
# include <iostream>

/*
*	@todo :
*	@ Members:
*		@require iterators:
*		swap
*
*	@ Non Members:
*		relational Operators
*		swap
*		
*/

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public :
			typedef Compare																key_compare;
			typedef Key																	key_type;
			typedef T																	mapped_type;

			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef ft::pair<const key_type, const mapped_type>							const_value_type;
			typedef value_type*															value_type_ptr;
			typedef Alloc																allocator_type;

			typedef ft::tree<key_type, mapped_type, Compare, Alloc>						tree_type;
			typedef	tree_type*															tree_type_ptr;
			typedef typename allocator_type::template rebind<tree_type>::other			tree_allocator;

			typedef typename ft::node_def<value_type>									node_type;
			typedef node_type*															node_ptr;

			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::size_type									size_type;
			typedef typename allocator_type::difference_type							difference_type;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;

			typedef typename ft::mapIterator<value_type, Compare>						iterator;
			typedef typename ft::constMapIterator<value_type, Compare>					const_iterator;
			typedef typename ft::revMapIterator<value_type, Compare>					reverse_iterator;
			typedef typename ft::constRevMapIterator<value_type, Compare>				const_reverse_iterator;

		private :
			allocator_type			alloc;
			tree_allocator			treeAlloc;
			key_compare				cmp;
			size_type				Size;
			tree_type_ptr			tree;

		public:

			class value_compare : public ft::binary_function<value_type,value_type,bool>
			{
				private :
					friend class map;
					protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			//! Constructors
			explicit	map(const Compare &_cmp = Compare(), const allocator_type &_alloc = allocator_type()) :
				alloc(_alloc), cmp(_cmp), Size(0), tree()
			{
				this->tree = this->treeAlloc.allocate(1);
				this->treeAlloc.construct(this->tree, tree_type());
			}

			map (const map& x) : alloc(x.get_allocator()), cmp(x.key_comp()), Size(0), tree()
			{
				this->tree = this->treeAlloc.allocate(1);
				this->treeAlloc.construct(this->tree, tree_type());	
				this->tree_cpy(x.tree->getRoot());
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& _cmp = key_compare(), const allocator_type& _alloc = allocator_type()) :
				alloc(_alloc), cmp(_cmp), Size(0), tree()
			{
				this->tree = this->treeAlloc.allocate(1);
				this->treeAlloc.construct(this->tree, tree_type());
				InputIterator	it;
				for (it = first; it != last; it++)
					this->tree->insert(ft::make_pair<key_type, mapped_type>(it->first, it->second));
			}

			//! Assignment Operator
			map	&operator=(const map &x)
			{
				if (this != &x)
				{
					this->treeAlloc.destroy(this->tree);
					this->treeAlloc.deallocate(this->tree, 1);
					this->tree = this->treeAlloc.allocate(1);
					this->treeAlloc.construct(this->tree, tree_type());	
					this->tree_cpy(x.tree->getRoot());
				}
				return (*this);
			}

			//! Destructor
			~map()
			{
				this->treeAlloc.destroy(this->tree);
				this->treeAlloc.deallocate(this->tree, 1);
			}

			/*
			*	@brief : [] operator returns reference of mapped_type element of ft::pair<> with key_type k
			*	@note :
			*			uses the tree's insert function which will check if the node exists,
			*			if not it will insert the value into the tree, increasing size by one 
			*/
			mapped_type&	operator[] (const key_type& k)
			{
				ft::pair<key_type, mapped_type>	pr(k, mapped_type());
				node_ptr						node = this->tree->search(pr);

				if (!node)
					node = tree->insert(pr, true);
				return (node->data->second);
			}

			void clear()
			{
				tree->destroyTree();
			}

			size_type	count(const key_type& k) const
			{
				node_ptr	node = this->tree->search(ft::pair<key_type, mapped_type>(k,mapped_type()));
				return (node ? 1 : 0);
			}

			bool empty() const
			{
				if (!tree->size())
					return (true);
				return (false);
			}

			allocator_type	get_allocator() const
			{
				return (this->alloc);
			}

			key_compare	key_comp() const
			{
				return (this->cmp);
			}

			size_type max_size() const
			{
				return (this->tree->max_size());
			}

			size_type size() const
			{
				return (this->tree->size());
			}

			iterator begin()
			{
				if (!this->tree->size())
					return (this->end());
				return (iterator(this->tree->begin()));
			}

			iterator end()
			{
				return (iterator(this->tree->tmax()));
			}

			const_iterator begin() const
			{
				if (!this->tree->size())
					return (this->end());
				return (const_iterator(this->tree->begin()));
			}

			const_iterator end() const
			{
				return (const_iterator(this->tree->tmax()));
			}

			reverse_iterator	rbegin()
			{
				if (!this->tree->size())
					return (this->rend());
				return (reverse_iterator(this->tree->end()));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(this->tree->tmin()));
			}

			const_reverse_iterator	rbegin() const
			{
				if (!this->tree->size())
					return (this->rend());
				return (reverse_iterator(this->tree->end()));
			}

			const_reverse_iterator	rend() const
			{
				return (reverse_iterator(this->tree->tmin()));
			}

			value_compare value_comp() const
			{
				return (value_compare(this->key_comp()));
			}

			iterator	lower_bound(const key_type& k)
			{
				iterator	it = this->begin();
				while (it != this->end() && this->cmp(it->first, k))
					it++;
				return (it);
			}

			const_iterator	lower_bound(const key_type& k) const
			{
				const_iterator	it = this->begin();
				while (it != this->end() && this->cmp(it->first, k))
					it++;
				return (it);
			}

			iterator	upper_bound(const key_type& k)
			{
				iterator	it(this->end());
				iterator	end(this->tree->tmin());
				it--;
				while (it != end && this->cmp(k, it->first))
					it--;
				return (++it);
			}

			const_iterator	upper_bound(const key_type& k) const
			{
				const_iterator	it(this->end());
				const_iterator	end(this->tree->tmin());
				it--;
				while (it != end && this->cmp(k, it->first))
					it--;
				return (++it);
			}

			/*
			*	@brief : equal_range() function returns a range with k as key
			*	@note :
			*		All keys in map are unique, so equal_range will only
			*		return an ft::pair<> with the first being an iterator of the node,
			*		second being an iterator to the node after.
			*
			*		If k not found in tree, the return will be two iterators (first, and second)
			*		pointing to the same node (the first node with key val greater than k).
			*
			*		If k is greater than the max, return will be first and second pointing to the
			*		node after root.
			*/

			ft::pair<iterator,iterator>	equal_range(const key_type& k)
			{
				iterator	first = this->lower_bound(k);
				iterator	second = this->upper_bound(k);
				return (ft::make_pair<iterator, iterator>(first, second));
			}

			/*
			*	@brief : equal_range() function returns a range with k as key
			*	@note :
			*			The ft::pair<> with const_iterators works the same as the previous equal_range(),
			*			only it will construct using const_iterator (constant iterators).
			*/
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k)	const
			{
				const_iterator	first  = this->lower_bound(k);
				const_iterator	second = this->upper_bound(k);
				return (ft::make_pair(first, second));
			}

			/*
			*	@brief : position erase calls the tree's destroyElement function to remove the element
			*/
			void erase (iterator position)
			{
				if (position != this->end() && position != --this->begin())
					this->tree->destroyElement(*position.operator->());
			}

			/*
			*	@brief : range erase calls the key erase in a loop
			*	@note :
			*			In order to effectively erase the portion of data
			*			this function saves all the relevant keys of each node in a vector
			*			we can then extract each key use as argument for the key_type erase.
			*/
			void erase(iterator first, iterator last)
			{
				ft::vector<key_type>	vec;

				for (; first != last; first++)
					vec.push_back(first->first);
				for (size_type i = 0; i < vec.size(); i++)
					this->erase(vec[i]);
			}

			/*
			*	@brief : key erase calls the tree's search function followed by the position erase function 
			*	@note :
			*			The tree's search function takes an ft::pair<> as it's aruments. We construct the ft::pair with
			*			k, and an empty mapped_type. If search returns a NULL, or returns a rend() or end(), the erase
			*			will return 0, otherwise, it will return 1.
			*
			*	@return :
			*			The number of elements erased.
			*/
			size_type erase (const key_type& k)
			{
				node_ptr	node = this->tree->search(ft::pair<key_type, mapped_type>(k, mapped_type()));
				if (!node || !node->data)
					return (0);
				this->erase(iterator(node));
				return (1);
			}

			/*
			*	@brief : find() function uses the tree's search function to find the node
			*	@note :
			*			the tree's search function takes an ft::pair<> constructed with key k and mapped_type().
			*			if the node pointer is NULL, or = end() / rend(), no element containing k as key was found.
			*	@return :
			*			function returns end() iterator if no element was found, else it will return an iterator for
			*			the found element.
			*/
			iterator find(const key_type& k)
			{
				node_ptr	node = this->tree->search(ft::pair<key_type, mapped_type>(k, mapped_type()));
				if (!node || !node->data || node->data->first != k)
					return (this->end());
				return (iterator(node));
			}

			/*
			*	@brief : find() function uses the tree's search function to find the node
			*	@note :
			*			the tree's search function takes an ft::pair<> constructed with key k and mapped_type().
			*			if the node pointer is NULL, or = end() / rend(), no element containing k as key was found.
			*	@return :
			*			function returns end() const_iterator if no element was found, else it will return an const_iterator
			*			for the found element.
			*/
			const_iterator find(const key_type& k) const
			{
				node_ptr	node = this->tree->search(ft::pair<key_type, mapped_type>(k, mapped_type()));
				if (!node || !node->data || node->data->first != k)
					return (this->end());
				return (const_iterator(node));
			}

			/*
			*	@brief : insert() value_type inserts a new node with value_type into the tree
			*	@note :
			*			To insert the function will call the tree class's insert function which takes a const value_type ref
			*			and returns an ft::pair<node_ptr (pointer to node), boolean (true if it created a new node / false
			*			if node already exists)>
			*	@return :
			*			returns an ft::pair<iterator, boolean>. The returned node from tree->insert is casted to iterator
			*			and the ft::pair<> second is set to the boolean returned (true if the node was created, flase if
			*			no new node was created).
			*/
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<node_ptr, bool>	pr = this->tree->insert(val);
				return (ft::make_pair(iterator(pr.first), pr.second));
			}

			iterator insert(iterator position, const value_type& val)
			{
				(void) position;
				return (this->insert(val).first);
			}

			/*
			*	@brief : range insert() inserts a range of nodes
			*	@note :
			*			In order to find the values we dereference the value_type pointer that each node contains
			*			as an argument for the value_type insert function
			*/
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					this->insert(*first.operator->());
			}

			/*
			*	@brief : swap() function swaps the pointers to each's respective tree
			*/
			void	swap(map& x)
			{
				tree_type_ptr	tmp = x.tree;
				x.tree = this->tree;
				this->tree = tmp;
			}

			private :
				
			/*
			*	@brief : tree_cpy() is a private member that inserts nodes into the tree.
			*	@note :
			*			Takes a pointer to the node, and uses recursion on the nodes's left
			*			& right children to find all the elements in the tree / branch, and 
			*			insert them into the tree.
			*	@primary use :
			*			Is used for copying the elements in one tree to another (e.g: map's copy constructor &
			*			assignment operator overload). 
			*/
			void	tree_cpy(node_ptr	node)
			{
				if (node && node->data)
				{
					tree_cpy(node->lChld);
					tree_cpy(node->rChld);
					this->tree->insert(*node->data);
				}
			}

			/*
			*	@brief : node_search() takes a node pointer and k, and uses recursion to search the tree
			*	@note :
			*			To search for a node with a particular key, the function uses the key_compare object
			*			to compare the node's keys with k. If k is less than the node's key, use recursion to check
			*			the left child, else check the right child.
			*
			*			A temp pointer is set to the node before calling the recursion, if the node returned by the
			*			recursion is NULL, or the node is = rend() / end(), the function will return the temp.
			*	@primary use:
			*			Is used in equal_range() where the ft::pair<>::first iterator are never = end()
			*/
			node_ptr	node_search(node_ptr node, const key_type &k)
			{
				if (node && node->data)
				{
					node_ptr	temp = node;
					node = (this->cmp(k, node->data->first) ?
							this->node_search(node->lChld, k)
							: this->node_search(node->rChld, k));
					if (!node || !node->data)
						return (temp);
				}
				return (node);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
};

#endif