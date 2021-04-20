#include <Eigen/Geometry>
#include <iostream>

#include "vector_utils.h"

// FIXME
#define X 0
#define Y 1
#define Z 2
#define DASH "--------------------------------------------------------------------------"

std::pair<double, Eigen::Vector3d> getAreaVector(Eigen::Vector3d const &mid, Eigen::Vector3d const &next, Eigen::Vector3d const &prev) {
	Eigen::Vector3d nextEdge = next - mid;
	Eigen::Vector3d prevEdge = prev - mid;
	Eigen::Vector3d cross = nextEdge.cross(prevEdge);
	double norm = cross.norm();
	return std::make_pair(0.5*norm, cross / norm);
}

double getCosOfAngle(Eigen::Vector3d const &mid, Eigen::Vector3d const &v1, Eigen::Vector3d const &v2) {
	Eigen::Vector3d edge1 = v1 - mid;
	Eigen::Vector3d edge2 = v2 - mid;
	double length1 = edge1.norm();
	double length2 = edge2.norm();
	double dot = edge1.dot(edge2);
	return dot / (length1*length2);
}

Eigen::Matrix3d getRotationMatrix(Eigen::Vector3d const &oldAxis, Eigen::Vector3d const &newAxis, int axisToAlign) {
	Eigen::Matrix3d rotationMat, vCross;
	Eigen::Vector3d v;
	double c;

	v = oldAxis.cross(newAxis);
	c = oldAxis.dot(newAxis);

	if (c != -1) {
		vCross << 0, -v[Z], v[Y],
			v[Z], 0, -v[X],
			-v[Y], v[X], 0;

		rotationMat << Eigen::MatrixXd::Identity(3, 3);
		rotationMat += vCross + (vCross * vCross) / (1 + c);
	}
	else { // rotate around (axisToAlign + 2) % 3 by PI radians (mirror other axis)
		rotationMat = Eigen::MatrixXd::Identity(3, 3);
		rotationMat.col(axisToAlign) *= -1;
		rotationMat.col((axisToAlign + 1) % 3) *= -1;
	}

	return rotationMat;
}

/*
Eigen::Matrix3d getRotationMatrix(Eigen::Matrix3d const &oldBase, Eigen::Matrix3d const &newBase, int axisToAlign) {
	Eigen::Matrix3d rotationMat, vCross;
	Eigen::Vector3d v, oldAxis, newAxis;
	double c;

	oldAxis << oldBase.col(axisToAlign); 
	newAxis << newBase.col(axisToAlign);
	v = oldAxis.cross(newAxis);
	c = oldAxis.dot(newAxis);

	if (c != -1) {
		vCross << 0, -v[Z], v[Y],
				  v[Z], 0, -v[X],
			     -v[Y], v[X], 0;

		rotationMat << Eigen::MatrixXd::Identity(3, 3);
		rotationMat += vCross + (vCross * vCross) / (1 + c);
	}
	else { // rotate around (axisToAlign + 2) % 3 by PI radians (mirror other axis)
		rotationMat = Eigen::MatrixXd::Identity(3,3);
		rotationMat.col(axisToAlign) *= -1;
		rotationMat.col((axisToAlign + 1) % 3) *= -1;
	}

	return rotationMat;
}
*/
/*
void calcRotatedVertices(Eigen::Matrix3d &newBase, Eigen::Vector3d const vertices[], Eigen::Vector3d localVertices[]) {
	Eigen::Matrix3d rotationMat;

	rotationMat = getRotationMatrix(Eigen::MatrixXd::Identity(3, 3), newBase, Z);
	rotationMat *= getRotationMatrix(rotationMat, newBase, Y); // perform both rotations

	// TODO delete:
	std::cout << "newBase: " << std::endl << newBase << std::endl;
	std::cout << "rotation matrix: " << std::endl << rotationMat << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << "rotating: " << vertices[i] << std::endl;
		localVertices[i] = rotationMat * vertices[i];
		std::cout << "rotated: " << vertices[i] << std::endl;
	}
	std::cout << DASH << std::endl;
}
*/
