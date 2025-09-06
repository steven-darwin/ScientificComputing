/**
 * @file InputXDMFAdapter.cpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-07-28
 * @date Last Modified : 2025-08-30
 *
 * @brief [Implementation] Input adapter to XDMF library
 */

#include <memory>

#include "geometry-topology/GeometryTopology.hpp"
#include "input-output/InputXDMFAdapter.hpp"
#include "input-output/InputHDF5Adapter.hpp"

InputXDMFAdapter::InputXDMFAdapter(const char* xdmf_file_path, const char* hdf5_file_path) {
    _xdmfFilePath = xdmf_file_path;
    _hdf5FilePath = hdf5_file_path;
}

InputXDMFAdapter::~InputXDMFAdapter() {
    // TBA
}

std::shared_ptr<GeometryTopology> InputXDMFAdapter::deserialize() {
    InputHDF5Adapter hdf5Adapter = InputHDF5Adapter(_hdf5FilePath);
    return hdf5Adapter.deserialize();
}