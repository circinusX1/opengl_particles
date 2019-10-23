#ifndef CAMERA_H
#define CAMERA_H

#include "vertex.h"

class Camera
{
public:
    Camera(const V3& eye, float azimuth = 0.0f,
                          float elevation = 0.0f,
                          float roll = 0.0f);
    virtual ~Camera();

    // make from camera field a lookat matrix.
    // http://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
    const M4 GetViewMtx(float dTime)
    {
        return MLook(_pos, _fwd, _up, _right);
    }


    void Move(float f, float s, float u)
    {
        if(u)MoveUp(u);
        if(s)MoveSide(s);
        if(f)MoveFwd(f);

    }

    void	MoveUp(float r){_pos   += r * _up;}
    void	MoveSide(float r){_pos += r * _right;}
    void	MoveFwd(float r){_pos  += r * _fwd;}
    void    Rotate(float a, float e, float r)
    {
        _euler.y += a;
	    _euler.x -= e;
	    _euler.z += r;
	    BLOCKRANGE(_euler.x);
        Euler2Pos();
    }

    //http://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
    void Euler2Pos()
    {
        float CosrAz = Cosr(_euler.y);
        float CosrEl = Cosr(_euler.x);
        float SinrAz = Sinr(_euler.y);
        float SinrEl = Sinr(_euler.x);
        float CosrRl = Cosr(_euler.z);
        float SinrRl = Sinr(_euler.z);
        _fwd.x = SinrAz * CosrEl;
        _fwd.y = SinrEl;
        _fwd.z = CosrEl * -CosrAz;
        _up.x = -CosrAz * SinrRl - SinrAz * SinrEl * CosrRl;
        _up.y = CosrEl * CosrRl;
        _up.z = -SinrAz * SinrRl - SinrEl * CosrRl * -CosrAz;
        _right = Vcp(_fwd, _up);
    }
protected:
private:

    V3  _pos;
    V3  _fwd;
    V3  _up;
    V3  _right;
    V3  _euler;
    float _fov;   // field of view angle
};

#endif // CAMERA_H
