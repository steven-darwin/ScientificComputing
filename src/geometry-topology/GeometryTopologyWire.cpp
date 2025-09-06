/**
 * @file GeometryTopologyWire.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Neutral representation of closed set of edges
 */

#include <tuple>
#include <memory>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "geometry-topology/GeometryTopologyWire.hpp"
#include "geometry-topology/GeometryTopologyEdge.hpp"

GeometryTopologyWire::GeometryTopologyWire() {
    _type = GeometryTopology::Type::WIRE;
}

GeometryTopologyWire::~GeometryTopologyWire() {
    // TBA
}

void GeometryTopologyWire::getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type) {
    if (type < _type) {
        for (auto edge : _edges) {
            if (type + 1 == _type) {
                if (!list.contains(std::get<std::shared_ptr<GeometryTopologyEdge>>(edge))) {
                    list.insert(std::make_pair(std::get<std::shared_ptr<GeometryTopologyEdge>>(edge), list.size()));
                }
            }
            else {
                std::get<std::shared_ptr<GeometryTopologyEdge>>(edge)->getDescendants(list, type);
            }
        }
    }
    else {
        return;
    }
}

std::shared_ptr<GeometryTopologyWire> GeometryTopologyWire::reverseCopy() {
    std::shared_ptr<GeometryTopologyWire> reverse = std::make_shared<GeometryTopologyWire>();

    for (auto iter = _edges.rbegin(); iter != _edges.rend(); iter++) {
        reverse->addEdge(std::get<std::shared_ptr<GeometryTopologyEdge>>(*iter), std::get<unsigned int>(*iter) == 0 ? 1 : 0);
    }

    return reverse;
}

bool GeometryTopologyWire::isClosed() {
    return true;
}

void GeometryTopologyWire::addEdge(std::shared_ptr<GeometryTopologyEdge> edge_ptr, unsigned int origin_vertex_idx) {
    _edges.push_back({edge_ptr, origin_vertex_idx});
    std::cout << "Edge: " << edge_ptr << ", Origin Vertex: " << edge_ptr->getVertex(origin_vertex_idx) << std::endl;
}