#ifndef NUMBER_H
#define NUMBER_H

class Number   : public Object {
    protected:
        double value;
    public:
        Number(double val)
        {
            value = val;
        }

        // Addition
        Prototype operator+ ( Prototype& rval )
        {
            return Number( value + rval.toNum() );
        }

        // Subtraction
        Prototype operator- ( Prototype& rval )
        {
            return Number( value - rval.toNum() );
        }

        // Multiplication
        Prototype operator* ( Prototype& rval )
        {
            return Number( value * rval.toNum() );
        }

        // Division
        Prototype operator/ ( Prototype& rval )
        {
            return Number( value / rval.toNum() );
        }

        // Modulo
        Prototype operator% ( Prototype& rval )
        {
            return Number( (int)value % (int)rval.toNum() );
        }

        double toNum()
        {
            return value;
        }
};

#endif
