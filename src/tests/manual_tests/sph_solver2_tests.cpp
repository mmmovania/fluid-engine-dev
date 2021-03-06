// Copyright (c) 2016 Doyub Kim

#include <manual_tests.h>

#include <jet/box2.h>
#include <jet/implicit_surface_set2.h>
#include <jet/plane2.h>
#include <jet/rigid_body_collider2.h>
#include <jet/sph_solver2.h>
#include <jet/sphere2.h>
#include <jet/surface_to_implicit2.h>
#include <jet/volume_particle_emitter2.h>

using namespace jet;

JET_TESTS(SphSolver2);

JET_BEGIN_TEST_F(SphSolver2, SteadyState) {
    SphSolver2 solver;
    SphSystemData2Ptr particles = solver.sphSystemData();
    const double targetSpacing = particles->targetSpacing();

    BoundingBox2D initialBound(Vector2D(), Vector2D(1, 0.5));
    initialBound.expand(-targetSpacing);

    auto emitter = std::make_shared<VolumeParticleEmitter2>(
        std::make_shared<SurfaceToImplicit2>(
            std::make_shared<Sphere2>(Vector2D(), 10.0)),
        initialBound,
        particles->targetSpacing(),
        Vector2D());
    emitter->setJitter(0.0);

    Box2Ptr box = std::make_shared<Box2>(Vector2D(), Vector2D(1, 1));
    box->isNormalFlipped = true;
    RigidBodyCollider2Ptr collider = std::make_shared<RigidBodyCollider2>(box);

    solver.setCollider(collider);

    saveParticleDataXy(particles, 0);

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 10; frame.advance()) {
        emitter->emit(frame, particles);
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);
    }
}
JET_END_TEST_F

JET_BEGIN_TEST_F(SphSolver2, WaterDrop) {
    const double targetSpacing = 0.02;

    BoundingBox2D domain(Vector2D(), Vector2D(1, 2));

    // Initialize solvers
    SphSolver2 solver;

    SphSystemData2Ptr particles = solver.sphSystemData();
    particles->setTargetDensity(1000.0);
    particles->setTargetSpacing(targetSpacing);

    // Initialize source
    ImplicitSurfaceSet2Ptr surfaceSet = std::make_shared<ImplicitSurfaceSet2>();
    surfaceSet->addExplicitSurface(
        std::make_shared<Plane2>(
            Vector2D(0, 1), Vector2D(0, 0.25 * domain.height())));
    surfaceSet->addExplicitSurface(
        std::make_shared<Sphere2>(
            domain.midPoint(), 0.15 * domain.width()));

    BoundingBox2D sourceBound(domain);
    sourceBound.expand(-targetSpacing);

    auto emitter = std::make_shared<VolumeParticleEmitter2>(
        surfaceSet,
        sourceBound,
        targetSpacing,
        Vector2D());
    emitter->emit(Frame(), particles);

    // Initialize boundary
    Box2Ptr box = std::make_shared<Box2>(domain);
    box->isNormalFlipped = true;
    RigidBodyCollider2Ptr collider = std::make_shared<RigidBodyCollider2>(box);

    // Setup solver
    solver.setCollider(collider);

    saveParticleDataXy(particles, 0);

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 120; frame.advance()) {
        emitter->emit(frame, particles);
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);
    }
}
JET_END_TEST_F

JET_BEGIN_TEST_F(SphSolver2, WaterDropLargeDt) {
    const double targetSpacing = 0.02;

    BoundingBox2D domain(Vector2D(), Vector2D(1, 2));

    // Initialize solvers
    SphSolver2 solver;

    SphSystemData2Ptr particles = solver.sphSystemData();
    particles->setTargetDensity(1000.0);
    particles->setTargetSpacing(targetSpacing);

    // Initialize source
    ImplicitSurfaceSet2Ptr surfaceSet = std::make_shared<ImplicitSurfaceSet2>();
    surfaceSet->addExplicitSurface(
        std::make_shared<Plane2>(
            Vector2D(0, 1), Vector2D(0, 0.25 * domain.height())));
    surfaceSet->addExplicitSurface(
        std::make_shared<Sphere2>(
            domain.midPoint(), 0.15 * domain.width()));

    BoundingBox2D sourceBound(domain);
    sourceBound.expand(-targetSpacing);

    auto emitter = std::make_shared<VolumeParticleEmitter2>(
        surfaceSet,
        sourceBound,
        targetSpacing,
        Vector2D());
    emitter->emit(Frame(), particles);

    // Initialize boundary
    Box2Ptr box = std::make_shared<Box2>(domain);
    box->isNormalFlipped = true;
    RigidBodyCollider2Ptr collider = std::make_shared<RigidBodyCollider2>(box);

    // Setup solver
    solver.setCollider(collider);
    solver.setTimeStepLimitScale(10.0);

    saveParticleDataXy(particles, 0);

    Frame frame(1, 1.0 / 60.0);
    for ( ; frame.index < 120; frame.advance()) {
        emitter->emit(frame, particles);
        solver.update(frame);

        saveParticleDataXy(particles, frame.index);
    }
}
JET_END_TEST_F
