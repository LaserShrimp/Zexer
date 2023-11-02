#include "Vect.hpp"

Vect::Vect():x{0.0}, y{0.0}{}
Vect::Vect(const Vect& v):x{v.x}, y{v.y}{}
Vect::Vect(const float x, const float y):x{x}, y{y}{}


void Vect::setX(const float x){
	this->x = x;
}
void Vect::setY(const float y){
	this->y = y;
}

float Vect::getX() const{
	return this->x;
}
float Vect::getY() const{
	return this->y;
}

void Vect::addX(const float x){
	this->x+= x;
}
void Vect::addY(const float y){
	this->y+= y;
}

Vect& Vect::add(const Vect& v){
	this->x+= v.getX();
	this->y+= v.getY();
	
	return *this;
}
Vect& Vect::sub(const Vect& v){
	this->x-= v.getX();
	this->y-= v.getY();
	
	return *this;
}

Vect& Vect::divideBy(const float f){
// 	Vect n(this->x, this->y);
	if(f != 0){
		this->x/= f;
		this->y/= f;
	} else {
		std::cout << "couldn't divide by zero..." << std::endl;
	}
	
	return *this;
}
Vect& Vect::multiplyBy(const float f){
// 	Vect n(this->x, this->y);
	this->x*= f;
	this->y*= f;
	
	return *this;
}

float Vect::norm() const{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
float Vect::angle(const Vect& v) const{
	return acos((*(this)*v)/((this->norm())*v.norm()));
}
float Vect::dist(const Vect& v) const{
	return sqrt(pow(v.getX()-(this->getX()), 2)+pow(v.getY()-(this->getY()), 2));
}

Vect& operator+(Vect& v1, const Vect& v2){
	return v1.add(v2);
}
Vect& operator-(Vect& v1, const Vect& v2){
	return v1.sub(v2);
}
float operator*(const Vect& v1, const Vect& v2){
	return v1.getX()*v2.getX() + v1.getY()*v2.getY();
}
