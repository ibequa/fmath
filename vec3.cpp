//
//  vec3.cpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <cmath>
#include <iostream>

#include "vec3.hpp"

fmath::vec3::vec3() { _x = _y = _z = 0; }
fmath::vec3::vec3(float val) { _x = _y = _z = val; }
fmath::vec3::vec3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

float fmath::vec3::magnitude() const {
    return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
}

void fmath::vec3::normalize() {
    if (_x == _y == _z == 0)
        return;
    float mag = this->magnitude();
    _x /= mag; _y /= mag; _z /= mag;
}

fmath::vec3 fmath::vec3::normalized() const {
    if (_x == 0 && _y == 0 && _z == 0)
        return vec3(0.0f, 0.0f, 0.0f);
    
    float mag = this->magnitude();
    return fmath::vec3(this->_x / mag, this->_y / mag, this->_z / mag);
}

float fmath::vec3::dot(const fmath::vec3& a, const fmath::vec3& b) {
    return a._x * b._x + a._y * b._y + a._z * b._z;
}

fmath::vec3 fmath::vec3::cross(const fmath::vec3& a, const fmath::vec3& b) {
    fmath::vec3 res;
    
    res._x = (a._y * b._z) - (a._z * b._y);
    res._y = (a._z * b._x) - (a._x * b._z);
    res._z = (a._x * b._y) - (a._y * b._x);
    
    return res;
}

fmath::vec3 fmath::vec3::operator-() const {
    return fmath::vec3(-this->_x, -this->_y, -this->_z);
}

fmath::vec3 fmath::vec3::operator+(const fmath::vec3& vec) const {
    return fmath::vec3(this->_x + vec._x, this->_y + vec._y, this->_z + vec._z);
}

fmath::vec3& fmath::vec3::operator+=(const fmath::vec3& vec) {
    this->_x += vec._x;
    this->_y += vec._y;
    this->_z += vec._z;
    return *this;
}

fmath::vec3 fmath::vec3::operator-(const fmath::vec3& vec) const {
    return fmath::vec3(this->_x - vec._x, this->_y - vec._y, this->_z - vec._z);
}

fmath::vec3 fmath::vec3::operator*(const fmath::vec3& vec) const {
    return fmath::vec3(this->_x * vec._x, this->_y * vec._y, this->_z * vec._z);
}

fmath::vec3 fmath::operator*(float val, const fmath::vec3& vec) {
    return fmath::vec3(vec._x * val, vec._y * val, vec._z * val);
}

fmath::vec3 fmath::operator/(float val, const vec3& vec) {
    return fmath::vec3(val / vec._x, val / vec._y, val / vec._z);
}

fmath::vec3 fmath::vec3::operator*(float val) const {
    return fmath::vec3(this->_x * val, this->_y * val, this->_z * val);
}

fmath::vec3 fmath::vec3::operator/(const vec3& vec) const {
    return fmath::vec3(this->_x / vec._x, this->_y / vec._y, this->_z / vec._z);
}

fmath::vec3& fmath::vec3::operator/=(const vec3& vec) {
    this->_x /= vec._x;
    this->_y /= vec._y;
    this->_z /= vec._z;
    return *this;
}

fmath::vec3& fmath::vec3::operator*=(const vec3& vec) {
    this->_x *= vec._x;
    this->_y *= vec._y;
    this->_z *= vec._z;
    return *this;
}

bool fmath::vec3::operator==(const fmath::vec3& vec) const {
    return (vec._x == this->_x && vec._y == this->_y && vec._z == this->_z) ? true : false;
}

bool fmath::vec3::operator!=(const vec3& vec) const {
    return (vec._x != this->_x || vec._y != this->_y || vec._z != this->_z) ? true : false;
}

std::ostream& fmath::operator<<(std::ostream& os, const fmath::vec3& vec) {
    os << "(" << vec._x << "; " << vec._y << "; " << vec._z << ")";
    return os;
}

std::istream& fmath::operator>>(std::istream& is, fmath::vec3& vec) {
    is >> vec._x; is >> vec._y; is >> vec._z;
    return is;
}