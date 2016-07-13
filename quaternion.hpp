//
//  quaternion.hpp
//  Flexo
//
//  Created by Ilya on 10/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef quaternion_hpp
#define quaternion_hpp

#include <iosfwd>

#include "vec3.hpp"

namespace fmath {
    struct quaternion {
        static const float DEG2RAD;
        
        float _w, _x, _y, _z;
        
        quaternion();
        explicit quaternion(float x, float y, float z, float w);
        quaternion(float scalar, const vec3& vec);
        quaternion(const vec3& vec);
        
        quaternion inverse() const;
        inline quaternion conjugate() const { return quaternion(-_x, -_y, -_z, _w); }
        void normalize();
        quaternion normalized() const;
        float magnitude() const;
        
        /** \brief Calculates the quaternion from Euler angles
         */
        static quaternion fromEuler(const vec3& euler);
        
        /** \brief Calculates the Hamilton product
         */
        friend quaternion operator*(const quaternion&, const quaternion&);
        quaternion& operator*=(const quaternion&);
        quaternion operator+(const quaternion&) const;
        quaternion operator-() const;
        
        friend std::ostream& operator<<(std::ostream& os, const quaternion&);
        friend std::istream& operator>>(std::istream& os, quaternion&);
    };
}

#endif /* quaternion_hpp */