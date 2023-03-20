/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_def.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:35:30 by wismith           #+#    #+#             */
/*   Updated: 2023/03/18 13:06:51 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef NODE_DEF_HPP
# define NODE_DEF_HPP

namespace ft
{
	template <class T >
	struct node_def
	{
		public :
			typedef T				value_type;
			typedef value_type*		vp;
			vp						data;
			node_def<T>				*prev;
			node_def<T>				*lChld;
			node_def<T> 			*rChld;
			int						height;

			//! Constructors
			node_def (): data(), prev(), lChld(), rChld(), height(){}

			node_def (T *_data): data(_data), prev(), lChld(), rChld(), height() {}

			//! Destructor
			~node_def(){}
	};
};

#endif