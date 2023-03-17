/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:48:55 by wismith           #+#    #+#             */
/*   Updated: 2023/03/17 12:44:03 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public :
			typedef Container							container_type;
			typedef T									value_type;
			typedef typename container_type::size_type	size_type;

		protected :
			container_type	cont;

		public :
			explicit			stack(const container_type& ctnr = container_type()): cont(ctnr) {}

			bool				empty() const
			{
				return(this->cont.empty());
			}

			void				pop()
			{
				this->cont.pop_back();
			}

			void				push(const value_type& val)
			{
				this->cont.push_back(val);
			}

			size_type			size() const
			{
				return (this->cont.size());
			}

			 value_type&		top()
			 {
				return (this->cont.back());
			 }

			 const value_type&	top() const
			 {
				return (this->cont.back());
			 }

			 template <class T1, class Container1>
			friend bool	operator==(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);

			template <class T1, class Container1>
			friend bool	operator!=(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);

			template <class T1, class Container1>
			friend bool	operator<(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);

			template <class T1, class Container1>
			friend bool	operator<=(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);

			template <class T1, class Container1>
			friend bool	operator>(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);

			template <class T1, class Container1>
			friend bool	operator>=(const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs);
	};

	template <class T, class Container>
	bool	operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool	operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont != rhs.cont);
	}

	template <class T, class Container>
	bool	operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont < rhs.cont);
	}

	template <class T, class Container>
	bool	operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont <= rhs.cont);
	}

	template <class T, class Container>
	bool	operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont > rhs.cont);
	}

	template <class T, class Container>
	bool	operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
};

#endif