#include <stdio.h>
typedef struct ThreeDPointType { int x; int y; int z; } ThreeDPoint;
typedef struct DateType { int day; int month; int year; } Date;
int days(Date d) { return d.day; };
int main() {
ThreeDPoint p;
p.x = 7; p.y = 7; p.z = 1822;
printf("%d\n", days(p));
}
