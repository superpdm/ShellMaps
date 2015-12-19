#pragma once

#include "mycommon.h"
#include "trimesh.h"
#include "tetra.h"

using nanogui::MatrixXf;
using nanogui::MatrixXu;

extern void generateOffsetSurface(const MatrixXu &F, const MatrixXf &V, MatrixXu &oF, MatrixXf &oV, const float offset);

enum SPLIT_PATTERN {
	SPLIT_PATTERN_NONE = 0,
	SPLIT_PATTERN_R,
	SPLIT_PATTERN_F,
	SPLIT_PATTEN_COUNT
};

/* The computing result Pattern P has the same dimenstions as F, P.col(i) records the splitting pattern for base triangle F.col(i) in prim(i).
	For example:
	P(0, i) = 1: edge0(p0->p1) in triangle i has splitting pattern R,
	P(0, i) = 2: edge0(p0->p1) in triangle i has splitting pattern F.
	P(0, i) = 0: edge0(p0->p1) in triangle i has not assigend a pattern.
*/
extern void computePrimsSplittingPattern(const MatrixXu &F, MatrixXu &P);

/* F: base mesh(face indices), oF: offset mesh, P: prims splitting pattern, T: Tetrahedra to be computed, size will be: [4, F.cols() * 3].
F and oF should not have same elements! A simple choice of oF here is oF += V.cols(), means, final V = V.append(oV) ...? */
// TODO: put this function as a local function in constructTetrahedronMesh.
extern void constructTetraheraFromPrimsSimple(const MatrixXu &F, const MatrixXu &oF, const MatrixXu &P, MatrixXu &T);

extern void constructTetrahedronMeshSimple(const TriMesh &baseMesh, const TriMesh &offsetMesh, const MatrixXu &P, TetrahedronMesh &tetrahedronMesh);