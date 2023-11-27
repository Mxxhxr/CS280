#include "val.h"


// arithmetic overloaded divide this by op
Value Value::operator/(const Value& op) const {
    if (GetType() == VINT && op.GetType() == VINT) {
        return Value(Itemp / op.GetInt());
    }
    else if (GetType() == VREAL && op.GetType() == VREAL) {
        return Value(Rtemp / op.GetReal());
    }
    else if(GetType() == VREAL && op.GetType() == VINT) {
        return Value(Rtemp / op.GetInt());
    }
    else if(GetType() == VINT && op.GetType() == VREAL) {
        return Value(Itemp / op.GetReal());
    }
    return Value();
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
        else if(IsBool() && op.IsBool()) {
            return Value(Btemp == op.GetBool());
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
    if(GetType() != VBOOL) {
        return Value();
    }
    else if(GetType() == VBOOL && oper.GetType() == VERR) {
        return Value();
    }
    else if(GetType() == VERR && oper.GetType() == VBOOL) {
        return Value();
    }
    else if(GetType() == VBOOL && oper.GetType() == VINT) {
        return Value();
    }
    else if(GetType() == VBOOL && oper.GetType() == VREAL) {
        return Value();
    }
    else if(GetType() == VBOOL && oper.GetType() == VSTRING) {
        return Value();
    }
    else {
        return Value(Btemp == oper.GetBool());
    }
    return Value();
}

// arithmetic overloaded modulus this by op
Value Value::operator%(const Value& oper) const {
    if (GetType() == VINT && oper.GetType() == VINT) {
        // int mod
        return Value(Itemp % oper.GetInt());
    } 
    else {
        return Value();
    }
    return Value();
}