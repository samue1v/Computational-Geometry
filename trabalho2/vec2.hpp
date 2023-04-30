#ifndef VEC2_H
#define VEC2_H
#include <iostream>
#include <cmath>



class Vec2{
    private:
        double e[3];
    public:
        Vec2() : e{0,0}{}
        Vec2(double x, double y) : e{x,y}{}
        ~Vec2() = default;
        Vec2& operator =(const Vec2 & v){
            e[0] = v[0];
            e[1] = v[1];
            return *this;
        }

        double x()const {return e[0];}
        double y()const {return e[1];}
        Vec2 operator -() const{
            return Vec2(-e[0],-e[1]);
        }
        double operator [](int i) const {return e[i];}
        double& operator [](int i) {return e[i];}

        Vec2 & operator +=(const Vec2 & v){
            e[0] += v[0];
            e[1] += v[1];
            return *this;
        }
        Vec2 & operator -=(const Vec2 & v){
            e[0] -= v[0];
            e[1] -= v[1];
            return *this;
        }

        Vec2 & operator *=(const double d){
            e[0] *= d;
            e[1] *= d;
            return *this;
        }

        Vec2 & operator /=(const double d){
            e[0] *= 1.0f/d;
            e[1] *= 1.0f/d;
            return *this;
        }

        

        double len() const{ return sqrt(e[0]*e[0] + e[1]*e[1]);}


};

inline std::ostream& operator<<(std::ostream &out, const Vec2 &v) {
    return out << v[0] << ' ' << v[1]  << std::endl;
}

inline Vec2 operator+(const Vec2 & v0,const Vec2 & v1){
    return Vec2(v0[0]+v1[0], v0[1]+v1[1]);
} 

inline Vec2 operator-(const Vec2 & v0,const Vec2 & v1){
    return Vec2(v0[0]-v1[0], v0[1]-v1[1]);
} 

inline Vec2 operator*(const Vec2 & v0,const Vec2 & v1){
    return Vec2(v0[0]*v1[0], v0[1]*v1[1]);
} 

inline Vec2 operator*(const Vec2 & v, double t){
    return Vec2(v[0]*t,v[1]*t);
}

inline Vec2 operator*(double t, const Vec2 & v){
    return Vec2(v[0]*t,v[1]*t);
}

inline Vec2 operator/(const Vec2 & v, double t){
    return Vec2(v[0]/t,v[1]/t);
}

inline double dot(const Vec2 &v0, const Vec2 &v1) {
    return v0[0] * v1[0]
         + v0[1] * v1[1];
}

inline double cross(const Vec2 &v0, const Vec2 &v1) {
    return v0[0] * v1[1] - v0[1]*v1[0];
}

inline Vec2 unit(const Vec2& v) {
    return v / v.len();
}

inline Vec2 normalize(const Vec2& v) {
  double bigger = -INFINITY;
  if (v.x() > bigger) {
    bigger = v.x();
  }
  if (v.y() > bigger) {
    bigger = v.y();
  }

  return Vec2(v.x() / bigger, v.y() / bigger) ;
}

using Point2 = Vec2;
using RGBcolor = Vec2;

#endif
