#include "synth_block.h"

template<class T> inline
std::list<T> operator+(const std::list<T>& first, const std::list<T>& second)
{
	std::list<T> newList(first.cbegin(), first.cend());
	newList.insert(newList.end(), second.cbegin(), second.cend());
	return newList;
}

bool BF_grammar::EQUAL(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B)
{
	for (auto& it : m_rules)
	{
		for (auto first = it.second.m_right_part.begin(), second = (++it.second.m_right_part.begin()); second != it.second.m_right_part.end() && first != it.second.m_right_part.end(); ++first, ++second)
		{
			if (*A == *(*first) && *B == *(*second))
				return true;
		}
	}

	return false;
}
