#pragma once
#include <vector>
#include <list>
#include <tuple>
#include<map>
#include<stack>
#include <iostream>
#include <fstream>
#include <set>



class SynthSymbol
{
public:
    std::string m_name;
    size_t      m_id;

    SynthSymbol();

    SynthSymbol(const SynthSymbol& obj);

    SynthSymbol(size_t id, std::string name);

    SynthSymbol& operator=(const SynthSymbol& obj);

    friend bool operator<(const SynthSymbol& obj, const SynthSymbol& obj1);
    
    friend bool operator==(const SynthSymbol& obj, const SynthSymbol& obj1);
    

};

class Terminal : public SynthSymbol
{
public:
    Terminal();

    Terminal(const Terminal& obj);

    Terminal(size_t id, std::string name);

    Terminal& operator=(const Terminal& obj);

    friend bool operator<(const Terminal& obj, const Terminal& obj1);

    friend bool operator==(const Terminal& obj, const Terminal& obj1);
};