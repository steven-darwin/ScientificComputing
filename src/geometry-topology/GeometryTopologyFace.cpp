/**
 * @file GeometryTopologyFace.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Neutral representation of face
 */

#include <iostream>
#include <unordered_map>

#include "geometry-topology/GeometryTopologyFace.hpp"

GeometryTopologyFace::GeometryTopologyFace(std::shared_ptr<GeometryTopologyWire> wire1_ptr, std::shared_ptr<GeometryTopologyWire> wire2_ptr) {
    _type = GeometryTopology::Type::FACE;

    _wires[0] = wire1_ptr;
    _wires[1] = wire2_ptr;

    std::cout << "Wire 1: " << wire1_ptr << ", Wire 2: " << wire2_ptr << std::endl;
}

GeometryTopologyFace::~GeometryTopologyFace() {
    // TBA
}

void GeometryTopologyFace::getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type) {
    if (type < _type) {
        for (auto wire : _wires) {
            if (type + 1 == _type) {
                if (!list.contains(wire)) {
                    list.insert(std::make_pair(wire, list.size()));
                }
            }
            else {
                wire->getDescendants(list, type);
            }
        }
    }
    else {
        return;
    }
}

std::shared_ptr<GeometryTopologyWire> GeometryTopologyFace::getWire(unsigned int wire_idx) {
    return _wires[wire_idx];
}