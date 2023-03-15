#define CATCH_Solver
#include <Eigen/Dense>
#include <autodiff/forward/real.hpp>
#include <autodiff/forward/real/eigen.hpp>
#include <chrono>
#include <string>
#include <unsupported/Eigen/AutoDiff>

#include "../include/Parser.hpp"
#include "../include/Solver.hpp"
#include "catch2/catch.hpp"

using namespace tr;
using namespace parser;
using namespace kinematics;
using namespace dynamics;
using namespace solver;

TEST_CASE("Test single euler integration step for simple model", "[Solver]") {
    // Create a robot model
    auto robot_model = import_urdf<double, 4>("data/urdfs/simple.urdf");

    // Create initial conditions
    Eigen::Matrix<double, 4, 1> q0 = robot_model.home_configuration();
    Eigen::Matrix<double, 4, 1> p0 = Eigen::Matrix<double, 4, 1>::Zero();
    p0 << 0, 1, 0, 0;
    Eigen::Matrix<double, 4, 1> u0 = Eigen::Matrix<double, 4, 1>::Zero();
    double dt                      = 0.1;

    // Run a single step of euler integration
    Eigen::Matrix<double, 8, 1> result;
    result = euler_step(robot_model, q0, p0, u0, dt);
}

TEST_CASE("Test integration routine for simple model with euler integration", "[Solver]") {
    // Create a robot model
    auto robot_model = import_urdf<double, 4>("data/urdfs/simple.urdf");

    // Create initial conditions
    Eigen::Matrix<double, 4, 1> q0 = robot_model.home_configuration();
    Eigen::Matrix<double, 4, 1> p0 = Eigen::Matrix<double, 4, 1>::Zero();
    p0 << 0, 1, 0, 0;
    Eigen::Matrix<double, 4, 1> u0 = Eigen::Matrix<double, 4, 1>::Zero();
    Eigen::Matrix<double, 2, 1> tspan;
    tspan << 0.0, 10.0;
    double dt = 0.1;

    // Run solver
    SolverParams<double, 4> params;
    params.dt                 = 0.1;
    params.tspan              = std::pair<float, float>(0.0, 10.0);
    params.integration_method = IntegrationMethod::RK4;
    auto results              = tr::solver::solver(robot_model, q0, p0, u0, params);

    // TODO: Verify results
}

TEST_CASE("Test integration routine for simple model with symplectic euler integration", "[Solver]") {
    // Create a robot model
    auto robot_model = import_urdf<double, 4>("data/urdfs/simple.urdf");

    // Create initial conditions
    Eigen::Matrix<double, 4, 1> q0 = robot_model.home_configuration();
    Eigen::Matrix<double, 4, 1> p0 = Eigen::Matrix<double, 4, 1>::Zero();
    p0 << 0, 1, 0, 0;
    Eigen::Matrix<double, 4, 1> u0 = Eigen::Matrix<double, 4, 1>::Zero();
    Eigen::Matrix<double, 2, 1> tspan;
    tspan << 0.0, 10.0;
    double dt = 0.01;

    // Run solver
    SolverParams<double, 4> params;
    params.dt                 = 0.1;
    params.tspan              = std::pair<float, float>(0.0, 10.0);
    params.integration_method = IntegrationMethod::SYMPLECTIC_EULER;
    auto results              = tr::solver::solver(robot_model, q0, p0, u0, params);

    // TODO: Verify results
}