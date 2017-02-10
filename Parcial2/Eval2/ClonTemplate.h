#pragma once

template <class Base, class SubClase>
class ClonTemplate : public Base
{
public:
    //using Base::Base;

    virtual Base* clonar()
    {
        return new SubClase(dynamic_cast<SubClase&>(*this));
    }
};
