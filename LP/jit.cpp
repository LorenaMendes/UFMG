#include<iostream>
class ThreeDPoint { public: int x; int y; int z; };
class DateType { public: int day; int month; int year; };
main() {
ThreeDPoint *p = new ThreeDPoint();
p->x = 7; p->y = 7; p->z = 1822;
DateType *d = (DateType*)p;
std::cout << d->day << ", " << d->month << ", " << d->year << std::endl;
}