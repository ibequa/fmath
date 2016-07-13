//
//  mat4.hpp
//  Flexo
//
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef mat4_hpp
#define mat4_hpp

#include <iosfwd>

#include "vec3.hpp"

namespace fmath {
    
    /** \class 4x4 matrix implementation. Internally matrix is laid-out in a column-major order.
     *
     * You're allowed to access matrix data only via operator().
     */
    class mat4 {
    private:
        void swap(float*, float*);
        float data[4][4];
        
    public:
        /** \brief Constructs an identity matrix
         */
        mat4();
        
        /** \brief Constructs a matrix consisting of value's
         */
        mat4(float value);
        
        /** \brief Matrix is column-major laid out in an 1-d array
         * \return column-major array representation of the matrix
         */
        const float* rawData() const;
        
        mat4 transposed() const;
        mat4 inversed() const;
        
        /** \brief Replaces the current matrix with the identity matrix
         */
        void loadIdentity();
        
        friend mat4 operator+(const mat4&, const mat4&);
        friend mat4 operator*(const mat4&, const mat4&);
        friend vec3 operator*(const mat4&, const vec3&);
        mat4& operator*=(const mat4&);
        mat4 operator*(float) const;
        friend mat4 operator*(float, const mat4&);
        friend bool operator==(const mat4&, const mat4&);
        float& operator()(int i, int j);
        
        friend std::ostream& operator<<(std::ostream&, const mat4&);
        friend std::istream& operator>>(std::istream&, mat4&);
    };
}

#endif /* mat4_hpp */