#ifndef __VECT_HPP__
#define __VECT_HPP__

#include <iostream>
#include <cmath>

class Vect{
private:
	float x;
	float y;
	
protected:
public:
	Vect();
	Vect(const float x, const float y);
	Vect(const Vect& v);
	
	void setX(const float x);
	void setY(const float y);
	
	float getX() const;
	float getY() const;
	
	void addX(const float x);
	void addY(const float y);
	
	Vect& add(const Vect& v);
	Vect& sub(const Vect& v);
	Vect& divideBy(const float f);
	Vect& multiplyBy(const float f);
	
	float norm() const;
	float angle(const Vect& v) const;
	float dist(const Vect& v) const;
};

std::ostream& operator<<(std::ostream& out, Vect &v);
Vect& operator+(Vect& v1, const Vect& v2);
Vect& operator-(Vect& v1, const Vect& v2);
float operator*(const Vect& v1, const Vect& v2); //Scalar

#endif
