#include "pch.h"
#include "List.h"
#include "Number.h"

List::List(std::shared_ptr<std::vector<Number>> value) 
{
    values = value;
}

List List::added_to(Number value)
{
    if (!values->empty()) {
        if (values->at(0).getValue().type() == value.getValue().type())
        {
            values->push_back(value);
        }
        else
            CW_CORE_ERROR("Invalid Type To add to List");
    }
    else {
        values->push_back(value);
    }
    return *this;
}

List List::concatenated(Number value)
{
    List* newList;
    try {
       newList = new List(any_cast<List>(value.getValue()));
    }
    catch (...) 
    {
        CW_CORE_WARN("Tried to concatenate a list with non list type");
        return added_to(value);
    }


    if (newList->getValues() != nullptr && !newList->getValues()->empty()) { //check if list empty
        if (values->empty())
        {
            return *newList;
        }
        if (newList->getValues()->at(0).getValue().type() == values->at(0).getValue().type()) //Check types of list are same 
        {
            //Concatonating list
            for (auto& val : *newList->getValues())
            {
                this->values->push_back(val);
            }
        }
        else
        {
            CW_CORE_ERROR("Tried to add List of incorrect type");
        }
    }
    else
    {
        CW_CORE_WARN("Tried to add an empty List");
    }

    delete newList;

    return *this;
}

void List::remove(std::shared_ptr<Number> index)
{
    if (!values->empty())
    {
        try
        {
            int val = any_cast<int>(index->getValue());
            if(val < values->size())
                values->erase(values->begin() + val); 
            else
            {
                if (any_cast<int>(index->getValue())) {
                    CW_CORE_ERROR("Could Not remove Item, Index {} not found. List size is {}", any_cast<int>(index->getValue()), values->size());
                }
                else {
                    CW_CORE_ERROR("Could Not remove Item, Index type invalid. List size is {}", any_cast<int>(index->getValue()), values->size());
                }
            }
        }
        catch( ... )
        {
            if (any_cast<int>(index->getValue())) {
                CW_CORE_ERROR("Could Not remove Item, Index {} not found. List size is {}", any_cast<int>(index->getValue()), values->size());
            }
            else {
                CW_CORE_ERROR("Could Not remove Item, Index type invalid. List size is {}", any_cast<int>(index->getValue()), values->size());
            }
        }

    }else
    {
        CW_CORE_ERROR("Could Not remove Item from an Empty List");
    }
}

std::any List::retrieve(std::shared_ptr<Number> index)
{
    if (!values->empty())
    {
        try
        {
            int val = any_cast<int>(index->getValue());
            return values->at(val).getValue();
        }
        catch (...)
        {
            if (any_cast<int>(index->getValue())) {
                CW_CORE_ERROR("Could Not retrieve Item, Index {} not found. List size is {}", any_cast<int>(index->getValue()), values->size());
            }
            else {
                CW_CORE_ERROR("Could Not retrieve Item, Index type invalid. List size is {}", any_cast<int>(index->getValue()), values->size());
            }
            
        }
    }
    else
    {
        CW_CORE_ERROR("Could Not return Item from an Empty List");
    }
    return std::any();
}

const std::shared_ptr<std::vector<Number>> List::getValues() const
{
    return values;
}
