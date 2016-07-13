//
//  fmath.hpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef fmath_hpp
#define fmath_hpp

#include "vec3.hpp"
#include "quaternion.hpp"
#include "mat4.hpp"

namespace fmath {
    
    /** \brief Constructs orthogonal projection matrix
     * \return 4x4 orthogonal projecton matrix
     */
    mat4 ortho(float l, float r, float b, float t, float n, float f);
    
    /** Constructs perspective projection matrix
     * \return 4x4 perspective projection matrix
     */
    mat4 frustum(float l, float r, float b, float t, float n, float f);
    
    /** Constructs symmetrical perspective projection. Base case of frustum().
     * \return 4x4 symmetrical perspective projection matrix
     */
    mat4 perspective(float fovy, float aspect, float n, float f);
    
    /** \brief Constructs look-at matrix
     * Creates a 4x4 matrix representing a transformation
     *         to a right-handed coordinate system with dir as Z axis, cross(up, position - dir)
     *         as X axis and cross(dir, Xaxis) as Y axis
     * \return 4x4 view space matrix
     * \param position world space position
     * \param dir world space direction
     * \param up world space up direction
     */
    mat4 lookAt(const vec3& position, const vec3& dir, const vec3& up);
    
    /** \brief Multiples target with 4x4 translation matrix
     * \param vec translation vector
     * \param target mat4, will be multipled with the translation matrix
     * \return Product of target and the translation matrix
     */
    mat4 translate(const mat4& target, const vec3& vec);
    
    /** \brief Multiples target with 4x4 scale matrix
     * \param vec scale vector
     * \param target mat4, will be multipled with the scale matrix
     * \return Product of target and the scale matrix
     */
    mat4 scale(const mat4& target, const vec3& vec);
    
    /** \brief Converts quaternion to 4x4 rotation matrix
     * \param q quaternion to be converted
     * \return 4x4 rotation matrix
     */
    mat4 quaternionToMatrix(const quaternion& _q);

    /** \brief Linearly interpolates between x0 and x1 based on t
     */
    float lerp(float x0, float x1, float t);
}

#endif /* fmath_hpp */