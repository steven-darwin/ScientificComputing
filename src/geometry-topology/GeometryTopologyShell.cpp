/**
 * @file GeometryTopologyShell.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Neutral representation of closed set of faces
 */

#include <memory>
#include <iostream>
#include <unordered_map>

#include "geometry-topology/GeometryTopologyShell.hpp"
#include "geometry-topology/GeometryTopologyFace.hpp"

GeometryTopologyShell::GeometryTopologyShell() {
    _type = GeometryTopology::Type::SHELL;
}

GeometryTopologyShell::~GeometryTopologyShell() {
    // TBA
}

void GeometryTopologyShell::getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type) {
    if (type < _type) {
        for (auto face : _faces) {
            if (type + 1 == _type) {
                if (!list.contains(std::get<std::shared_ptr<GeometryTopologyFace>>(face))) {
                    list.insert(std::make_pair(std::get<std::shared_ptr<GeometryTopologyFace>>(face), list.size()));
                }
            }
            else {
                std::get<std::shared_ptr<GeometryTopologyFace>>(face)->getDescendants(list, type);
            }
        }
    }
    else {
        return;
    }
}

std::shared_ptr<GeometryTopologyShell> GeometryTopologyShell::reverseCopy() {
    std::shared_ptr<GeometryTopologyShell> reverse = std::make_shared<GeometryTopologyShell>();

    for (auto iter = _faces.rbegin(); iter != _faces.rend(); iter++) {
        reverse->addFace(std::get<std::shared_ptr<GeometryTopologyFace>>(*iter), std::get<unsigned int>(*iter) == 0 ? 1 : 0);
    }

    return reverse;
}

bool GeometryTopologyShell::isClosed() {
    return true;
}

void GeometryTopologyShell::addFace(std::shared_ptr<GeometryTopologyFace> face_ptr, unsigned int ccw_wire_idx) {
    _faces.push_back({ face_ptr, ccw_wire_idx });
    std::cout << "Face: " << face_ptr << ", CCW Wire: " << face_ptr->getWire(ccw_wire_idx) << std::endl;
}