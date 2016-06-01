// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID_BLOCKED_BOUNDARY_CONDITION_SOLVER3_H_
#define INCLUDE_JET_GRID_BLOCKED_BOUNDARY_CONDITION_SOLVER3_H_

#include <jet/grid_fractional_boundary_condition_solver3.h>

#include <memory>

namespace jet {

class GridBlockedBoundaryConditionSolver3 final
    : public GridFractionalBoundaryConditionSolver3 {
 public:
    GridBlockedBoundaryConditionSolver3();

    void constrainVelocity(
        FaceCenteredGrid3* velocity,
        unsigned int extrapolationDepth = 5) override;

    const Array3<char>& marker() const;

 protected:
    void onColliderUpdated(
        const Size3& gridSize,
        const Vector3D& gridSpacing,
        const Vector3D& gridOrigin) override;

 private:
    Array3<char> _marker;
};

typedef std::shared_ptr<GridBlockedBoundaryConditionSolver3>
    GridBlockedBoundaryConditionSolver3Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_GRID_BLOCKED_BOUNDARY_CONDITION_SOLVER3_H_
