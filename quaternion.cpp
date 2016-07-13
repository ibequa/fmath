//
//  quaternion.cpp
//  Flexo
//
//  Created by Ilya on 10/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <cmath>
#include <iostream>
#include "quaternion.hpp"

const float fmath::quaternion::DEG2RAD = M_PI / 180.0f;

fmath::quaternion::quaternion() : _x(0), _y(0), _z(0), _w(1) {}
fmath::quaternion::quaternion(const fmath::vec3& vec): _x(vec._x), _y(vec._y), _z(vec._z), _w(0) {}
fmath::quaternion::quaternion(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}
fmath::quaternion::quaternion(float scalar, const vec3& vec) : _x(vec._x), _y(vec._y), _z(vec._z), _w(scalar) {}

fmath::quaternion fmath::quaternion::fromEuler(const fmath::vec3& euler) {
    float s_roll = sinf(DEG2RAD * (euler._x / 2.0f));
    float c_roll = cosf(DEG2RAD * (euler._x / 2.0f));
    fmath::quaternion q_roll(s_roll, 0.0f, 0.0f, c_roll);
    
    float s_pitch = sinf(DEG2RAD * (euler._y / 2.0f));
    float c_pitch = cosf(DEG2RAD * (euler._y /2.0f));
    fmath::quaternion q_pitch(0.0f, s_pitch, 0.0f, c_pitch);
    
    float s_yaw = sinf(DEG2RAD * (euler._z / 2.0f));
    float c_yaw = cosf(DEG2RAD * (euler._z / 2.0f));
    fmath::quaternion q_yaw(0.0f, s_yaw, 0.0f, c_yaw);
    
    return (q_yaw * q_pitch * q_roll);
}

fmath::quaternion fmath::quaternion::normalized() const {
    if (_x == 0 && _y == 0 && _z == 0 && _w == 0)
        return *this;
    float mag = magnitude();
    return quaternion(_x / mag, _y / mag, _z / mag, _w / mag);
}

void fmath::quaternion::normalize() {
    if (_x == 0 && _y == 0 && _z == 0 && _w == 0)
        return;
    float mag = magnitude();
    _x /= mag; _y /= mag; _z /= mag; _w /= mag;
}

float fmath::quaternion::magnitude() const { return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2) + pow(_w, 2)); }

fmath::quaternion fmath::quaternion::inverse() const {
    fmath::quaternion con = this->conjugate();
    float mag = this->magnitude();
    
    return quaternion(con._x / mag, con._y / mag, con._z / mag, con._w / mag);
}

fmath::quaternion fmath::quaternion::operator+(const fmath::quaternion& q) const {
    return quaternion(_x + q._x, _y + q._y, _z + q._z, _w + q._w);
}

fmath::quaternion fmath::quaternion::operator-() const {
    return quaternion(-_x, -_y, -_z, -_w);
}

fmath::quaternion fmath::operator*(const quaternion& a, const quaternion& b) {
    fmath::quaternion q;
    q._x = a._x * b._w + a._y * b._z - a._z * b._y + a._w * b._x;
    q._y = -a._x * b._z + a._y * b._w + a._z * b._x + a._w * b._y;
    q._z =  a._x * b._y - a._y * b._x + a._z * b._w + a._w * b._z;
    q._w = -a._x * b._x - a._y * b._y - a._z * b._z + a._w * b._w;
    return q;
}

fmath::quaternion& fmath::quaternion::operator*=(const quaternion& q) {
    *this = *this * q;
    return *this;
}

std::ostream& fmath::operator<<(std::ostream& os, const quaternion& q) {
    os << "(" << q._w << ", " << q._x << "i, " << q._y << "j, " << q._z << "k)";
    return os;
}

std::istream& fmath::operator>>(std::istream& is, quaternion& q) {
    is >> q._w; is >> q._x; is >> q._y; is >> q._z;
    return is;
}