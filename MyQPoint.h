#ifndef MYQPOINT_H
#define MYQPOINT_H

#include<QPoint>
#include<QColor>
#include <vector>
using namespace std;
class MyQPoint:public QPoint{
public:
	MyQPoint();
	MyQPoint(QPoint point);
	MyQPoint(QColor color, long long index);
	~MyQPoint(){};
	void setIndex(long long index);
	void setColor(QColor color);
	long long getIndex();
	QColor getColor();
	vector<int> getQ();
	void setQ(vector<int> Q);

public:
	long long index_;
	QColor color_;
	vector<int> Q_;

};

#endif // !MYQPOINT_H
