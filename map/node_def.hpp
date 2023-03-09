/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_def.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:35:30 by wismith           #+#    #+#             */
/*   Updated: 2023/02/27 23:24:53 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef NODE_DEF_HPP
# define NODE_DEF_HPP

namespace ft
{
	template <class T >
	class node_def
	{
		public :
			T			*data;
			node_def<T>	*prev;
			node_def<T>	*lChld;
			node_def<T> *rChld;
			int			height;

		public :
			//! Constructors
			node_def (): data(), prev(), lChld(), rChld(), height(){}

			node_def (T *_data): data(_data), prev(), lChld(), rChld(), height() {}

			node_def (const node_def<T> &t) : data(t.data), prev(t.prev), lChld(t.lChld), rChld(t.rChld), height(t.height) {}

			//! Destructor
			~node_def(){}

			//! Copy assignment op overload
			node_def &operator=(const node_def<T> &t)
			{
				if (this != &t)
				{
					this->data = t.data;
					this->lChld = t.lChld;
					this->rChld = t.rChld;
				}
				return (*this);
			}
	};
};

#endif