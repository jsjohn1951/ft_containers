/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:26:06 by wismith           #+#    #+#             */
/*   Updated: 2023/03/05 00:03:04 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef TREE_HPP
# define TREE_HPP

# include "node_def.hpp"
# include "balance.hpp"
# include "../utils/iterator_traits.hpp"
# include "../utils/utility.hpp"
# include <functional>
# include <memory>
# include <iostream>

# define left 1
# define right 2

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class tree
	{
		public :
			typedef Compare																key_compare;
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef value_type*															value_type_ptr;
			typedef ft::node_def<value_type>											node_type;
			typedef node_type*															pointer;
			typedef Alloc																base_allocator_type;
			typedef typename base_allocator_type::template rebind<node_type>::other		allocator_type;
			typedef std::size_t															size_type;
			typedef ft::balance<Key, T>													balance_type;

		private :
			key_compare			key_cmp;
			base_allocator_type	b_alloc;
			allocator_type		alloc;
			pointer				root;
			pointer				nullNode1;
			pointer				nullNode2;
			size_type			Size;
			balance_type		balance;

		public :
			explicit tree (const Compare &_cmp = key_compare(),
				const Alloc &_alloc = allocator_type()) : key_cmp(_cmp),
				alloc(_alloc), root(), Size(0)
			{
					this->nullNode1 = this->newNode(NULL);
					this->nullNode1->data = NULL;
					this->nullNode2 = this->newNode(NULL);
					this->nullNode2->data = NULL;
					this->root = NULL;
			}

			tree (const tree &t) : key_cmp(t.key_cmp),
				alloc(t.alloc), root(), Size(0)
			{
					this->nullNode1 = this->newNode(NULL);
					this->nullNode1->data = NULL;
					this->nullNode2 = this->newNode(NULL);
					this->nullNode2->data = NULL;
					this->cpyTree(t.getRoot());
					this->setSize(this->totalNodes(this->root));
			}

			~tree ()
			{
				this->root = this->_destroyTree(this->root);
				this->nullNode1 = this->destroyNode(this->nullNode1);
				this->nullNode2 = this->destroyNode(this->nullNode2);
			}

			tree	&operator=(const tree &t)
			{
				if (this != &t)
				{
					this->root = this->_destroyTree(this->root);
					this->cpyTree(t.getRoot());
					this->Size = t.Size;
				}
				return (*this);
			}
			
			ft::pair<pointer, bool>	insert(const value_type &val)
			{
				pointer node = this->search_tree(this->root, val.first);
				if (!node || !node->data)
					return (ft::pair<pointer, bool>(this->insert(val, true), true));
				return (ft::pair<pointer, bool>(node, false));
			}

			pointer	insert(const value_type &val, bool _insert)
			{
				pointer node = NULL;
				if (_insert)
				{
					this->init_leftRight(this->min(this->root), NULL, left);
					this->init_leftRight(this->max(this->root), NULL, right);
					{
						node = this->newNode(this->newValue(val));
						this->root = this->insertNode(this->root, node);
						this->Size++;
						this->setPrevVar(this->root, NULL);
					}
					this->init_leftRight(this->min(this->root), this->nullNode1, left);
					this->init_leftRight(this->max(this->root), this->nullNode2, right);
				}
				return (node);
			}

			void	destroyElement(const value_type &val)
			{
				this->init_leftRight(this->min(this->root), NULL, left);
				this->init_leftRight(this->max(this->root), NULL, right);
				this->root = this->deleteNode(this->root, val);
				this->setPrevVar(this->root, NULL);
				this->init_leftRight(this->min(this->root), this->nullNode1, left);
				this->init_leftRight(this->max(this->root), this->nullNode2, right);
			}

			void	destroyTree()
			{
				this->root = this->_destroyTree(this->root);
			}

			void	printData()
			{
				this->inorder(this->root);
				std::cout << std::endl;
			}

			size_type	size() const
			{
				return (this->Size);
			}

			void	setSize(size_type s)
			{
				this->Size = s;
			}

			pointer	search(const value_type &val) const
			{
				pointer node = this->search_tree(this->root, val.first);
				if (!node || !node->data)
					return (NULL);
				return (node);
			}

			size_type max_size() const
			{
				return (this->alloc.max_size());
			}

			pointer	begin()
			{
				if (!this->Size)
					return (this->root);
				return (this->min(this->root));
			}

			pointer	end()
			{
				if (!this->Size)
					return (this->root);
				return (this->max(this->root));
			}

			pointer tmin()
			{
				// if (!this->Size)
				// 	return (this->root);
				return (this->nullNode1);
			}

			pointer tmax()
			{
				// if (!this->Size)
				// 	return (this->root);
				return (this->nullNode2);
			}

			pointer	getRoot() const
			{
				return (this->root);
			}

			void	setRoot(const pointer r)
			{
				this->root = r;
				this->setSize(this->totalNodes(this->root));
			}

			private :

			void	cpyTree(pointer node)
			{
				if (!node || !node->data)
					return ;
				this->cpyTree(node->lChld);
				this->cpyTree(node->rChld);
				this->insert(*node->data);
			}

			int totalNodes(pointer node)
			{
			    if (!node || !node->data)
			        return 0;
			    int l = totalNodes(node->lChld);
			    int r = totalNodes(node->rChld);
 
			    return (1 + l + r);
			}

			/*
			*	@brief : finds the far left node
			*	@note :
			*		uses recursion to find the far left node. Recursion will break
			*		when it encounters a NULL node / left child points to NULL / or
			*		the data within left child points to NULL.
			*
			*		Checking for data in left child is necessary because ideally left child
			*		will be set to nullNode.
			*/
			pointer	min(pointer node)
			{
				if (node && node->lChld && node->lChld->data)
					node = this->min(node->lChld);
				return (node);
			}

			/*
			*	@brief : finds the far right node
			*	@note :
			*		uses recursion to find the far right node. Recursion will break
			*		when it encounters a NULL node / right child points to NULL / or
			*		the data within right child points to NULL.
			*
			*		Checking for data in right child is necessary because ideally right child
			*		will be set to nullNode.
			*/
			pointer	max(pointer node)
			{
				if (node && node->rChld && node->rChld->data)
					node = this->max(node->rChld);
				return (node);
			}

			/*
			*	@brief : outputs to terminal the keys for each element
			*	@note :
			*		Uses recursion to print each element key in order from least to greatest
			*		starting from left most node.
			*/
			void inorder(pointer root) 
			{
				if (root && root->data) 
				{
					inorder(root->lChld); 
					std::cout << root->data->first << " "; 
					inorder(root->rChld); 
				}
			}


			/*
			*	@brief : destroys entire branches / tree
			*	@note :
			*		starts at pointer given as parameter, and destroys all consecutive
			*		nodes that follow using recusion method. It calls destroyNode function
			*		on each node.
			*/
			pointer	_destroyTree(pointer node)
			{
				if (node && node->data)
				{
					this->_destroyTree(node->lChld);
					this->_destroyTree(node->rChld);
					node = this->destroyNode(node);
				}
				return (NULL);
			}

			/*
			*	@brief : destroys a node and it's data
			*	@note :
			*		if data (A.k.a : ft::pair<key_type, mapped_type> *) is != NULL
			*		function will destroy and deallocate data before destroying the node
			*/
			pointer	destroyNode(pointer node)
			{
				this->Size--;
				node->data = this->destroyData(node);
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				return (NULL);
			}

			/*
			*	@brief : destroys data within a node
			*	@note :
			*		if data (A.k.a : ft::pair<key_type, mapped_type> *) is != NULL
			*		function will destroy and deallocate data
			*/
			value_type_ptr	destroyData(pointer node)
			{
				if (!node->data)
					return (NULL);
				this->b_alloc.destroy(node->data);
				this->b_alloc.deallocate(node->data, 1);
				return (NULL);
			}

			/*
			*	@brief : allocates value
			*	@note :
			*		Each node contains a ft::pair<key, T> value
			*		This function will return a pointer to an allocated value
			*/
			value_type_ptr	newValue(const value_type &data)
			{
				value_type_ptr	_data = this->b_alloc.allocate(1);
				this->b_alloc.construct(_data, data);
				return (_data);
			}

			/*
			*	@brief : allocates newNode
			*	@note :
			*		Function allocates a newNode and initializes it's value
			*		With value pointer passed as parameter
			*/
			pointer newNode(value_type_ptr data)
			{
				pointer	node = this->alloc.allocate(1);
				this->alloc.construct(node, data);
				node->lChld = NULL;
				node->rChld = NULL;
				node->height = 0;
				return (node);
			}

			/*
			*	@brief : inserts a node into the tree
			*	@note :
			*		Function uses recursion method to find a slot for a new node
			*		the key_compare obj is used to compare the left and right
			*		branchs.
			*/
			pointer	insertNode(pointer r, pointer &node)
			{	
				if (!r)
					return (r = node);
				(key_cmp(node->data->first, r->data->first) ?
					r->lChld = this->insertNode(r->lChld, node)
					: r->rChld = this->insertNode(r->rChld, node));
				r = this->balance._balance(r);
				return (r);
			}

			pointer destroyAndReplace(pointer node)
			{
				pointer new_node;
				if (!node->lChld && !node->rChld)
					return (node = this->destroyNode(node));
				(!node->lChld && node->rChld ?
					new_node = node->rChld :
				(node->lChld && !node->rChld ?
					new_node = node->lChld :
					new_node = NULL));
				node = this->destroyNode(node);
				return (new_node);
			}

			pointer	deleteNode(pointer node, const value_type &data)
			{
				if (!node)
					return (node);
				if (this->key_cmp(data.first, node->data->first)) 
					node->lChld = deleteNode(node->lChld, data);
				else if (this->key_cmp(node->data->first, data.first))
					node->rChld = deleteNode(node->rChld, data);
				else
				{
					if (!node->lChld || !node->rChld)
						return (this->destroyAndReplace(node));
					pointer temp = this->min(node->rChld);
					this->b_alloc.destroy(node->data);
					this->b_alloc.construct(node->data, *temp->data);
					node->rChld = deleteNode(node->rChld, *temp->data);
				}
				node = balance._balance(node);
				return (node);
			}

			/*
			*	@brief : search tree for specific key
			*	@note :
			*		Function uses recursion method to search through the tree
			*		or branchs of the tree. Using key_compare type obj to compare
			*		the keys of each node
			*/
			pointer	search_tree(pointer node, const key_type &t) const
			{
				if (node && node->data && node->data->first != t)
				{
					node = (this->key_cmp(t, node->data->first) ?
							search_tree(node->lChld, t)
							: search_tree(node->rChld, t));
				}
				return (node);
			}

			/*
			*	@brief : init left or right
			*	@note :
			*		Function will initialize node's left or right child with ptr
			*		depending on the flag passed (left (Aka: 1) / right (Aka: 2)
			*/
			void	init_leftRight(pointer node, pointer ptr, int flag)
			{
				if (node)
				{
					if (ptr)
						ptr->prev = node;
					if (flag == left)
						node->lChld = ptr;
					else if (flag == right)
						node->rChld = ptr;
				}
			}

			/*
			*	@brief : sets the prev variable in nodes
			*	@note :
			*		Function will initialize the prev variable to the parent node
			*		using recursion
			*/
			void	setPrevVar(pointer node, pointer prev)
			{
				if (node && node->data)
				{
					setPrevVar(node->lChld, node);
					node->prev = prev;
					setPrevVar(node->rChld, node);
				}
			}
	};
};

#endif