// Copyright (c) 2016 Doyub Kim

#include <pch.h>
#include <jet/constant_vector_field2.h>

using namespace jet;

ConstantVectorField2::ConstantVectorField2(const Vector2D& value) :
    _value(value) {
}

Vector2D ConstantVectorField2::sample(const Vector2D& x) const {
    UNUSED_VARIABLE(x);

    return _value;
}

std::function<Vector2D(const Vector2D&)> ConstantVectorField2::sampler() const {
    return [this](const Vector2D&) -> Vector2D {
        return _value;
    };
}
