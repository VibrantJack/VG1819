#pragma once
#include "puppy\P_Common.h"

namespace scene
{
	struct Frustum
	{
		glm::vec4 planes[6];
	};


	//This method assumes the points are given in clockwise.
	static glm::vec4 computePlane(const glm::vec3& p_point1, const glm::vec3 p_point2, const glm::vec3 p_point3)
	{
		//Based on : http://www.lighthouse3d.com/tutorials/maths/plane/
		glm::vec3 v = p_point2 - p_point1;
		glm::vec3 u = p_point3 - p_point1;

		glm::vec3 n = glm::cross(v, u);
		n = glm::normalize(n);

		glm::vec4 plane;
		plane[0] = n[0]; //A coefficient
		plane[1] = n[1]; //B coefficient
		plane[2] = n[2]; //C coefficient
		plane[3] = -1 * (glm::dot(n, p_point1)); //D

		return plane;
	}

	//Below methods used if frustum was wanted from a matrix
	
	static void normalizePlane(glm::vec4& p_toNormalize)
	{
		glm::vec3 plane(p_toNormalize[0], p_toNormalize[1], p_toNormalize[2]);
		float length = glm::length(plane);
		p_toNormalize = p_toNormalize / length;
	}

	static Frustum getFrustum(const glm::mat4& p_matrix)
	{
		Frustum toReturn;

		glm::vec4 rowX(p_matrix[0][0], p_matrix[0][1], p_matrix[0][2], p_matrix[0][3]);
		glm::vec4 rowY(p_matrix[1][0], p_matrix[1][1], p_matrix[1][2], p_matrix[1][3]);
		glm::vec4 rowZ(p_matrix[2][0], p_matrix[2][1], p_matrix[2][2], p_matrix[2][3]);
		glm::vec4 rowW(p_matrix[3][0], p_matrix[3][1], p_matrix[3][2], p_matrix[3][3]);

		//Left plane
		toReturn.planes[0] = (rowW + rowX);
		normalizePlane(toReturn.planes[0]);
		//Right plane
		toReturn.planes[1] = (rowW - rowX);
		normalizePlane(toReturn.planes[1]);
		//Top plane
		toReturn.planes[2] = (rowW - rowY);
		normalizePlane(toReturn.planes[2]);
		//Bottom plane
		toReturn.planes[3] = (rowW + rowY);
		normalizePlane(toReturn.planes[3]);
		//Near plane
		toReturn.planes[4] = (rowW + rowZ);
		normalizePlane(toReturn.planes[4]);
		//Far plane
		toReturn.planes[5] = (rowW - rowZ);
		normalizePlane(toReturn.planes[5]);

		return toReturn;
	}
}