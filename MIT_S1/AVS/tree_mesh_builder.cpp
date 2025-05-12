/**
 * @file    tree_mesh_builder.cpp
 *
 * @author  Alexej Beňuš <xbenus01@stud.fit.vutbr.cz>
 *
 * @brief   Parallel Marching Cubes implementation using OpenMP tasks +
 octree *early elimination
 *
 * @date    03.12.2024
 **/

#include <iostream>
#include <limits>

#include "tree_mesh_builder.h"

TreeMeshBuilder::TreeMeshBuilder(unsigned gridEdgeSize)
    : BaseMeshBuilder(gridEdgeSize, "Octree")
{
}

unsigned TreeMeshBuilder::marchCubes(const ParametricScalarField &field)
{
    unsigned totalTriangles = 0;
#pragma omp parallel
    {
#pragma omp single
        {
            totalTriangles =
                processOctreeNode(0.0, 0.0, 0.0, mGridSize,
                                  field); // Zkusit prohodit parametry? TODO
        }
    }
    return totalTriangles;
}

unsigned TreeMeshBuilder::processOctreeNode(const float x, const float y,
                                            const float z, float size,
                                            const ParametricScalarField &field)
{
    const float childSize = size / 2.0f;
    static const float expr = sqrt(3) / (float)2.0 * mGridResolution;
    // Compute whether the block intersects the isosurface

    Vec3_t<float> center((x + childSize) * mGridResolution,
                         (y + childSize) * mGridResolution,
                         (z + childSize) * mGridResolution);
    if (evaluateFieldAt(center, field) > mIsoLevel + expr * size)
    {
        return 0;
    }
    else if (size > SIZE_CUT_OFF)
    {
        unsigned localTriangles = 0;
        // if (size < TASK_CREATION_CUT_OFF) // do it sequentially
        // {
        //     for (int i = 0; i < 8; ++i)
        //     {
        //         float dx = (i & 1) ? childSize : 0.0f;
        //         float dy = (i & 2) ? childSize : 0.0f;
        //         float dz = (i & 4) ? childSize : 0.0f;
        //         localTriangles +=
        //             processOctreeNode(x + dx, y + dy, z + dz, childSize,
        //             field);
        //     }
        //     return localTriangles;
        // }
        for (int i = 0; i < 8; ++i)
        {
#pragma omp task shared(localTriangles)
            {
                float dx = (i & 1) ? childSize : 0.0f;
                float dy = (i & 2) ? childSize : 0.0f;
                float dz = (i & 4) ? childSize : 0.0f;
                unsigned tmp =
                    processOctreeNode(x + dx, y + dy, z + dz, childSize, field);
#pragma omp atomic update
                localTriangles += tmp;
            }
        }
#pragma omp taskwait
        return localTriangles;
    }
    else // if (size <= CUT_OFF)
    {
        return buildCube(Vec3_t<float>(x, y, z), field);
    }
}

float TreeMeshBuilder::evaluateFieldAt(const Vec3_t<float> &pos,
                                       const ParametricScalarField &field)
{
    const Vec3_t<float> *pPoints = field.getPoints().data();
    const unsigned count = unsigned(field.getPoints().size());

    float value = std::numeric_limits<float>::max();

    for (unsigned i = 0; i < count; ++i)
    {
        float distanceSquared = (pos.x - pPoints[i].x) * (pos.x - pPoints[i].x);
        distanceSquared += (pos.y - pPoints[i].y) * (pos.y - pPoints[i].y);
        distanceSquared += (pos.z - pPoints[i].z) * (pos.z - pPoints[i].z);

        value = std::min(value, distanceSquared);
    }
    return sqrt(value);
}

void TreeMeshBuilder::emitTriangle(const BaseMeshBuilder::Triangle_t &triangle)
{
#pragma omp critical(treeEmitTriangle)
    {
        _triangles.push_back(triangle);
    }
}
