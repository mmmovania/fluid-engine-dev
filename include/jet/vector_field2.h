// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_VECTOR_FIELD2_H_
#define INCLUDE_JET_VECTOR_FIELD2_H_

#include <jet/field2.h>
#include <jet/vector2.h>
#include <functional>
#include <memory>

namespace jet {

//! Abstract base class for 2-D vector field.
class VectorField2 : public Field2 {
 public:
    //! Default constructor.
    VectorField2();

    //! Default destructor.
    virtual ~VectorField2();

    //! Returns sampled value at given position \p x.
    virtual Vector2D sample(const Vector2D& x) const = 0;

    //! Returns divergence at given position \p x.
    virtual double divergence(const Vector2D& x) const;

    //! Returns curl at given position \p x.
    virtual double curl(const Vector2D& x) const;

    //! Returns sampler function object.
    virtual std::function<Vector2D(const Vector2D&)> sampler() const;
};

typedef std::shared_ptr<VectorField2> VectorField2Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_VECTOR_FIELD2_H_
