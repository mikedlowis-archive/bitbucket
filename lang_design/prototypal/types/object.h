#ifndef OBJECT_H
#define OBJECT_H

class Object : public Prototype {
    public:
        Object() : Prototype((Prototype*)Nil) {}
};

#endif
