/**
 * @file OutputXDMFAdapter.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-07-28
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Output adapter to XDMF library
 */

#include <memory>
#include <vector>
#include <iostream>

#include "hdf5.h"
#include "XdmfDomain.hpp"
#include "XdmfWriter.hpp"
#include "XdmfHDF5Controller.hpp"
#include "XdmfAttribute.hpp"
#include "XdmfUnstructuredGrid.hpp"
#include "XdmfArray.hpp"
#include "XdmfGeometry.hpp"
#include "XdmfTopology.hpp"

#include "geometry-topology/GeometryTopology.hpp"
#include "input-output/OutputHDF5Adapter.hpp"
#include "input-output/OutputXDMFAdapter.hpp"

OutputXDMFAdapter::OutputXDMFAdapter(const char* xdmf_file_path, const char* hdf5_file_path) {
    _xdmfFilePath = xdmf_file_path;
    _hdf5FilePath = hdf5_file_path;
}

OutputXDMFAdapter::~OutputXDMFAdapter() {
    // TBA
}

void OutputXDMFAdapter::serialize(std::shared_ptr<GeometryTopology> neutral_geometry_topology) {
    OutputHDF5Adapter hdf5Adapter = OutputHDF5Adapter(_hdf5FilePath);
    hdf5Adapter.serialize(neutral_geometry_topology);

    hid_t file = H5Fopen(_hdf5FilePath, H5F_ACC_RDONLY, H5P_DEFAULT);
    shared_ptr<XdmfDomain> domain = XdmfDomain::New();

    hid_t mesh_group = H5Gopen(file, "mesh", H5P_DEFAULT);
    shared_ptr<XdmfUnstructuredGrid> mesh_grid = XdmfUnstructuredGrid::New();
    mesh_grid->setName("Mesh");
    domain->insert(mesh_grid);
    
    mesh_grid->setGeometry(handleGeometry(mesh_group));
    mesh_grid->setTopology(handleWireTopology(mesh_group));
    mesh_grid->insert(handleShellTopology(mesh_group));
    
    H5Gclose(mesh_group);
    H5Fclose(file);

    shared_ptr<XdmfWriter> writer = XdmfWriter::New(_xdmfFilePath);
    writer->setMode(XdmfWriter::DistributedHeavyData);
    writer->setLightDataLimit(0);
    domain->accept(writer);
}

shared_ptr<XdmfGeometry> OutputXDMFAdapter::handleGeometry(hid_t parent_group) {
    hid_t geometry_dataset = H5Dopen(parent_group, "geometry", H5P_DEFAULT);
    shared_ptr<XdmfGeometry> geometry = XdmfGeometry::New();
    geometry->setName("Geometry");
    geometry->setType(XdmfGeometryType::XYZ());

    hid_t geometry_dataspace = H5Dget_space(geometry_dataset);
    hsize_t geometry_dataspace_dim[2];
    H5Sget_simple_extent_dims(geometry_dataspace, geometry_dataspace_dim, nullptr);

    std::vector<unsigned int> geometry_start{ 0, 0 };
    std::vector<unsigned int> geometry_stride{ 1, 1 };
    std::vector<unsigned int> geometry_dim{ static_cast<unsigned int>(geometry_dataspace_dim[0]), static_cast<unsigned int>(geometry_dataspace_dim[1]) };
    shared_ptr<XdmfHDF5Controller> geometry_data_controller = XdmfHDF5Controller::New(_hdf5FilePath, "/mesh/geometry", XdmfArrayType::Float64(), geometry_start, geometry_stride, geometry_dim, geometry_dim);

    geometry->setHeavyDataController(geometry_data_controller);
    geometry->release();

    H5Sclose(geometry_dataspace);
    H5Dclose(geometry_dataset);

    return geometry;
}

shared_ptr<XdmfTopology> OutputXDMFAdapter::handleWireTopology(hid_t parent_group) {
    hid_t wire_topology_dataset = H5Dopen(parent_group, "topology_wire", H5P_DEFAULT);
    shared_ptr<XdmfTopology> wire_topology = XdmfTopology::New();
    wire_topology->setName("Wire Topology");
    wire_topology->setType(XdmfTopologyType::Polyline(4));

    hid_t wire_topology_dataspace = H5Dget_space(wire_topology_dataset);
    hsize_t wire_topology_dataspace_dim[2];
    H5Sget_simple_extent_dims(wire_topology_dataspace, wire_topology_dataspace_dim, nullptr);

    std::vector<unsigned int> wire_topology_start{ 0, 0 };
    std::vector<unsigned int> wire_topology_stride{ 1, 1 };
    std::vector<unsigned int> wire_topology_dim{ static_cast<unsigned int>(wire_topology_dataspace_dim[0]), static_cast<unsigned int>(wire_topology_dataspace_dim[1]) };
    shared_ptr<XdmfHDF5Controller> wire_topology_data_controller = XdmfHDF5Controller::New(_hdf5FilePath, "/mesh/topology_wire", XdmfArrayType::UInt32(), wire_topology_start, wire_topology_stride, wire_topology_dim, wire_topology_dim);

    wire_topology->setHeavyDataController(wire_topology_data_controller);
    wire_topology->release();

    H5Sclose(wire_topology_dataspace);
    H5Dclose(wire_topology_dataset);

    return wire_topology;
}

shared_ptr<XdmfAttribute> OutputXDMFAdapter::handleShellTopology(hid_t parent_group) {
    hid_t shell_topology_dataset = H5Dopen(parent_group, "topology_shell", H5P_DEFAULT);
    shared_ptr<XdmfAttribute> shell_topology = XdmfAttribute::New();
    shell_topology->setName("Shell Topology");
    shell_topology->setType(XdmfAttributeType::Vector());
    shell_topology->setCenter(XdmfAttributeCenter::Cell());

    hid_t shell_topology_dataspace = H5Dget_space(shell_topology_dataset);
    hsize_t shell_topology_dataspace_dim[2];
    H5Sget_simple_extent_dims(shell_topology_dataspace, shell_topology_dataspace_dim, nullptr);

    std::vector<unsigned int> shell_topology_start{ 0, 0 };
    std::vector<unsigned int> shell_topology_stride{ 1, 1 };
    std::vector<unsigned int> shell_topology_dim{ static_cast<unsigned int>(shell_topology_dataspace_dim[0]), static_cast<unsigned int>(shell_topology_dataspace_dim[1]) };
    shared_ptr<XdmfHDF5Controller> shell_topology_data_controller = XdmfHDF5Controller::New(_hdf5FilePath, "/mesh/topology_shell", XdmfArrayType::UInt32(), shell_topology_start, shell_topology_stride, shell_topology_dim, shell_topology_dim);

    shell_topology->setHeavyDataController(shell_topology_data_controller);
    shell_topology->release();

    H5Sclose(shell_topology_dataspace);
    H5Dclose(shell_topology_dataset);

    return shell_topology;
}