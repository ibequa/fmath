//
//  vec3.hpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <iosfwd>

namespace fmath {
    
    /** \class Vector3 implementation.
     * Multiplication and division are calculated component-wise.  
     */
    struct vec3 {
        vec3();
        explicit vec3(float);
        explicit vec3(float, float, float);
        
        float _x, _y, _z;
        float magnitude() const;
        void normalize();
        vec3 normalized() const;
        
        static float dot(const vec3&, const vec3&);
        static vec3 cross(const vec3&, const vec3&);
        
        vec3 operator-() const;
        vec3 operator+(const vec3&) const;
        vec3& operator+=(const vec3&);
        vec3 operator-(const vec3&) const;
        vec3 operator*(const vec3&) const;
        vec3 operator/(const vec3&) const;
        vec3 operator*(float) const;
        vec3& operator/=(const vec3&);
        vec3& operator*=(const vec3&);
        friend vec3 operator*(float, const vec3&);
        friend vec3 operator/(float, const vec3&);
        bool operator==(const vec3&) const;
        bool operator!=(const vec3&) const;
        
        friend std::ostream& operator<<(std::ostream&, const vec3&);
        friend std::istream& operator>>(std::istream&, vec3&);
        
        inline static vec3 up() { return vec3(0.0f, 1.0f, 0.0f); }
        inline static vec3 forward() { return vec3(0.0f, 0.0f, 1.0f); }
        inline static vec3 right() { return vec3(1.0f, 0.0f, 0.0f); }
        inline static vec3 zero() { return vec3(0.0f, 0.0f, 0.0f); }
        inline static vec3 one() { return vec3(1.0f, 1.0f, 1.0f); }
    };
}

#endif /* vec3_hpp */
