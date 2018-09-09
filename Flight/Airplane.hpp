#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

class Airplane {
private:
	int capacity;
    Airplane& operator=(const Airplane &other);
    Airplane(const Airplane &other);
public:
    Airplane(int capacity);
    int getCapacity() const;
    ~Airplane();
};

#endif
