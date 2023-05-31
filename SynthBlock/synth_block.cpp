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

bool BF_grammar::MORE(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B)
{
	bool res = false;

	for (auto &it : m_rules)
		for (auto first = it.second.m_right_part.begin(), second = (++it.second.m_right_part.begin()); second != it.second.m_right_part.end() && first != it.second.m_right_part.end(); ++first, ++second)
		{
			bool B_in_FIRST1_of_second = false;                  //Флаг говорит, что В входит в FIRST1 от second
			auto FIRST1_of_second = FIRST1(* second);             
			for (auto& that : FIRST1_of_second)
			{
				if (that->m_id == B->m_id)
					B_in_FIRST1_of_second = true;
			}

			if (((dynamic_cast<Terminal*>(B.get())) && *B == *(*second)) || B_in_FIRST1_of_second && (dynamic_cast<Non_terminal*>(first->get())))
			{
				auto first_end = END1(*first);
				for (auto& that : first_end)
				{
					if (that->m_id == A->m_id)
						res = true;
				}
			}
		}

	return res;
}

////////////////////////////////LESS//////////////////////////////////////
bool BF_grammar::LESS(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B)
{
	bool res = false;
	for (auto& it : m_rules)
		for (auto first = it.second.m_right_part.begin(), second = (++it.second.m_right_part.begin()); second != it.second.m_right_part.end() && first != it.second.m_right_part.end(); ++first, ++second)
			if (*A == *(*first) && (dynamic_cast<Non_terminal*>(second->get())))
			{
				auto sec_start1 = START1(*second);
				for (auto& that : sec_start1)
					if (that->m_id == B->m_id)
						res = true;
			}

	return res;
}

BF_grammar::BF_RELATION BF_grammar::check_relation(std::shared_ptr<Symbol> A, std::shared_ptr<Symbol> B)
{
	bool wasrelat = false;
	BF_RELATION relat_code = None;

	if (EQUAL(A, B))
	{
		wasrelat = true;
		relat_code = Equal;
	}
	if (LESS(A, B))
	{
		if (wasrelat)
			return LESS_EQ;
		wasrelat = true;
		relat_code = Less;
	}
	if (MORE(A, B))
	{
		if (wasrelat)
		{
			if (relat_code == Equal)
				return MORE_EQ;
			else
				return MORE_LESS;
		}
		relat_code = More;
	}

	return relat_code;
}

void BF_grammar::create_BF_table()
{
	for (auto& it : m_terminals)
		for (auto& that : m_terminals)
		{
			BF_RELATION rel = check_relation(it.second, that.second);
			/*if (rel == Error)
			{
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << std::endl;
			}*/

			switch (rel)
			{
			case LESS_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " < and == " << std::endl;
				break;
			case MORE_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and == " << std::endl;
				break;
			case MORE_LESS:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and < " << std::endl;
				break;
			default:
				m_BF_table[*it.second][*that.second] = rel;
				break;
			}
		}
	for (auto& it : m_non_terminals)
		for (auto& that : m_terminals)
		{
			BF_RELATION rel = check_relation(it.second, that.second);
			switch (rel)
			{
			case LESS_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " < and == " << std::endl;
				break;
			case MORE_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and == " << std::endl;
				break;
			case MORE_LESS:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and < " << std::endl;
				break;
			default:
				m_BF_table[*it.second][*that.second] = rel;
				break;
			}
		}
	for (auto& it : m_terminals)
		for (auto& that : m_non_terminals)
		{
			BF_RELATION rel = check_relation(it.second, that.second);
			switch (rel)
			{
			case LESS_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " < and == " << std::endl;
				break;
			case MORE_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and == " << std::endl;
				break;
			case MORE_LESS:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and < " << std::endl;
				break;
			default:
				m_BF_table[*it.second][*that.second] = rel;
				break;
			}
		}
	for (auto& it : m_non_terminals)
		for (auto& that : m_non_terminals)
		{
			BF_RELATION rel = check_relation(it.second, that.second);
			switch (rel)
			{
			case LESS_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " < and == " << std::endl;
				break;
			case MORE_EQ:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and == " << std::endl;
				break;
			case MORE_LESS:
				std::cout << "Relation conflict between " << it.second->m_name << " and " << that.second->m_name << " > and < " << std::endl;
				break;
			default:
				m_BF_table[*it.second][*that.second] = rel;
				break;
			}
		}


	/////////////////////////////Заполнение отношений с долларом//////////////////////////////////
	for (auto& it : m_terminals)
	{
		auto START_S = START1(m_non_terminals["[S]"]);
		bool in_start_s = false;
		for (auto& that : START_S)
			if (*that == *it.second)
				m_BF_table[*Dollar][*that] = Less;
	}
	for (auto& it : m_non_terminals)
	{
		auto START_S = START1(m_non_terminals["[S]"]);
		bool in_start_s = false;
		for (auto& that : START_S)
			if (*that == *it.second)
				m_BF_table[*Dollar][*that] = Less;
	}
	for (auto& it : m_terminals)
	{
		auto END_S = END1(m_non_terminals["[S]"]);
		bool in_END_s = false;
		for (auto that : END_S)
			if (*that == *it.second)
				m_BF_table[*that][*Dollar] = More;
	}
	for (auto& it : m_non_terminals)
	{
		auto END_S = END1(m_non_terminals["[S]"]);
		bool in_END_s = false;
		for (auto that : END_S)
			if (*that == *it.second)
				m_BF_table[*that][*Dollar] = More;
	}
}
