#include "vec3.h"

//
//=== Member function implementation.
//
inline void vec3::make_unit_vector( void )
{
    /**
     * +---> unit vector.
     * |
     *
     * ^     1
     * v = _____ * v
     *     ||v||
     *
     * ||v|| = sqrt( v dot v )
     *
     *      1
     * k =_____
     *    ||v||
     */
    
    value_type length = this->length();

    if(this->e[X] != 0)
        this->e[X] = e[X]/length;

    if(this->e[Y] != 0)
        this->e[Y] = e[Y]/length;

    if(this->e[Z] != 0)
        this->e[Z] = e[Z]/length;
}

//
//=== Non-member function implementation: operator overloading.
//

inline std::istream& operator>>( std::istream& is, vec3 & v )
{
    is >> v.e[vec3::field_t::X]
       >> v.e[vec3::field_t::Y]
       >> v.e[vec3::field_t::Z];
    return is;
}

inline std::ostream& operator<<( std::ostream& os, const vec3 & v )
{
    os << "{ "
       << v.e[vec3::field_t::X]
       << " "
       << v.e[vec3::field_t::Y]
       << " "
       << v.e[vec3::field_t::Z]
       << " }";

    return os;
}

inline vec3 operator+( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.e[vec3::X] + v2.e[vec3::X],
                 v1.e[vec3::Y] + v2.e[vec3::Y],
                 v1.e[vec3::Z] + v2.e[vec3::Z] );
}

inline vec3 operator-( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.e[vec3::X] - v2.e[vec3::X],
                 v1.e[vec3::Y] - v2.e[vec3::Y],
                 v1.e[vec3::Z] - v2.e[vec3::Z] );
}

inline vec3 operator*( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.e[vec3::X] * v2.e[vec3::X],
                 v1.e[vec3::Y] * v2.e[vec3::Y],
                 v1.e[vec3::Z] * v2.e[vec3::Z] );
}

inline vec3 operator/( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.e[vec3::X] / v2.e[vec3::X],
                 v1.e[vec3::Y] / v2.e[vec3::Y],
                 v1.e[vec3::Z] / v2.e[vec3::Z] );
}



// Uso: V * 4
inline vec3 operator*( const vec3 & v, vec3::value_type t )
{
    return vec3( v.e[vec3::X] * t,
                 v.e[vec3::Y] * t,
                 v.e[vec3::Z] * t );
}

// Uso: 4 * V
inline vec3 operator*( vec3::value_type t, const vec3 & v )
{
    return vec3( v.e[vec3::X] * t,
                 v.e[vec3::Y] * t,
                 v.e[vec3::Z] * t );
}

inline vec3 operator/( const vec3 & v, vec3::value_type t )
{
    return vec3( v.e[vec3::X] / t,
                 v.e[vec3::Y] / t,
                 v.e[vec3::Z] / t );
}

inline vec3::value_type dot( const vec3 & v1, const vec3 & v2 )
{
    return  v1.e[vec3::X] * v2.e[vec3::X] +
            v1.e[vec3::Y] * v2.e[vec3::Y] +
            v1.e[vec3::Z] * v2.e[vec3::Z] ;
}

inline vec3 cross( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.e[vec3::Y] * v2.e[vec3::Z] - v1.e[vec3::Z] * v2.e[vec3::Y],
                 v1.e[vec3::Z] * v2.e[vec3::X] - v1.e[vec3::X] * v2.e[vec3::Z],
                 v1.e[vec3::X] * v2.e[vec3::Y] - v1.e[vec3::Y] * v2.e[vec3::X] );
}

inline vec3& vec3::operator+=( const vec3 & v )
{
    e[X] += v.e[X];
    e[Y] += v.e[Y];
    e[Z] += v.e[Z];

    return *this;
}

inline vec3& vec3::operator-=( const vec3 & v )
{
    e[X] -= v.e[X];
    e[Y] -= v.e[Y];
    e[Z] -= v.e[Z];

    return *this;
}

inline vec3& vec3::operator*=( const vec3 & v )
{
    e[X] *= v.e[X];
    e[Y] *= v.e[Y];
    e[Z] *= v.e[Z];

    return *this;
}

// Uso: A /= B;
inline vec3& vec3::operator/=( const vec3 & v )
{
    e[X] /= v.e[X];
    e[Y] /= v.e[Y];
    e[Z] /= v.e[Z];

    return *this;
}

// Uso: A *= 3;
inline vec3& vec3::operator*=( const value_type t )
{
    e[X] = e[X]*t;
    e[Y] = e[Y]*t;
    e[Z] = e[Z]*t;

    return *this;
}

// Uso: A /= 3;
inline vec3& vec3::operator/=( const value_type t )
{
    e[X] = e[X]/t;
    e[Y] = e[Y]/t;
    e[Z] = e[Z]/t;

    return *this;
}

// Uso: vec3 A = unit_vector( B );
inline vec3 unit_vector( const vec3 & v )
{
    return v/v.length();
}

//==============================[ vec3.inl ]==============================//
