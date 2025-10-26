#ifndef __LABEL_H__
#define __LABEL_H__

#include <list>
#include <iostream>
#include <cassert>

class label
{
public:
    std::list<double> lbl;

    label()
    {
    }

    label(std::list<double> &_label) : lbl(_label)
    {
    }

    void set_label(std::list<double> &_label)
    {
        assert(lbl.size() == _label.size());

        auto it_label = lbl.begin();
        auto it_label_ = _label.begin();

        while (it_label != lbl.end())
        {
            *it_label = *it_label_;
            ++it_label;
            ++it_label_;
        }
    }

    void print()
    {
        std::cout << "Label: [";
        for (auto field : lbl)
        {
            printf("%f ", field);
        }
        std::cout << "]" << std::endl;
    }
};

#endif
