// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID_FRACTIONAL_BOUNDARY_CONDITION_SOLVER3_H_
#define INCLUDE_JET_GRID_FRACTIONAL_BOUNDARY_CONDITION_SOLVER3_H_

#include <jet/cell_centered_scalar_grid3.h>
#include <jet/grid_boundary_condition_solver3.h>

#include <memory>

namespace jet {

//!
//! \brief Fractional 3-D boundary condition solver for grids.
//!
//! This class constrains the velocity field by projecting the flow to the
//! signed-distance field representation of the collider. This implementation
//! should pair up with GridFractionalSinglePhasePressureSolver3 to provide
//! sub-grid resolutional velocity projection.
//!
class GridFractionalBoundaryConditionSolver3
    : public GridBoundaryConditionSolver3 {
 public:
    //! Default constructor.
    GridFractionalBoundaryConditionSolver3();

    //! Default destructor.
    virtual ~GridFractionalBoundaryConditionSolver3();

    //!
    //! Constrains the velocity field to conform the collider boundary.
    //!
    //! \param velocity Input and output velocity grid.
    //! \param extrapolationDepth Number of inner-collider grid cells that
    //!     velocity will get extrapolated.
    //!
    void constrainVelocity(
        FaceCenteredGrid3* velocity,
        unsigned int extrapolationDepth = 5) override;

    //! Returns the signed distance field of the collider.
    const CellCenteredScalarGrid3& colliderSdf() const;

 protected:
    //! Invoked when a new collider is set.
    void onColliderUpdated(
        const Size3& gridSize,
        const Vector3D& gridSpacing,
        const Vector3D& gridOrigin) override;

 private:
    CellCenteredScalarGrid3 _colliderSdf;
};

typedef std::shared_ptr<GridFractionalBoundaryConditionSolver3>
    GridFractionalBoundaryConditionSolver3Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_GRID_FRACTIONAL_BOUNDARY_CONDITION_SOLVER3_H_
