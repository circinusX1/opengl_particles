
#ifndef _VERTEX_H
#define _VERTEX_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>


//macros utils
#define EPSILON					0.0009765625F

#define INFINIT					999999999.0
#define PI						3.141592f                // PI in radians
#define HLFPI                   (3.141592f/2.0f)
#define ONEDG                   0.01745329f                // one degree
#define G2R(a)					(a*0.01745f)               // degree to radians
#define R2G(a)					(a*57.2957f)               //radians to degrees
#define SWITCHI(_x,_y)			((_x)^=(_y)^=(_x)^=(_y))                        // swithes 2 integers
#define ROLLG(a)				{if(a<0) a=360; else if (a > 360) a = 0;}       // roll's the angle
#define ROLLR(a)				{if(a<0) a=(PI*2.0f); else if (a > (PI*2.0f)) a = 0.00;}
#define ROLL180(a)				{if(a<-180.00) a=180.00; else if (a > 180.00) a = -180.00;}
#define BLOCKRANGE(a)			if(a < - HLFPI-EPSILON) a =- (HLFPI-EPSILON); else if (a > HLFPI-EPSILON) a = HLFPI-EPSILON;  // blocks the range of angle to straight up/down
#define CLAMPVAL(_v_,m_,M_)     {if(_v_< m_) _v_= m_; else if (_v_> M_)  _v_=M_;}
#define ROLLPI(a)				{if(a < -(PI) ) a = (PI); else if (a > (PI)) a = -(PI);}
#define ROLL2PI(a)				{if(a < 0) a = (PI*2.0f); else if (a > (PI*2.0f)) a = 0;}
#define RRND()		            ((float)rand()*(1.0f /(float)RAND_MAX))  // Floating point random number generator ( 0 -> 1)
#define SGN(a)                  ((a)<0?-1:((a)?1:0))


template <class T>T tmin(T a, T b)  {return a < b ? a : b;}
template <class T>T tmax(T a, T b)  {return a >= b ? a : b;}


#define FRAND(low,high) (float)(rand() % ((high - low) + 1) + low)




inline bool IsPowOf2(int value){ // if error here you did not define one of _CFG_**** (see top)
    return (value&(value-1))==0;
}
inline int ToPow2(int value, int sv=0x1){
    while(value>>=1){
        sv<<=1;
    }
    return sv;
}

inline float Tanr(float gr){
    return tanf(gr);
}

inline float Sinr(float gr){
    return sinf(gr);
}

inline float Cosr(float gr){
    return cosf(gr);
}

inline float Sina(float gr){
    ROLLG(gr); return Sinr(gr);
}

inline float Cosa(float gr){
    ROLLG(gr); return Cosr(gr);
}

inline long R2I (float f){
#ifdef WINDOWS
    static int i;
    ASM_ fld dword ptr [esp+4]
        ASM_ fistp i
        ASM_ mov eax, i
        ASM_ ret
#else
        return (long)f;
#endif //
}
inline int Randval(int iMin, int iMax)
{
    return((rand() % (abs(iMax-iMin)+1))+iMin);
}

inline float  Randval(float fMin, float fMax)
{
    if (fMin == fMax) return(fMin);
    float fRandom = (float)rand() / (float)RAND_MAX;
    return((fRandom * (float)fabs(fMax-fMin))+fMin);
}

inline float Rabs (float f){
    int i = *(int*) &f;
    i &= 0x7FFFFFFF;
    return *(float*)&i;
}

inline float Frand(){

    static unsigned int x = /* QfRandomInt() */ 1234567;
    static unsigned int jflone = 0x40000000;
    static unsigned int jflmask = 0x007fffff;

    x = x * 1664525 + 1013904223;
    unsigned int t = jflone | (jflmask & x);
    return (*(float*)&t) - 3.0f;
}

inline bool  IsZero(float a , float b=EPSILON){
    if(a==0)return true;
    return ( a > -b && a < b );
}

inline float Asinr (float val) {
    if ( -1.0 < val ) {
        if ( val < 1.0 ) {
            return float (asin(val));
        } else {
            return -PI/2.0f;
        }
    } else {
        return PI/2.0f;
    }
}

inline float ATanr (float val) {
    return float(atan(val));
}

//---------------------------------------------------------------------------------------
struct V3I{int x,y,z;};
typedef  float    AV3[4];
class  V3
{
public:
    float x, y, z;
    V3():x(0.0),y(0.0),z(0.0) {};
    V3(float inX, float inY, float inZ): x(inX), y(inY), z(inZ) {}
    V3(const V3 &v): x(v.x), y(v.y), z(v.z) {}
    V3(const float f): x(f), y(f), z(f) {}
    V3(const float *f): x(*f), y(*(f+1)), z(*(f+2)) {}
    void RawPaste(float* pr){*pr =x;	*(pr+1) = y;*(pr+2) = z;}
    void RawCopy(float* pr){	x = *pr;y = *(pr+1);z = *(pr+2);}
    operator float*(){return &x;}
    operator const float*()const{return &x;}
    inline  V3& operator+=(const V3 &v){x += v.x; y += v.y; z += v.z;	return *this;}
    inline  V3& operator+=(const float r){	x += r; y += r; z += r;	return *this;}
    inline  V3& operator-=(const V3 &v){x -= v.x ;y -= v.y; z -= v.z;return *this;}
    inline  V3& operator=(const V3 &v){x = v.x ;y = v.y; z = v.z;return *this;}
    //inline  V3& operator=(const float* pf){x=(*pf); y=(*(pf+1)); z=(*(pf+2)); return *this;}
    inline  void negate(){x=-x;y=-y;z=-z;};
    inline  V3& operator*=(float f) {x *= f;y *= f;z *= f;	return *this;}
    inline  V3& operator/=(float f) {x /= f;y /= f;z /= f;	return *this;}
    inline  V3& operator/=(int f) {x /= (float)f;y /= (float)f;z /= (float)f;return *this;}
    inline  V3& operator*=(const V3& v){	x *= v.x;y *= v.y;z *= v.z;return *this;}
    float getmin()const{return tmin((tmin(x,y)),z);}
    float getmax()const{return tmax((tmax(x,y)),z);}
    inline void reset(){	memset(this,0,sizeof(*this));}
    inline void domin(V3& v){	x = tmin(x, v.x);y = tmin(y, v.y);z = tmin(z, v.z);	}
    inline  void domax(V3& v){x = tmax(x, v.x);y = tmax(y, v.y);z = tmax(z, v.z);	}
    inline void addscaled(V3& v, float d){	x+=v.x*d;	y+=v.y*d;	z+=v.z*d;}
    friend inline  bool operator==(const V3 &a, const V3 &b) {return(IsZero(a.x-b.x) && IsZero(a.y-b.y) &&  IsZero(a.z-b.z));	}
    friend inline  bool operator!=(const V3 &a, const V3 &b) {return((a.x != b.x) || (a.y != b.y) || (a.z != b.z));}
    friend inline  V3 operator-(const V3 &a){	return V3(-a.x, -a.y, -a.z);}
    friend inline  V3 operator+(const V3& a, const V3& b) {V3 ret(a);ret += b;return ret;}
    friend inline  V3 operator-(const V3 &a, const V3 &b) {V3 ret(a); ret -= b; return ret;}
    friend inline  V3 operator*(const V3 &v, float f) {return V3(f * v.x, f * v.y, f * v.z);}
    friend inline  V3 operator*(float f, const V3 &v) {return V3(f * v.x, f * v.y, f * v.z);}
    friend inline  V3 operator/(const V3 &v, float f) {return V3(v.x / f, v.y / f, v.z / f);}
    friend inline  V3  operator/(const V3 &v, const V3 &f) {return V3(v.x / f.x, v.y / f.y, v.z / f.z);}
    friend inline  V3  operator*(const V3 &v, const V3 &f) {return V3(v.x * f.x, v.y * f.y, v.z * f.z);}
    friend inline  float vdist(const V3& p1,const  V3& p2){V3 tmp(p1);	tmp-=p2;return tmp.len();}
    friend inline  float vdist2(const V3& p1,const  V3& p2){V3 tmp(p1);	tmp-=p2;	return tmp.len2();}
    inline  float vdp(const V3& b){  return x*b.x + y*b.y + z*b.z; }
    inline  V3&  vcp(const V3 &b){setval(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);return *this;}
    inline  void setval(float xx, float yy, float zz) {x = xx; y = yy; z = zz;}
    inline  void setval(float xx[3]) {x = xx[0]; y = xx[1]; z = xx[2];}
    inline  void squeeze(float val)	{if (x > -val && x < val)x = 0.00;if (y > -val && y < val)y = 0.00;if (z > -val && z < val)	z = 0.00;}
    inline  void setval(float xx) {x = xx; y = xx; z = xx;	}
    inline  bool Valid(){	return fabs(x) != INFINIT;}
    inline  void setval(V3& v) {x = v.x; y = v.y; z = v.z;}

    inline float len() const {return(float) sqrt(x*x + y*y + z*z);	}
    inline float len2() const{return(x*x + y*y + z*z);}
    inline bool isnot1()const{return (x!=1 || y!=1 || z!=1);	}
    inline bool is0(float eps=EPSILON)	const{return Rabs(x) < eps && Rabs(y) < eps && Rabs(z) < eps;}
    bool isnot0()const{return Rabs(x)>EPSILON || Rabs(y)>EPSILON || Rabs(z)>EPSILON;}
    inline bool isortonormal()const{
        if (y > .999 || y< -.999) return 1;
        if (x > .999 || x< -.999) return 1;
        if (z > .999 || z< -.999) return 1;
        return 0;
    }
    float normalize(){
        float m = len();
        if (m > 0.0) m = 1.0 / m;
        else m = 0.0;x *= m;
        y *= m; z *= m;
        return m;
    }
    inline  V3 &norm(){	float m = len();
    if (m > 0.0) m = 1.0 / m;
    else m = 0.0;x *= m;
    y *= m; z *= m;
    return *this;
    }
    inline void cross(const V3 &v1,const V3 &v2) {
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
    }
    void SetLength(float l)
    {
        float len = sqrt(x*x + y*y + z*z);
        x *= l/len;
        y *= l/len;
        z *= l/len;
    }
};
//---------------------------------------------------------------------------------------
extern V3 VX;
extern V3 VZ;
extern V3 VY;
extern V3 V0;
extern V3 V1;


//---------------------------------------------------------------------------------------
inline   V3 Vcp(const V3 &a, const V3 &b){
    return V3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

//---------------------------------------------------------------------------------------
inline  V3 Getnormal(const V3& p0,const  V3& p1,const  V3& p2){
    V3 v = Vcp(p0-p1, p2-p1);
    v.norm();
    return v;
}

//------------------------------------------------------------------------------------
// Normalises the input vector and returns the vector normalised
inline  V3 Vnrm(const V3 &a)
{
    V3 ret(a.x,a.y,a.z);
    return ret.norm();
}

//---------------------------------------------------------------------------------------
inline  float Vdp(const V3 &a, const V3 &b)
{
    return (float)(a.x*b.x + a.y*b.y + a.z*b.z);
}

//---------------------------------------------------------------------------------------
inline  void Vswp(V3 &a, V3 &b)
{
    V3 tmp(a);    a = b;    b = tmp;
}

//---------------------------------------------------------------------------------------
typedef  unsigned char    ACLR[4];
class  CLR
{
public:
    unsigned char r,g,b,a;
    CLR():r(255),g(255),b(255),a(255){};
    CLR(unsigned char rgb):r(rgb),g(rgb),b(rgb),a(rgb){};
    CLR(ACLR rgb):r(rgb[0]),g(rgb[1]),b(rgb[2]),a(rgb[3]){};
    CLR(const CLR& rgb):r(rgb.r),g(rgb.g),b(rgb.b),a(rgb.a){}
    CLR(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa){r = rr;    g = gg;    b = bb;    a = aa;}
    CLR(unsigned char rr, unsigned char gg, unsigned char bb){	r = rr;    g = gg;    b = bb;    a = 255;}
    CLR (unsigned int dwclr){ a=255; r= (dwclr>>16)&0xff; g= (dwclr>>8)&0xff; b= (dwclr)&0xff;}
    operator unsigned int(){unsigned int drv; drv = (r<<24)|(g<<16)|b; return drv;}

};



//---------------------------------------------------------------------------------------
#define	PLANE_X						0
#define	PLANE_Y						1
#define	PLANE_Z						2
#define	PLANE_ANYX					3
#define	PLANE_ANYY					4
#define	PLANE_ANYZ					5
#define	PLANE_ANY					6

//---------------------------------------------------------------------------------------
typedef  float  APlane[4];
class Plane
{
public:
    Plane():_c(0.0),_t(PLANE_ANY){};

    ~Plane(){}
    inline float DistTo(const V3& pct)const{
        float r = (Vdp(pct, _n) - _c);
        return r;
    }
    inline float DistTo(float a, float b, float c)const{return (Vdp(V3(a,b,c), _n) - _c);	}
    inline void CalcNormal(const V3& p0, const  V3& p1, const  V3& p2){
        V3 vV1 = p0-p1;
        V3 vV2 = p0-p2;
        _n = Vcp(vV1, vV2);	_n.norm();
        _c = Vdp(p0,_n);
    }

    inline float FastDistTo(const V3& pct)const{
        switch (_t&0xF){
        case PLANE_X: if(_n.x<0) return -(pct.x - (-_c)); return (pct.x - _c);
        case PLANE_Y: if(_n.y<0) return -(pct.y - (-_c)); return (pct.y - _c);
        case PLANE_Z: if(_n.z<0) return -(pct.z - (-_c)); return (pct.z - _c);
        }
        return (Vdp(pct, _n) - _c);
    }
    void TypeIt(){
        _t = PLANE_ANY;
        if(IsZero(Rabs(_n.x)-1.0))		_t = PLANE_X;
        else if(IsZero(Rabs(_n.y)-1.0))	_t = PLANE_Y;
        else if(IsZero(Rabs(_n.z)-1.0))	_t = PLANE_Z;
    }
    inline bool RayIntersect( const V3& vpos, const V3& vdir, V3& ip)const{
        float dp = Vdp(_n, vdir);
        if(dp  >= 0.0)//away from plane
        {
            return false;
        }
        ip = vpos - ((vdir * DistTo(vpos)) / dp);
        return true;
    }


public:
    V3		_n;
    float	_c;
    unsigned short	_t;
    unsigned short	_u;

};



inline void	ReflectVector(V3& who, V3& normal, float attn, V3& newSpeed)
{
    newSpeed = 2.0f * (normal * Vdp(-who, normal)) +  who;
    newSpeed*=attn;
}


typedef  float  AM4[16]; //for opengl

class M4
{
public:
    float   _m[16];

public:
    M4()     {identity();};
    M4(V3 v) {translate(v);};
    M4(const V3 &axis,float angle)              {rotate(axis,angle);}
    inline  M4(const M4 &m) {
        _m[0] = m._m[0]; _m[4] = m._m[4]; _m[8] = m._m[8]; _m[12] = m._m[12];
        _m[1] = m._m[1]; _m[5] = m._m[5]; _m[9] = m._m[9]; _m[13] = m._m[13];
        _m[2] = m._m[2]; _m[6] = m._m[6]; _m[10] = m._m[10]; _m[14] = m._m[14];
        _m[3] = m._m[3]; _m[7] = m._m[7]; _m[11] = m._m[11]; _m[15] = m._m[15];
    }
    M4& operator=(const M4& m) {
        if(this != &m){
            _m[0] = m._m[0]; _m[4] = m._m[4]; _m[8] = m._m[8]; _m[12] = m._m[12];
            _m[1] = m._m[1]; _m[5] = m._m[5]; _m[9] = m._m[9]; _m[13] = m._m[13];
            _m[2] = m._m[2]; _m[6] = m._m[6]; _m[10] = m._m[10]; _m[14] = m._m[14];
            _m[3] = m._m[3]; _m[7] = m._m[7]; _m[11] = m._m[11]; _m[15] = m._m[15];
        }
        return *this;
    }
    operator float*() { return (float*)_m; }
    operator const float*() const { return (float*)_m; }
    M4 operator+(const M4 &m) const
    {
        M4 ret;
        ret[0] = _m[0] + m[0]; ret[4] = _m[4] + m[4]; ret[8] = _m[8] + m[8]; ret[12] = _m[12] + m[12];
        ret[1] = _m[1] + m[1]; ret[5] = _m[5] + m[5]; ret[9] = _m[9] + m[9]; ret[13] = _m[13] + m[13];
        ret[2] = _m[2] + m[2]; ret[6] = _m[6] + m[6]; ret[10] = _m[10] + m[10]; ret[14] = _m[14] + m[14];
        ret[3] = _m[3] + m[3]; ret[7] = _m[7] + m[7]; ret[11] = _m[11] + m[11]; ret[15] = _m[15] + m[15];
        return ret;
    }
    V3 operator*(const V3 &v) const {
        V3 ret;
        ret[0] = _m[0] * v.x + _m[4] * v.y + _m[8] * v.z + _m[12];
        ret[1] = _m[1] * v.x + _m[5] * v.y + _m[9] * v.z + _m[13];
        ret[2] = _m[2] * v.x + _m[6] * v.y + _m[10] * v.z + _m[14];
        return ret;
    }
    M4 operator*(float f) const {
        M4 ret;
        ret._m[0] = _m[0] * f; ret._m[4] = _m[4] * f; ret._m[8] = _m[8] * f; ret._m[12] = _m[12] * f;
        ret._m[1] = _m[1] * f; ret._m[5] = _m[5] * f; ret._m[9] = _m[9] * f; ret._m[13] = _m[13] * f;
        ret._m[2] = _m[2] * f; ret._m[6] = _m[6] * f; ret._m[10] = _m[10] * f; ret._m[14] = _m[14] * f;
        ret._m[3] = _m[3] * f; ret._m[7] = _m[7] * f; ret._m[11] = _m[11] * f; ret._m[15] = _m[15] * f;
        return ret;
    }
    M4 operator*(const M4 &m) const {
        M4 ret;
        ret._m[0] = _m[0] * m._m[0] + _m[4] * m._m[1] + _m[8] * m._m[2] + _m[12] * m._m[3];
        ret._m[1] = _m[1] * m._m[0] + _m[5] * m._m[1] + _m[9] * m._m[2] + _m[13] * m._m[3];
        ret._m[2] = _m[2] * m._m[0] + _m[6] * m._m[1] + _m[10] * m._m[2] + _m[14] * m._m[3];
        ret._m[3] = _m[3] * m._m[0] + _m[7] * m._m[1] + _m[11] * m._m[2] + _m[15] * m._m[3];
        ret._m[4] = _m[0] * m._m[4] + _m[4] * m._m[5] + _m[8] * m._m[6] + _m[12] * m._m[7];
        ret._m[5] = _m[1] * m._m[4] + _m[5] * m._m[5] + _m[9] * m._m[6] + _m[13] * m._m[7];
        ret._m[6] = _m[2] * m._m[4] + _m[6] * m._m[5] + _m[10] * m._m[6] + _m[14] * m._m[7];
        ret._m[7] = _m[3] * m._m[4] + _m[7] * m._m[5] + _m[11] * m._m[6] + _m[15] * m._m[7];
        ret._m[8] = _m[0] * m._m[8] + _m[4] * m._m[9] + _m[8] * m._m[10] + _m[12] * m._m[11];
        ret._m[9] = _m[1] * m._m[8] + _m[5] * m._m[9] + _m[9] * m._m[10] + _m[13] * m._m[11];
        ret._m[10] = _m[2] * m._m[8] + _m[6] * m._m[9] + _m[10] * m._m[10] + _m[14] * m._m[11];
        ret._m[11] = _m[3] * m._m[8] + _m[7] * m._m[9] + _m[11] * m._m[10] + _m[15] * m._m[11];
        ret._m[12] = _m[0] * m._m[12] + _m[4] * m._m[13] + _m[8] * m._m[14] + _m[12] * m._m[15];
        ret._m[13] = _m[1] * m._m[12] + _m[5] * m._m[13] + _m[9] * m._m[14] + _m[13] * m._m[15];
        ret._m[14] = _m[2] * m._m[12] + _m[6] * m._m[13] + _m[10] * m._m[14] + _m[14] * m._m[15];
        ret._m[15] = _m[3] * m._m[12] + _m[7] * m._m[13] + _m[11] * m._m[14] + _m[15] * m._m[15];
        return ret;
    }

    M4 &operator*=(float f)     { return *this = *this * f; }
    M4 &operator*=(const M4 &m) { return *this = *this * m; }
    M4 &operator+=(const M4 &m) { return *this = *this + m; }

    void orthonormalize() {
        V3 x(_m[0],_m[1],_m[2]);
        V3 y(_m[3],_m[4],_m[5]);
        V3 z;
        x.norm();
        z.cross(x,y);
        z.norm();
        y.cross(z,x);
        y.norm();
        _m[0] = x.x; _m[3] = y.x; _m[6] = z.x;
        _m[1] = x.y; _m[4] = y.y; _m[7] = z.y;
        _m[2] = x.z; _m[5] = y.z; _m[8] = z.z;
    }

    inline void v3transposeTransform(V3& i)
    {
        V3 r;
        i.x -= _m[12];
        i.y -= _m[13];
        i.z -= _m[14];

        r.x = i.x * _m[0] + i.y * _m[1] + i.z * _m[2] ;
        r.y = i.x * _m[4] + i.y * _m[5] + i.z * _m[6] ;
        r.z = i.x * _m[8] + i.y * _m[9] + i.z * _m[10] ;
        i=r;
    }

    inline void v3transform(V3& v)
    {
        v3translate(v);
        v3rotate(v);
        /*
        V3 r;
        r.x = v.x * _m[0] + v.y * _m[4] + v.z * _m[8]  + _m[12];
        r.y = v.x * _m[1] + v.y * _m[5] + v.z * _m[9]  + _m[13];
        r.z = v.x * _m[2] + v.y * _m[6] + v.z * _m[10] + _m[14];
        v=r;
        */
    }
    inline void v3rotate(V3& v)
    {
        V3 r;
        r.x = v.x * _m[0] + v.y * _m[4] + v.z * _m[8] ;
        r.y = v.x * _m[1] + v.y * _m[5] + v.z * _m[9] ;
        r.z = v.x * _m[2] + v.y * _m[6] + v.z * _m[10] ;
        v=r;
    }

    inline void v3translate(V3& ret)
    {
        ret.x = ret.x + _m[12];
        ret.y = ret.y + _m[13];
        ret.z = ret.z + _m[14];
    }

    inline void v3scale(V3& ret)
    {
        ret.x = ret.x * _m[0];
        ret.y = ret.y * _m[5];
        ret.z = ret.z * _m[10];
    }

    inline void identity() {
        _m[0] = 1.0; _m[4] = 0.0; _m[8] = 0.0; _m[12] = 0.0;
        _m[1] = 0.0; _m[5] = 1.0; _m[9] = 0.0; _m[13] = 0.0;
        _m[2] = 0.0; _m[6] = 0.0; _m[10] = 1.0; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }

    inline void transp(){
        M4 ret;
        ret._m[0] = _m[0]; ret._m[4] = _m[1]; ret._m[8] = _m[2]; ret._m[12] = _m[3];
        ret._m[1] = _m[4]; ret._m[5] = _m[5]; ret._m[9] = _m[6]; ret._m[13] = _m[7];
        ret._m[2] = _m[8]; ret._m[6] = _m[9]; ret._m[10] = _m[10]; ret._m[14] = _m[11];
        ret._m[3] = _m[12]; ret._m[7] = _m[13]; ret._m[11] = _m[14]; ret._m[15] = _m[15];
        *this = ret;
    }

    float det() const {
        float det;
        det = _m[0] * _m[5] * _m[10];
        det += _m[4] * _m[9] * _m[2];
        det += _m[8] * _m[1] * _m[6];
        det -= _m[8] * _m[5] * _m[2];
        det -= _m[4] * _m[1] * _m[10];
        det -= _m[0] * _m[9] * _m[6];
        return det;
    }
    M4 inverse() const {
        M4 ret;
        float idet = 1.0f / det();
        ret._m[0] =  (_m[5] * _m[10] - _m[9] * _m[6]) * idet;
        ret._m[1] = -(_m[1] * _m[10] - _m[9] * _m[2]) * idet;
        ret._m[2] =  (_m[1] * _m[6] - _m[5] * _m[2]) * idet;
        ret._m[3] = 0.0;
        ret._m[4] = -(_m[4] * _m[10] - _m[8] * _m[6]) * idet;
        ret._m[5] =  (_m[0] * _m[10] - _m[8] * _m[2]) * idet;
        ret._m[6] = -(_m[0] * _m[6] - _m[4] * _m[2]) * idet;
        ret._m[7] = 0.0;
        ret._m[8] =  (_m[4] * _m[9] - _m[8] * _m[5]) * idet;
        ret._m[9] = -(_m[0] * _m[9] - _m[8] * _m[1]) * idet;
        ret._m[10] =  (_m[0] * _m[5] - _m[4] * _m[1]) * idet;
        ret._m[11] = 0.0;
        ret._m[12] = -(_m[12] * ret._m[0] + _m[13] * ret._m[4] + _m[14] * ret._m[8]);
        ret._m[13] = -(_m[12] * ret._m[1] + _m[13] * ret._m[5] + _m[14] * ret._m[9]);
        ret._m[14] = -(_m[12] * ret._m[2] + _m[13] * ret._m[6] + _m[14] * ret._m[10]);
        ret._m[15] = 1.0;
        return ret;
    }

    void rotate(const V3 &axis, float angle) {
        float rad = G2R(angle);
        float c = Cosr(rad);
        float s = Sinr(rad);
        V3 v = axis;
        v.norm();
        float xx = v.x * v.x;
        float yy = v.y * v.y;
        float zz = v.z * v.z;
        float xy = v.x * v.y;
        float yz = v.y * v.z;
        float zx = v.z * v.x;
        float xs = v.x * s;
        float ys = v.y * s;
        float zs = v.z * s;
        _m[0] = (1.0f - c) * xx + c; _m[4] = (1.0f - c) * xy - zs; _m[8] = (1.0f - c) * zx + ys; _m[12] = 0.0;
        _m[1] = (1.0f - c) * xy + zs; _m[5] = (1.0f - c) * yy + c; _m[9] = (1.0f - c) * yz - xs; _m[13] = 0.0;
        _m[2] = (1.0f - c) * zx - ys; _m[6] = (1.0f - c) * yz + xs; _m[10] = (1.0f - c) * zz + c; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void rotatex(float angle) {
        float rad = G2R(angle);
        float c = Cosr(rad);
        float s = Sinr(rad);
        _m[0] = 1.0; _m[4] = 0.0; _m[8] = 0.0; _m[12] = 0.0;
        _m[1] = 0.0; _m[5] = c; _m[9] = -s; _m[13] = 0.0;
        _m[2] = 0.0; _m[6] = s; _m[10] = c; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void rotatey(float angle) {
        float rad = G2R(angle);
        float c = Cosr(rad);
        float s = Sinr(rad);
        _m[0] = c; _m[4] = 0.0; _m[8] = s; _m[12] = 0.0;
        _m[1] = 0.0; _m[5] = 1.0; _m[9] = 0.0; _m[13] = 0.0;
        _m[2] = -s; _m[6] = 0.0; _m[10] = c; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void rotatez(float angle) {
        float rad = G2R(angle);
        float c = Cosr(rad);
        float s = Sinr(rad);
        _m[0] = c; _m[4] = -s; _m[8] = 0.0; _m[12] = 0.0;
        _m[1] = s; _m[5] = c; _m[9] = 0.0; _m[13] = 0.0;
        _m[2] = 0.0; _m[6] = 0.0; _m[10] = 1.0; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void scale(const V3 &v) {
        _m[0] = v.x; _m[4] = 0.0; _m[8] = 0.0; _m[12] = 0.0;
        _m[1] = 0.0; _m[5] = v.y; _m[9] = 0.0; _m[13] = 0.0;
        _m[2] = 0.0; _m[6] = 0.0; _m[10] = v.z; _m[14] = 0.0;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void translate(const V3 &v) {
        _m[0] = 1.0; _m[4] = 0.0; _m[8] = 0.0; _m[12] = v.x;
        _m[1] = 0.0; _m[5] = 1.0; _m[9] = 0.0; _m[13] = v.y;
        _m[2] = 0.0; _m[6] = 0.0; _m[10] = 1.0; _m[14] = v.z;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }
    void reflect(const V3 &norm, float c) {
        float x = norm.x;
        float y = norm.y;
        float z = norm.z;
        float x2 = x * 2.0f;
        float y2 = y * 2.0f;
        float z2 = z * 2.0f;
        _m[0] = 1.0f - x * x2; _m[4] = -y * x2; _m[8] = -z * x2; _m[12] = -c * x2;
        _m[1] = -x * y2; _m[5] = 1.0f - y * y2; _m[9] = -z * y2; _m[13] = -c * y2;
        _m[2] = -x * z2; _m[6] = -y * z2; _m[10] = 1.0f - z * z2; _m[14] = -c * z2;
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = 0.0; _m[15] = 1.0;
    }

    void perspective(float fov,float aspect,float znear,float zfar) {
        float y = tan(fov * PI / 360.0f);
        float x = y * aspect;
        _m[0] = 1.0f / x; _m[4] = 0.0; _m[8] = 0.0; _m[12] = 0.0;
        _m[1] = 0.0; _m[5] = 1.0f / y; _m[9] = 0.0; _m[13] = 0.0;
        _m[2] = 0.0; _m[6] = 0.0; _m[10] = -(zfar + znear) / (zfar - znear); _m[14] = -(2.0f * zfar * znear) / (zfar - znear);
        _m[3] = 0.0; _m[7] = 0.0; _m[11] = -1.0; _m[15] = 0.0;
    }
    void look_to(const V3 &eye,const V3 &at,const V3 &up) {
        V3 x,y,z;
        M4 m0,m1;
        z = eye - at;
        z.norm();
        x.cross(up,z);
        x.norm();
        y.cross(z,x);
        y.norm();
        m0._m[0] = x.x; m0._m[4] = x.y; m0._m[8] = x.z; m0._m[12] = 0.0;
        m0._m[1] = y.x; m0._m[5] = y.y; m0._m[9] = y.z; m0._m[13] = 0.0;
        m0._m[2] = z.x; m0._m[6] = z.y; m0._m[10] = z.z; m0._m[14] = 0.0;
        m0._m[3] = 0.0; m0._m[7] = 0.0; m0._m[11] = 0.0; m0._m[15] = 1.0;
        m1.translate(-eye);
        *this = m0 * m1;
    }
    M4 rotation() const {
        M4 ret;
        ret[0] = _m[0]; ret[4] = _m[4]; ret[8] = _m[8]; ret[12] = 0;
        ret[1] = _m[1]; ret[5] = _m[5]; ret[9] = _m[9]; ret[13] = 0;
        ret[2] = _m[2]; ret[6] = _m[6]; ret[10] = _m[10]; ret[14] = 0;
        ret[3] = 0; ret[7] = 0; ret[11] = 0; ret[15] = 1;
        return ret;
    }
    M4 transpose() const {
        M4 ret;
        ret[0] = _m[0]; ret[4] = _m[1]; ret[8] = _m[2]; ret[12] = _m[3];
        ret[1] = _m[4]; ret[5] = _m[5]; ret[9] = _m[6]; ret[13] = _m[7];
        ret[2] = _m[8]; ret[6] = _m[9]; ret[10] = _m[10]; ret[14] = _m[11];
        ret[3] = _m[12]; ret[7] = _m[13]; ret[11] = _m[14]; ret[15] = _m[15];
        return ret;
    }
    M4 transpose_rotation() const {
        M4 ret;
        ret[0] = _m[0]; ret[4] = _m[1]; ret[8] = _m[2]; ret[12] = _m[12];
        ret[1] = _m[4]; ret[5] = _m[5]; ret[9] = _m[6]; ret[13] = _m[13];
        ret[2] = _m[8]; ret[6] = _m[9]; ret[10] = _m[10]; ret[14] = _m[14];
        ret[3] = _m[3]; ret[7] = _m[7]; ret[14] = _m[14]; ret[15] = _m[15];
        return ret;
    }

    void rotateradians(float dAngleX, float dAngleY, float dAngleZ)
    {
	    float cr = cos( dAngleX );
	    float sr = sin( dAngleX );
	    float cp = cos( dAngleY );
	    float sp = sin( dAngleY );
	    float cy = cos( dAngleZ );
	    float sy = sin( dAngleZ );

	    _m[0] = ( float )( cp*cy );
	    _m[1] = ( float )( cp*sy );
	    _m[2] = ( float )( -sp );

	    float srsp = sr*sp;
	    float crsp = cr*sp;

	    _m[4] = ( float )( srsp*cy-cr*sy );
	    _m[5] = ( float )( srsp*sy+cr*cy );
	    _m[6] = ( float )( sr*cp );

	    _m[8] = ( float )( crsp*cy+sr*sy );
	    _m[9] = ( float )( crsp*sy-sr*cy );
	    _m[10] = ( float )( cr*cp );

    }

    void multiply (M4 *matrix)
    {
	    float newMatrix[16];
	    const float *m1 = _m, *m2 = matrix->_m;

	    newMatrix[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2];
	    newMatrix[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2];
	    newMatrix[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2];
	    newMatrix[3] = 0;

	    newMatrix[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6];
	    newMatrix[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6];
	    newMatrix[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6];
	    newMatrix[7] = 0;

	    newMatrix[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10];
	    newMatrix[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10];
	    newMatrix[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10];
	    newMatrix[11] = 0;

	    newMatrix[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12];
	    newMatrix[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13];
	    newMatrix[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14];
	    newMatrix[15] = 1;

	    for (int i=0; i<16; i++)
		    this->_m[i] = newMatrix[i];
    }
	void  inversetranslatevect(V3& vct)
	{
		vct.x = vct.x-_m[12];
		vct.y = vct.y-_m[13];
		vct.z = vct.z-_m[14];
	}

	void inverserotatevect(V3&  vct)
	{
		V3 vec(vct.x*_m[0]+vct.y*_m[1]+vct.z*_m[2],
		       vct.x*_m[4]+vct.y*_m[5]+vct.z*_m[6],
		       vct.x*_m[8]+vct.y*_m[9]+vct.z*_m[10]);

		vct = vec;
	}

};

//---------------------------------------------------------------------------------------
inline  M4 MTranslate(float x, float y, float z)
{
    M4 mret;
    mret._m[12] = x; mret._m[13] = y; mret._m[14] = z;
    return mret;
}

//---------------------------------------------------------------------------------------
//http://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
inline M4 MLook(const V3& eye,const  V3& fwd,const  V3& up,const  V3& side)
{
    M4 mret;
    mret._m[0] = side.x;    mret._m[4] = side.y;    mret._m[8] = side.z;   mret._m[12] = 0.0;
    mret._m[1] = up.x;      mret._m[5] = up.y;      mret._m[9] = up.z;     mret._m[13] = 0.0;
    mret._m[2] = -fwd.x;    mret._m[6] = -fwd.y;    mret._m[10] = -fwd.z;   mret._m[14] = 0.0;
    mret._m[3] = 0.0;       mret._m[7] = 0.0;       mret._m[11] = 0.0;      mret._m[15] = 1.0;
    mret *= MTranslate(-eye.x, -eye.y, -eye.z);
    return mret;
}

#endif //
