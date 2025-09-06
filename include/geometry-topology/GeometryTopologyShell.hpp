/**
 * @file GeometryTopologyShell.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-18
 * @date Last Modified : 2025-08-30
 *
 * @brief [Header] Neutral representation of closed set of faces 
 */

#ifndef GEOMETRY_TOPOLOGY_SHELL_HPP
#define GEOMETRY_TOPOLOGY_SHELL_HPP

#include <tuple>
#include <memory>
#include <vector>
#include <unordered_map>

#include "GeometryTopology.hpp"
#include "GeometryTopologyFace.hpp"

class GeometryTopologyShell : public GeometryTopology {
public:
    /** Constructor of GeometryTopologyShell object
     */
    GeometryTopologyShell();

    /** Destructor of GeometryTopologyShell object */
    ~GeometryTopologyShell();

    /** Method that traverse GeometryTopologyShell data structure and return set of GeometryTopology object with particular type */
    void getDescendants(std::unordered_map<std::shared_ptr<GeometryTopology>, unsigned int>& list, GeometryTopology::Type type);

    /** Method to copy shell object but with the list of faces being reversed */
    std::shared_ptr<GeometryTopologyShell> reverseCopy();

    /** Method to check if the shell is created by a closed set of faces */
    bool isClosed();

    /** Method to add face on list of edges that build this wire */
    void addFace(std::shared_ptr<GeometryTopologyFace> face_ptr, unsigned int ccw_wire_idx);
private:
    /** Attribute to store list of faces that build this shell */
    std::vector<std::tuple<std::shared_ptr<GeometryTopologyFace>, unsigned int>> _faces;
};

#endif