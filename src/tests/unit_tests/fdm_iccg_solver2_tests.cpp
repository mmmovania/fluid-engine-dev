// Copyright (c) 2016 Doyub Kim

#include <jet/fdm_iccg_solver2.h>
#include <gtest/gtest.h>

using namespace jet;

TEST(FdmIccgSolver2, Constructors) {
    FdmLinearSystem2 system;
    system.A.resize(3, 3);
    system.x.resize(3, 3);
    system.b.resize(3, 3);

    system.A.forEachIndex([&](size_t i, size_t j) {
        if (i > 0) {
            system.A(i, j).center += 1.0;
        }
        if (i < system.A.width() - 1) {
            system.A(i, j).center += 1.0;
            system.A(i, j).right -= 1.0;
        }

        if (j > 0) {
            system.A(i, j).center += 1.0;
        } else {
            system.b(i, j) += 1.0;
        }

        if (j < system.A.height() - 1) {
            system.A(i, j).center += 1.0;
            system.A(i, j).up -= 1.0;
        } else {
            system.b(i, j) -= 1.0;
        }
    });

    FdmIccgSolver2 solver(10, 1e-9);
    solver.solve(&system);

    EXPECT_GT(solver.tolerance(), solver.lastResidual());
}
