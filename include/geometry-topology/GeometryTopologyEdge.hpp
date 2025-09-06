/**
 * @file GeometryTopologyEdge.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Header] Neutral representation of edge
 */

#ifndef GEOMETRY_TOPOLOGY_EDGE_HPP
#define GEOMETRY_TOPOLOGY_EDGE_HPP

#include <array>
#include <memory>
#include <unordered_map>

#include "GeometryTopology.hpp"
#include "GeometryTopologyVertex.hpp"

class GeometryTopologyEdge : public GeometryTopology {
public:
    /** Constructor of GeometryTopologyEdge object
     */
    GeometryTopologyEdge(std::shared_ptr<GeometryTopologyVertex> vertex1_ptr, std::shared_ptr<GeometryTopologyVertex> vertex2_ptr);

    /** Destructor of GeometryTopologyEdge object */
    ~GeometryTopologyEdge();

    /** Method that traverse GeometryTopologyEdge data structure and return set of GeometryTopology object with particular type */
    void getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type);

    /** Method to get address of vertex on the list of vertices that build this edge */
    std::shared_ptr<GeometryTopologyVertex> getVertex(unsigned int vertex_idx);
private:
    /** Attribute to store list of vertices that builds this edge */
    std::array<std::shared_ptr<GeometryTopologyVertex>, 2> _vertices = {nullptr, nullptr};
};

#endif