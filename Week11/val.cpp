#include "val.h"


// arithmetic overloaded divide this by op
Value Value::operator/(const Value& op) const {
    if(this->GetType() != op.GetType()) {
        return Value(false);
    }
    return Value(true);
}


//overloaded equality operator of this with op
Value Value::operator==(const Value& op) const {
    if (this->GetType() == VERR || op.GetType() == VERR) {
        // If either operand is an error, consider them equal
        return Value(false);
    }

    if (this->GetType() == op.GetType()) {
        // Compare values based on their types
        switch (this->GetType()) {
            case VINT:
                return Value(this->GetInt() == op.GetInt());
            case VREAL:
                return Value(this->GetReal() == op.GetReal());
            case VSTRING:
                return Value(this->GetString() == op.GetString());
            case VBOOL:
                return Value(this->GetBool() == op.GetBool());
            default:
                throw std::logic_error("Comparison not supported for this type");
        }
    }

    // If types are different, return false
    return Value(false);
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
