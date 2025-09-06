/**
 * @file GeometryTopologyEdge.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Neutral representation of edge
 */

#include <memory>
#include <iostream>
#include <unordered_map>

#include "geometry-topology/GeometryTopologyEdge.hpp"

GeometryTopologyEdge::GeometryTopologyEdge(std::shared_ptr<GeometryTopologyVertex> vertex1_ptr, std::shared_ptr<GeometryTopologyVertex> vertex2_ptr) {
    _type = GeometryTopology::Type::EDGE;

    _vertices[0] = vertex1_ptr;
    _vertices[1] = vertex2_ptr;

    std::cout << "Vertex 1: " << vertex1_ptr << ", Vertex 2: " << vertex2_ptr << std::endl;
}

GeometryTopologyEdge::~GeometryTopologyEdge() {
    // TBA
}

void GeometryTopologyEdge::getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type) {
    if (type < _type) {
        for (auto vertex : _vertices) {
            if (type + 1 == _type) {
                if (!list.contains(vertex)) {
                    list.insert(std::make_pair(vertex, list.size()));
                }
            }
            else {
                vertex->getDescendants(list, type);
            }
        }
    }
    else {
        return;
    }
}

std::shared_ptr<GeometryTopologyVertex> GeometryTopologyEdge::getVertex(unsigned int vertex_idx) {
    return _vertices[vertex_idx];
}