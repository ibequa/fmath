//
//  mat4.cpp
//  Flexo
//
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <iostream>
#include <cmath>

#include "mat4.hpp"

void fmath::mat4::swap(float* x, float* y) {
    float t = *x;
    *x = *y;
    *y = t;
}

fmath::mat4 fmath::mat4::transposed() const {
    fmath::mat4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m(i, j) = this->data[i][j];
    return m;
}

fmath::mat4 fmath::mat4::inversed() const {
    fmath::mat4 a(*this);
    int indxc[4], indxr[4], ipiv[4];
    int i, j, icol = 0, irow = 0, ir, ic;
    float big, dum, pivinv, temp, bb;
    ipiv[0] = -1;
    ipiv[1] = -1;
    ipiv[2] = -1;
    ipiv[3] = -1;
    for (i = 0; i < 4; i++) {
        big = 0.0f;
        for (j = 0; j < 4; j++) {
            if (ipiv[j] != 0) {
                if (ipiv[0] == -1) {
                    if ((bb = (float) fabs(a(j, 0))) > big) {
                        big = bb;
                        irow = j;
                        icol = 0;
                    }
                } else if (ipiv[0] > 0) {
                    return a;
                }
                if (ipiv[1] == -1) {
                    if ((bb = (float) fabs((float) a(j, 1))) > big) {
                        big = bb;
                        irow = j;
                        icol = 1;
                    }
                } else if (ipiv[1] > 0) {
                    return a;
                }
                if (ipiv[2] == -1) {
                    if ((bb = (float) fabs((float) a(j, 2))) > big) {
                        big = bb;
                        irow = j;
                        icol = 2;
                    }
                } else if (ipiv[2] > 0) {
                    return a;
                }
                if (ipiv[3] == -1) {
                    if ((bb = (float) fabs((float) a(j, 3))) > big) {
                        big = bb;
                        irow = j;
                        icol = 3;
                    }
                } else if (ipiv[3] > 0) {
                    return a;
                }
            }
        }
        ++(ipiv[icol]);
        if (irow != icol) {
            temp = a(irow, 0);
            a(irow, 0) = a(icol, 0);
            a(icol, 0) = temp;
            temp = a(irow, 1);
            a(irow, 1) = a(icol, 1);
            a(icol, 1) = temp;
            temp = a(irow, 2);
            a(irow, 2) = a(icol, 2);
            a(icol, 2) = temp;
            temp = a(irow, 3);
            a(irow, 3) = a(icol, 3);
            a(icol, 3) = temp;
        }
        indxr[i] = irow;
        indxc[i] = icol;
        if (a(icol, icol) == 0.0) {
            return a;
        }
        pivinv = 1.0f / a(icol, icol);
        a(icol, icol) = 1.0f;
        a(icol, 0) *= pivinv;
        a(icol, 1) *= pivinv;
        a(icol, 2) *= pivinv;
        a(icol, 3) *= pivinv;
        if (icol != 0) {
            dum = a(0, icol);
            a(0, icol) = 0.0f;
            a(0, 0) -= a(icol, 0) * dum;
            a(0, 1) -= a(icol, 1) * dum;
            a(0, 2) -= a(icol, 2) * dum;
            a(0, 3) -= a(icol, 3) * dum;
        }
        if (icol != 1) {
            dum = a(1, icol);
            a(1, icol) = 0.0f;
            a(1, 0) -= a(icol, 0) * dum;
            a(1, 1) -= a(icol, 1) * dum;
            a(1, 2) -= a(icol, 2) * dum;
            a(1, 3) -= a(icol, 3) * dum;
        }
        if (icol != 2) {
            dum = a(2, icol);
            a(2, icol) = 0.0f;
            a(2, 0) -= a(icol, 0) * dum;
            a(2, 1) -= a(icol, 1) * dum;
            a(2, 2) -= a(icol, 2) * dum;
            a(2, 3) -= a(icol, 3) * dum;
        }
        if (icol != 3) {
            dum = a(3, icol);
            a(3, icol) = 0.0f;
            a(3, 0) -= a(icol, 0) * dum;
            a(3, 1) -= a(icol, 1) * dum;
            a(3, 2) -= a(icol, 2) * dum;
            a(3, 3) -= a(icol, 3) * dum;
        }
    }
    if (indxr[3] != indxc[3]) {
        ir = indxr[3];
        ic = indxc[3];
        temp = a(0, ir);
        a(0, ir) = a(0, ic);
        a(0, ic) = temp;
        temp = a(1, ir);
        a(1, ir) = a(1, ic);
        a(1, ic) = temp;
        temp = a(2, ir);
        a(2, ir) = a(2, ic);
        a(2, ic) = temp;
        temp = a(3, ir);
        a(3, ir) = a(3, ic);
        a(3, ic) = temp;
    }
    if (indxr[2] != indxc[2]) {
        ir = indxr[2];
        ic = indxc[2];
        temp = a(0, ir);
        a(0, ir) = a(0, ic);
        a(0, ic) = temp;
        temp = a(1, ir);
        a(1, ir) = a(1, ic);
        a(1, ic) = temp;
        temp = a(2, ir);
        a(2, ir) = a(2, ic);
        a(2, ic) = temp;
        temp = a(3, ir);
        a(3, ir) = a(3, ic);
        a(3, ic) = temp;
    }
    if (indxr[1] != indxc[1]) {
        ir = indxr[1];
        ic = indxc[1];
        temp = a(0, ir);
        a(0, ir) = a(0, ic);
        a(0, ic) = temp;
        temp = a(1, ir);
        a(1, ir) = a(1, ic);
        a(1, ic) = temp;
        temp = a(2, ir);
        a(2, ir) = a(2, ic);
        a(2, ic) = temp;
        temp = a(3, ir);
        a(3, ir) = a(3, ic);
        a(3, ic) = temp;
    }
    if (indxr[0] != indxc[0]) {
        ir = indxr[0];
        ic = indxc[0];
        temp = a(0, ir);
        a(0, ir) = a(0, ic);
        a(0, ic) = temp;
        temp = a(1, ir);
        a(1, ir) = a(1, ic);
        a(1, ic) = temp;
        temp = a(2, ir);
        a(2, ir) = a(2, ic);
        a(2, ic) = temp;
        temp = a(3, ir);
        a(3, ir) = a(3, ic);
        a(3, ic) = temp;
    }
    return a;
}

void fmath::mat4::loadIdentity() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = (i == j) ? 1.0f : 0.0f;
}

fmath::mat4::mat4() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = (i == j) ? 1.0f : 0.0f;
}

fmath::mat4::mat4(float value) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[i][j] = value;
}

const float* fmath::mat4::rawData() const { return (float*) data; }

fmath::mat4 fmath::operator+(const fmath::mat4& a, const fmath::mat4& b) {
    fmath::mat4 res(0.0f);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.data[i][j] = a.data[i][j] + b.data[i][j];
    return res;
}

// column-major multiplication
fmath::mat4 fmath::operator*(const fmath::mat4& a, const fmath::mat4& b) {
    fmath::mat4 res(0.0f);
   
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                res.data[j][i] += a.data[k][i] * b.data[j][k];
    
    return res;
}

fmath::mat4 fmath::mat4::operator*(float val) const {
    fmath::mat4 res(0.0f);
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.data[i][j] = this->data[i][j] * val;
    
    return res;
}

fmath::mat4& fmath::mat4::operator*=(const mat4& m) {
    *this = *this * m;
    return *this;
}

fmath::vec3 fmath::operator*(const fmath::mat4& m, const fmath::vec3& vec) {
    fmath::vec3 res;
    res._x = m.data[0][0] * vec._x + m.data[1][0] * vec._y + m.data[2][0] * vec._z + m.data[3][0];
    res._y = m.data[0][1] * vec._x + m.data[1][1] * vec._y + m.data[2][1] * vec._z + m.data[3][1];
    res._z = m.data[0][2] * vec._x + m.data[1][2] * vec._y + m.data[2][2] * vec._z + m.data[3][2];
    
    return res;
}

fmath::mat4 fmath::operator*(float val, const fmath::mat4& m) {
    fmath::mat4 res(0.0f);
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.data[i][j] = m.data[i][j] * val;
    
    return res;
}

float& fmath::mat4::operator()(int i, int j) {
    return data[j][i];
}

bool fmath::operator==(const fmath::mat4& a, const fmath::mat4& b) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (a.data[i][j] == b.data[i][j]) continue;
            else return false;
        }
    return true;
}

std::ostream& fmath::operator<<(std::ostream& os, const fmath::mat4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << m.data[j][i] << " ";
            if (j == 3) os << "\n";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, fmath::mat4& m) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            is >> m(i, j);
    return is;
}