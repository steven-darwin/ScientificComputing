/**
 * @file GeometryTopologyVertex.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Neutral representation of vertex
 */

#include <iostream>
#include <unordered_map>

#include "geometry-topology/GeometryTopologyVertex.hpp"

GeometryTopologyVertex::GeometryTopologyVertex(double x, double y, double z) {
    _type = GeometryTopology::Type::VERTEX;

    _coordinateX = x;
    _coordinateY = y;
    _coordinateZ = z;

    std::cout << "X: " << _coordinateX << ", Y: " << _coordinateY << ", Z: " << _coordinateZ << std::endl;
}

GeometryTopologyVertex::~GeometryTopologyVertex() {
    // TBA
}

void GeometryTopologyVertex::getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type) {
    if (type < _type) {
        return;
    }
    else {
        return;
    }
}

double GeometryTopologyVertex::getCoordinate(GeometryTopologyVertex::Coordinate axis) {
    switch (axis) {
    case GeometryTopologyVertex::Coordinate::X:
        return _coordinateX;
    case GeometryTopologyVertex::Coordinate::Y:
        return _coordinateY;
    case GeometryTopologyVertex::Coordinate::Z:
        return _coordinateZ;
    }
}