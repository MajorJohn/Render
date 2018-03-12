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

//rand a point inside a sphere (r = 1)
inline vec3 random_in_unit_sphere()
{
    vec3 p;

    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (dot(p,p) >= 1.0);

    return p;
}

//rand a point inside a disc (r = 1)
inline vec3 random_in_unit_disc()
{
    vec3 p;

    do {
        p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1,1,0);
    } while (dot(p,p) >= 1.0);

    return p;
}

//return a v reflect by normal n (both need to be unit vec)
inline vec3 reflect (const vec3 & v, const vec3 & n) 
{
    return v - 2*dot(v,n)*n;
}

//normalize the vector. If it is with any space greater than 1, turn its to 1
inline void normalizeColor(color & c_)
{
    if(c_.x() > 1) c_[color::R] = 1;
    if(c_.y() > 1) c_[color::G] = 1;
    if(c_.z() > 1) c_[color::B] = 1;
}

//distance between two points
inline float distance(point3 p1_, point3 p2_)
{
    float a, b, c;

    a = p1_.x() - p2_.x();
    b = p1_.y() - p2_.y();
    c = p1_.z() - p2_.z();

    return sqrt(a*a + b*b + c*c);
}

inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv = unit_vector(v);
    float dt = dot(uv,n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);

    if (discriminant > 0)
    {
        refracted = ni_over_nt*(v - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else
        return false;
}

//==============================[ vec3.inl ]==============================//
