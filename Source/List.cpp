#include "pch.h"
#include "List.h"
#include "Number.h"

List::List(std::shared_ptr<std::vector<std::any>> value, string type) : valueType(type)
{
    values = value;
}

List List::added_to(std::any value, string type)
{
    //Adding of a list elementn type
    if (!values->empty()) //Hard Check
    {
        if (values->at(0).type() == value.type())
        {
            values->push_back(value);
        }
        else
            CW_CORE_ERROR("Invalid Type To add to List");
    }
    else if (type == valueType) //Manual check for empty list 
    {
        values->push_back(value);
    }
    //Adding of Another List
    else if (type == "List") 
    {
        List newList = any_cast<List>(value);
        if (newList.getValues() != nullptr) {
            if (newList.getValueType() == valueType) {
                std::shared_ptr<std::vector<std::any>> values = newList.getValues();
                for (auto& val : *values)
                {
                    this->values->push_back(val);
                }
            }else
            {
                CW_CORE_ERROR("Tried to add List of incorrect type");
            }
        }
        else 
        {
            CW_CORE_WARN("Tried to add an empty List");
        }
    }
    else 
    {
        CW_CORE_ERROR("Invalid Type To add to List");
    }
    return *this;
}

void List::remove(std::shared_ptr<Number> index)
{
    if (!values->empty())
    {
        try
        {
            int val = index->getValue() - 1;
            values->erase(values->begin() + val);
        }
        catch( ... )
        {
            CW_CORE_ERROR("Could Not remove Item, Index {} not found. List size is {}", index->getValue(), values->size());
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
            int val = index->getValue() - 1;
            return values->erase(values->begin() + val);
        }
        catch (...)
        {
            CW_CORE_ERROR("Could Not return Item, Index {} not found. List size is {}", index->getValue(), values->size());
            
        }
    }
    else
    {
        CW_CORE_ERROR("Could Not return Item from an Empty List");
    }
    return std::any();
}

const string& List::getValueType() const
{
    return valueType;
}

const std::shared_ptr<std::vector<std::any>> List::getValues() const
{
    return values;
}
