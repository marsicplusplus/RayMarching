#ifndef __VEC_HPP__
#define __VEC_HPP__

#include <cmath>
#include <iostream>

class Vec3{
	public:
		float x, y, z;

	public:
		Vec3(float a, float b, float c) : x{a}, y{b}, z{c} {};
		Vec3(float a) : x{a}, y{a}, z{a} {};
		Vec3() : x{0.0f}, y{0.0f}, z{0.0f} {};
		Vec3 operator +(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z+v.z); }
		Vec3 operator -(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
		Vec3 operator -() const { return Vec3(-x, -y, -z); }
		Vec3 operator *(const float t) const { return Vec3(x*t, y*t, z*t); }
		Vec3 operator *(const Vec3 &v)const { return Vec3(x*v.x, y*v.y, z*v.z); }
		float dot(const Vec3 &v) const { return x * v.x + y * v.y + z * v.z; }
		Vec3& operator /= (const float t) { x/=t; y/=t; z/=t; return *this; }
		Vec3& operator *= (const float t) { x*=t; y*=t; z*=t; return *this; }
		Vec3 cross(const Vec3 &v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); } 
		float norm() const { return x*x + y*y + z*z;}
		float length() const { return sqrt(norm()); }

		const float& operator[](u_int8_t i) const { return(&x)[i]; }
		float& operator[](u_int8_t i) { return(&x)[i]; }
		Vec3& normalize(){
			float n = norm();
			if(n > 0) {
				float factor = 1 / sqrt(n);
				x*=factor, y*=factor, z*=factor;
			}
			return *this;
		}

		friend Vec3 operator * (const float r, const Vec3 &v) { return Vec3(v.x * r, v.y * r, v.z * r); }
		friend Vec3 operator / (const float r, const Vec3 &v) { return Vec3(v.x / r, v.y / r, v.z / r); }

		friend std::ostream& operator << (std::ostream &s, const Vec3 &v){ return s<<'[' << v.x << ' ' << v.y << ' ' << v.z << ']'; }

		friend Vec3 vabs(const Vec3 &v){
			return Vec3(fabs(v.x), fabs(v.y), fabs(v.z));
		}

		friend Vec3 vmod(const Vec3 &v, const Vec3 &u) {
			return Vec3(
					v.x - u.x * floor(v.x / u.x),
					v.y - u.y * floor(v.y / u.y),
					v.z - u.z * floor(v.z / u.z));
		}

		friend Vec3 vmax(const Vec3 &v, const Vec3 &u) {
			return Vec3(fmax(v.x, u.x), fmax(v.y, u.y), fmax(v.z, u.z));
		}
};

#endif
