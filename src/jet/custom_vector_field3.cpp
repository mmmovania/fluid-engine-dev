// Copyright (c) 2016 Doyub Kim

#include <pch.h>
#include <jet/custom_vector_field3.h>

using namespace jet;

CustomVectorField3::CustomVectorField3(
    const std::function<Vector3D(const Vector3D&)>& customFunction,
    double derivativeResolution) :
    _customFunction(customFunction),
    _resolution(derivativeResolution) {
}

CustomVectorField3::CustomVectorField3(
    const std::function<Vector3D(const Vector3D&)>& customFunction,
    const std::function<double(const Vector3D&)>& customDivergenceFunction,
    double derivativeResolution) :
    _customFunction(customFunction),
    _customDivergenceFunction(customDivergenceFunction),
    _resolution(derivativeResolution) {
}

CustomVectorField3::CustomVectorField3(
    const std::function<Vector3D(const Vector3D&)>& customFunction,
    const std::function<double(const Vector3D&)>& customDivergenceFunction,
    const std::function<Vector3D(const Vector3D&)>& customCurlFunction) :
    _customFunction(customFunction),
    _customDivergenceFunction(customDivergenceFunction),
    _customCurlFunction(customCurlFunction) {
}

Vector3D CustomVectorField3::sample(const Vector3D& x) const {
    return _customFunction(x);
}

double CustomVectorField3::divergence(const Vector3D& x) const {
    if (_customDivergenceFunction) {
        return _customDivergenceFunction(x);
    } else {
        double left
            = _customFunction(x - Vector3D(0.5 * _resolution, 0.0, 0.0)).x;
        double right
            = _customFunction(x + Vector3D(0.5 * _resolution, 0.0, 0.0)).x;
        double bottom
            = _customFunction(x - Vector3D(0.0, 0.5 * _resolution, 0.0)).y;
        double top
            = _customFunction(x + Vector3D(0.0, 0.5 * _resolution, 0.0)).y;
        double back
            = _customFunction(x - Vector3D(0.0, 0.0, 0.5 * _resolution)).z;
        double front
            = _customFunction(x + Vector3D(0.0, 0.0, 0.5 * _resolution)).z;

        return (right - left + top - bottom + front - back) / _resolution;
    }
}

Vector3D CustomVectorField3::curl(const Vector3D& x) const {
    if (_customCurlFunction) {
        return _customCurlFunction(x);
    } else {
        Vector3D left
            = _customFunction(x - Vector3D(0.5 * _resolution, 0.0, 0.0));
        Vector3D right
            = _customFunction(x + Vector3D(0.5 * _resolution, 0.0, 0.0));
        Vector3D bottom
            = _customFunction(x - Vector3D(0.0, 0.5 * _resolution, 0.0));
        Vector3D top
            = _customFunction(x + Vector3D(0.0, 0.5 * _resolution, 0.0));
        Vector3D back
            = _customFunction(x - Vector3D(0.0, 0.0, 0.5 * _resolution));
        Vector3D front
            = _customFunction(x + Vector3D(0.0, 0.0, 0.5 * _resolution));

        double Fx_ym = bottom.x;
        double Fx_yp = top.x;
        double Fx_zm = back.x;
        double Fx_zp = front.x;

        double Fy_xm = left.y;
        double Fy_xp = right.y;
        double Fy_zm = back.y;
        double Fy_zp = front.y;

        double Fz_xm = left.z;
        double Fz_xp = right.z;
        double Fz_ym = bottom.z;
        double Fz_yp = top.z;

        return Vector3D(
            (Fz_yp - Fz_ym) - (Fy_zp - Fy_zm),
            (Fx_zp - Fx_zm) - (Fz_xp - Fz_xm),
            (Fy_xp - Fy_xm) - (Fx_yp - Fx_ym)) / _resolution;
    }
}

std::function<Vector3D(const Vector3D&)> CustomVectorField3::sampler() const {
    return _customFunction;
}
