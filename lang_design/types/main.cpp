#include <string>
#include <iostream>

template <typename T>
struct TypeWrapper
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

template <typename T>
struct TypeWrapper<const T>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

template <typename T>
struct TypeWrapper<const T&>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

template <typename T>
struct TypeWrapper<T&>
{
    typedef T TYPE;
    typedef const T CONSTTYPE;
    typedef T& REFTYPE;
    typedef const T& CONSTREFTYPE;
};

class Var
{
    private:
        class AVarContainer
        {
            public:
                virtual ~AVarContainer() {}
        };

        template<class T>
        struct VarContainer : public AVarContainer
        {
            T value;
            VarContainer(T val) : value(val) { }
            ~VarContainer() {}
        };

    protected:
        AVarContainer* value;

    public:
        Var() : value(0) {}

        template<class T>
        Var(T val) :
            value(new VarContainer<typename TypeWrapper<T>::TYPE>(val))
        {
        }

        template<class T>
        typename TypeWrapper<T>::REFTYPE val()
        {
            return dynamic_cast<VarContainer<typename TypeWrapper<T>::TYPE>&>(*value).value;
        }

        template<class T>
        typename TypeWrapper<T>::CONSTREFTYPE val() const
        {
            return dynamic_cast<VarContainer<typename TypeWrapper<T>::TYPE>&>(*value).value;
        }
};

int main(int argc, char** argv)
{
    Var foo = 3.3;
    foo = foo.val<double>() + 5;
    std::cout << "foo = " << foo.val<double>() << std::endl;

    foo = 5;
    std::cout << "foo = " << foo.val<int>() << std::endl;

    foo = std::string("foo!");
    std::cout << "foo = \"" << foo.val<std::string>() << "\"" << std::endl;

    Var arry[] = { 0, 1, 2.2, std::string("") };
    std::cout << "foo = " << arry[2].val<double>() << std::endl;
}
