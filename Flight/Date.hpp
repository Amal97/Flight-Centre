#ifndef TIME_HPP
#define TIME_HPP

class Date{
private:
	int day;
	int hour;
public:
    Date(int day, int hour);
    int getDay() const;
    int getHour() const;
    void addTime(int hours);
    bool isLessThan(const Date &other) const;
    void changeDateTo(int day, int hour);
    ~Date();
};

#endif
