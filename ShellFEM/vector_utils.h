#pragma once

#include <Eigen/Core>

std::pair<double, Eigen::Vector3d> getAreaVector(Eigen::Vector3d const &v1, Eigen::Vector3d const &v2, Eigen::Vector3d const &v3);
double getCosOfAngle(Eigen::Vector3d const &v1, Eigen::Vector3d const &v2, Eigen::Vector3d const &v3);
//void calcRotatedVertices(Eigen::Vector3d newAxes[3], Eigen::Vector3d const vertices[], Eigen::Vector3d localVertices[]);