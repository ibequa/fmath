//
//  fmath.cpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <cmath>

#include "fmath.hpp"

#define DEG2RAD(x) (x * M_PI / 180.0f)


fmath::mat4 fmath::frustum(float l, float r, float b, float t, float n, float f) {
    mat4 fr(0.0f);
    
    fr(0, 0)  = 2.0f * n / (r - l);
    fr(1, 1)  = 2.0f * n / (t - b);
    fr(0, 2)  = (r + l) / (r - l);
    fr(1, 2)  = (t + b) / (t - b);
    fr(2, 2) = -(f + n) / (f - n);
    fr(3, 2) = -1.0f;
    fr(2, 3) = -(2.0f * f * n) / (f - n);
    
    return fr;
}

fmath::mat4 fmath::perspective(float fovy, float aspect, float n, float f) {
    float tg = tanf(DEG2RAD(fovy / 2));
    float t = n * tg;
    float r = t * aspect;
    
    return frustum(-r, r, -t, t, n, f);
}

fmath::mat4 fmath::ortho(float l, float r, float b, float t, float n, float f) {
    mat4 m(0.0f);
    
    m(0, 0) = 2.0f / (r - l);
    m(1, 1) = 2.0f / (t - b);
    m(2, 2) = -2.0f / (f - n);
    m(3, 3) = 1.0f;
    m(0, 3) = - (r + l) / (r - l);
    m(1, 3) = - (t + b) / (t - b);
    m(2, 3) = - (f + n) / (f - n);
        
    return m;
}

fmath::mat4 fmath::lookAt(const vec3& position, const vec3& dir, const vec3& up) {
    fmath::mat4 m(0.0f);
    
    fmath::vec3 _camDir = (position - dir).normalized();
    
    fmath::vec3 camRight = (fmath::vec3::cross(up, _camDir)).normalized();
    fmath::vec3 camUp = (fmath::vec3::cross(_camDir, camRight)).normalized();
    
    m(0, 0) = camRight._x; m(0, 1) = camRight._y; m(0, 2) = camRight._z;
    m(1, 0) = camUp._x;   m(1, 1) = camUp._y;   m(1, 2) = camUp._z;
    m(2, 0) = _camDir._x;   m(2, 1) = _camDir._y;   m(2, 2) = _camDir._z;
    m(3, 3) = 1.0f;
    
    return fmath::translate(m, -position);
}

fmath::mat4 fmath::translate(const mat4& target, const vec3& vec) {
    mat4 tr_m;
    tr_m(0, 3) = vec._x;
    tr_m(1, 3) = vec._y;
    tr_m(2, 3) = vec._z;
    
    return target * tr_m;
}

fmath::mat4 fmath::scale(const mat4& target, const vec3& vec) {
    mat4 s_m;
    s_m(0, 0) = vec._x;
    s_m(1, 1) = vec._y;
    s_m(2, 2) = vec._z;
    
    return target * s_m;
}

fmath::mat4 fmath::quaternionToMatrix(const quaternion& q) {
   float n = q._w * q._w + q._x * q._x + q._y * q._y + q._z * q._z;
    float s = (n == 0) ? 0.0f : 2.0f / n;
    float wx = s * q._w * q._x, wy = s * q._w * q._y, wz = s * q._w * q._z;
    float xx = s * q._x * q._x, xy = s * q._x * q._y, xz = s * q._x * q._z;
    float yy = s * q._y * q._y, yz = s * q._y * q._z, zz = s * q._z * q._z;

    fmath::mat4 res;
    res(0, 0) = 1.0f - (yy + zz);   res(0, 1) = xy - wz;              res(0, 2) = xz + wy;
    res(1, 0) = xy + wz;            res(1, 1) = 1.0f - (xx + zz);     res(1, 2) = yz - wx;
    res(2, 0) = xz - wy;            res(2, 1) = yz + wx;              res(2, 2) = 1.0f - (xx + yy);
    
    return res;
}

float fmath::lerp(float x0, float x1, float t) {
    return x0 * (1.0f - t) + x1 * t;
}