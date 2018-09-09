#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <string>

/*
The Human class is a base class for all other subclasses. It defines the interface
which Human must implement, and provides some basic functionality all Human classes will need.
*/
class Human {
protected:
    std::string name;
    Human(const std::string &name);
public:
    /*
    The destructor for any polymorphic base class *must* be declared virtual, otherwise when you
    delete an object through a polymorphic pointer the base class destructor will be called instead
    of the one in the derived class.
    */
    virtual ~Human();
    virtual std::string getName() const;
};

#endif
