#include "val.h"


// arithmetic overloaded divide this by op
Value Value::operator/(const Value& op) const {
    if(this->GetType() != op.GetType()) {
        return Value(false);
    }
    return Value(true);
}


//overloaded equality operator of this with op
Value Value::operator==(const Value &op) const
{
    if (GetType() == op.GetType()) {
        // same type
        if (IsInt() && op.IsInt()) {
            return Value(Itemp == op.GetInt());
        }
        else if (IsReal() && op.IsReal()) {
            return Value(Rtemp == op.GetReal());
        }
        else if (IsString() && op.IsString()) {
            return Value(Stemp == op.GetString());
        }
    }
    else {
        if (IsInt() && op.IsReal()) {
            return Value(false);
        }
        else if (IsReal() && op.IsInt()) {
            return Value(false);
        }
    }
    return Value();
}



//Overloaded Anding operator
Value Value::operator&&(const Value& oper) const {
    if(this->GetType() != oper.GetType()) {
        return Value(false);
    }
    return Value(true);
}


// arithmetic overloaded modulus this by op
Value Value::operator%(const Value& oper) const {
    if(this->GetType() != oper.GetType()) {
        return Value(false);
    }
    return Value(true);
}   
