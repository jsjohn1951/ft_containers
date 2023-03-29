/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:07:04 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 17:09:00 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BALANCE_HPP
# define BALANCE_HPP

# include "node_def.hpp"
# include "../utils/iterator_traits.hpp"
# include "../utils/utility.hpp"
# include <functional>

namespace ft
{
	/*
	*	@brief : definition of object used to balance the nodes in the tree
	*		at insert and deletion.
	*/
	template < class Key, class T, class Compare = std::less<Key> >
	class balance
	{
		public :
			typedef Compare																key_compare;
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef value_type*															value_type_ptr;
			typedef ft::node_def<value_type>											node_type;
			typedef node_type*															pointer;
			typedef std::size_t															size_type;

		public :
			/*
			*	@brief : simple constructors 
			*/
			balance() {}
			balance(const balance &nh)
			{ (void) nh; }
			balance(pointer n)
			{ this->_balance(n);}
			
			/*
			*	@brief : destructor
			*/
			~balance(){}

			balance	&operator=(const balance &nh)
			{
				(void) nh;
				return  (*this);
			}

			/*
			*	@brief : uses recursion to set the height for each node
			*	@note :
			*		if root passed to function is not NULL, and contains data (is not a sentinal)
			*			recurse to leftchild, with argument i = i + 1.
			*		Once it reaches the leaf or sentinal, return i.
			*	@visual :
			*					1 <- height = 2
			*				  /  \
			*   			0     2 <- height = 1
			*			           \
			*						3 <- height = 0
			*/
			int	nodeHeight(pointer r, int i)
			{
				int	size1 = 0;
				int	size2 = 0;
				if (r && r->data)
				{
					size1 = nodeHeight(r->lChld, i + 1);
					size2 = nodeHeight(r->rChld, i + 1);
					return (size1 > size2 ? size1 : size2);
				}
				return (i);
			}

			/*
			*	@brief : returns the height of the node if the node is allocated
			*/
			int	getNodeHeight(pointer r)
			{
				return (!r ? 0 : r->height);
			}

			/*
			*	@brief : returns the difference between the height of the left and right child of the root
			*	@note :
			*		returns 0 if node is not allocated
			*/
			int	difference(pointer r)
			{
				return (!r ? 0 : this->getNodeHeight(r->lChld)
					- this->getNodeHeight(r->rChld));
			}

			/*
			*	@brief : rotates a node left inorder to balance the tree
			*	@note :
			*		after the rotation, resets the node heights, and returns the new root (x)
			*	@visual :
			*			1)	6 <- r    			2)  8 <- x
			*				\					   /
			*				 8 <- x	 			  6  <- r   
			*			   /		 			  \
			*			  7 <- y				   7 <- y
			*/
			pointer	left_rotate(pointer r)
			{
				pointer x = r->rChld;
			    pointer y = x->lChld;

				x->lChld = r;
				r->rChld = y;
				r->height = this->nodeHeight(r, 0);
				x->height = this->nodeHeight(x, 0);
				return (x);
			}

			/*
			*	@brief : rotates a node right inorder to balance the tree
			*	@note :
			*		after the rotation, resets the node heights, and returns the new root (x)
			*	@visual :
			*			1)	8 <- r    			2)  6 <- x
			*			   /					     \
			*			  6 <- x	 			      8  <- r   
			*			  \		 			         /
			*			   7 <- y				    7 <- y
			*/
			pointer	right_rotate(pointer r)
			{
				pointer x = r->lChld;
			    pointer y = x->rChld;

				x->rChld = r;
				r->lChld = y;
				r->height = this->nodeHeight(r, 0);
				x->height = this->nodeHeight(x, 0);
				return (x);
			}

			/*
			*	@brief : performs left_rotation on left_child, and right rotation on root
			*	@note :
			*		returns the new root node
			*	@visual :
			*			1)	   9 <- r			2)	  9 <- r    3)   8 
			*				 /						 /			    / \
			*			  	6 <- r->lChld    	   8               6   9
			*				\					  /				   \
			*				 8 	 			     6                  7
			*			   /		 			 \
			*			  7 				      7 
			*/
			pointer	leftRight(pointer r)
			{
				r->lChld = this->left_rotate(r->lChld);
				return (this->right_rotate(r));
			}

			/*
			*	@brief : performs left_rotation on left_child, and right rotation on root
			*	@note :
			*		returns the new root node
			*	@visual :
			*			1)	   8 <- r			2)	  8 <- r    3)       9
			*				    \					   \			    / \
			*			  	    12 <- r->rChld    	    9             8   12
			*				   /					    \				  /  
			*				 9 	 			             12              10       
			*			     \		 					/ 
			*			     10 				       10    
			*/
			pointer rightLeft(pointer r)
			{
				r->rChld = this->right_rotate(r->rChld);
				return (this->left_rotate(r));
			}

			/*
			*	@brief : function to initialize the balancing process
			*	@note :
			*		1)	sets the height of the root node taken as argument
			*		2)	Calculate the difference and store in an int (diff)
			*		if diff is less than 2 and greater than -2 [-1, 1] then
			*			return
			*		if diff is greater than 1, perform right_rotate, then leftright
			*			else diff is less than -1 and function will perform left_rotate, then
			*				followed by rightLeft rotate.
			*/
			pointer	_balance(pointer r)
			{
				r->height = this->nodeHeight(r, 0);
				int	diff = this->difference(r);

				if (diff <= 1 && diff >= -1)
					return (r);
				
				(diff > 1 ?
					(this->difference(r->lChld) >= 0 ?
						r = this->right_rotate(r) :
						r = this->leftRight(r))
				:
					(this->difference(r->rChld) <= 0 ?
						r = this->left_rotate(r) :
						r = this->rightLeft(r)));

				return (r);
			}
	};
};

#endif