/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:07:04 by wismith           #+#    #+#             */
/*   Updated: 2023/03/02 17:17:11 by wismith          ###   ########.fr       */
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
			balance() {}
			balance(const balance &nh)
			{
				if (this != &nh)
					*this = nh;
			}

			balance(pointer n)
			{
				this->_balance(n);
			}
			~balance(){}

			balance	&operator=(const balance &nh)
			{
				(void) nh;
				return  (*this);
			}

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

			int	getNodeHeight(pointer r)
			{
				return (!r ? 0 : r->height);
			}

			int	difference(pointer r)
			{
				return (!r ? 0 : this->getNodeHeight(r->lChld)
					- this->getNodeHeight(r->rChld));
			}

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

			pointer	leftRight(pointer r)
			{
				r->lChld = this->left_rotate(r->lChld);
				return (this->right_rotate(r));
			}

			pointer rightLeft(pointer r)
			{
				r->rChld = this->right_rotate(r->rChld);
				return (this->left_rotate(r));
			}

			pointer	_balance(pointer r)
			{
				r->height = this->nodeHeight(r, 0);
				int	diff = this->difference(r);

				if (diff <= 1 && diff >= -1)
					return (r);
				
				(diff > 1 ?
					(this->difference(r->lChld) >= 0 ?
						r = this->right_rotate(r) :
						r = this->leftRight(r)) :
					(this->difference(r->rChld) <= 0 ?
						r = this->left_rotate(r) :
						r = this->rightLeft(r)));

				return (r);
			}
	};
};

#endif