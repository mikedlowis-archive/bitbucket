#ifndef PROTOTYPE_H
#define PROTOTYPE_H

class Prototype {
    protected:
        Prototype* parent;
        map<string,Prototype*> prototype;
    public:
        Prototype(Prototype* proto) : parent(proto), prototype() {}
        virtual ~Prototype() {};

        Prototype& operator[] ( const string& x )
        {
            Prototype* ret = prototype[x];
            if( (ret == Nil) || (ret == NULL) )
            {
                ret = &(*parent)[x];
            }
            return *ret;
        }
        //---------------------------------------------------------------------
        // Operators
        //---------------------------------------------------------------------

        // Array index
        virtual Prototype operator[] ( unsigned int x )
        {
            throw exception();
        }

        // Function Application
        virtual Prototype operator() (void)
        {
            throw exception();
        }

        virtual Prototype operator() (Prototype& args)
        {
            throw exception();
        }

        // Addition
        virtual Prototype operator+ ( Prototype& rval )
        {
            throw exception();
        }

        // Subtraction
        virtual Prototype operator- ( Prototype& rval )
        {
            throw exception();
        }

        // Multiplication
        virtual Prototype operator* ( Prototype& rval )
        {
            throw exception();
        }

        // Division
        virtual Prototype operator/ ( Prototype& rval )
        {
            throw exception();
        }

        // Modulo
        virtual Prototype operator% ( Prototype& rval )
        {
            throw exception();
        }

        // Type Conversions
        virtual bool toBool()
        {
            throw exception();
        }

        virtual double toNum()
        {
            throw exception();
        }

        virtual string toString()
        {
            throw exception();
        }

        virtual char toChar()
        {
            throw exception();
        }
};

#endif
