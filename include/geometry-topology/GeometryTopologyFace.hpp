/**
 * @file GeometryTopologyFace.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Header] Neutral representation of cell
 */

#ifndef GEOMETRY_TOPOLOGY_FACE_HPP
#define GEOMETRY_TOPOLOGY_FACE_HPP

#include <array>
#include <memory>
#include <unordered_map>

#include "GeometryTopology.hpp"
#include "GeometryTopologyWire.hpp"

class GeometryTopologyFace : public GeometryTopology {
public:
    /** Constructor of GeometryTopologyFace object
     */
    GeometryTopologyFace(std::shared_ptr<GeometryTopologyWire> wire1_ptr, std::shared_ptr<GeometryTopologyWire> wire2_ptr);

    /** Destructor of GeometryTopologyFace object */
    ~GeometryTopologyFace();

    /** Method that traverse GeometryTopologyFace data structure and return set of GeometryTopology object with particular type */
    void getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type);

    /** Method to get address of wire on the list of wires that build this face */
    std::shared_ptr<GeometryTopologyWire> getWire(unsigned int wire_idx);
private:
    /** Attribute to store list of wires that builds this face */
    std::array<std::shared_ptr<GeometryTopologyWire>, 2> _wires;
};

#endif