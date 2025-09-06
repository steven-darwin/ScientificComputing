/**
 * @file GeometryTopologyWire.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Header] Neutral representation of closed set of edges
 */

#ifndef GEOMETRY_TOPOLOGY_WIRE_HPP
#define GEOMETRY_TOPOLOGY_WIRE_HPP

#include <tuple>
#include <memory>
#include <vector>
#include <unordered_map>

#include "GeometryTopology.hpp"
#include "GeometryTopologyEdge.hpp"

class GeometryTopologyWire : public GeometryTopology {
public:
    /** Constructor of GeometryTopologyWire object
     */
    GeometryTopologyWire();

    /** Destructor of GeometryTopologyWire object */
    ~GeometryTopologyWire();

    /** Method that traverse GeometryTopologyWire data structure and return set of GeometryTopology object with particular type */
    void getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type);

    /** Method to copy wire object but with the list of edges being reversed */
    std::shared_ptr<GeometryTopologyWire> reverseCopy();

    /** Method to check if the wire is created by a closed set of edges */
    bool isClosed();

    /** Method to add edge on list of edges that build this wire */
    void addEdge(std::shared_ptr<GeometryTopologyEdge> edge_ptr, unsigned int origin_vertex_idx);
private:
    /** Attribute to store list of edges that build this wire */
    std::vector<std::tuple<std::shared_ptr<GeometryTopologyEdge>, unsigned int>> _edges;
};

#endif