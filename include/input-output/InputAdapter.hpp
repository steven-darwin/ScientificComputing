/**
 * @file InputAdapter.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-20
 * @date Last Modified : 2025-08-23
 *
 * @brief [Header] Abstract class for input adapter
 */

#ifndef IO_INPUT_ADAPTER_HPP
#define IO_INPUT_ADAPTER_HPP

#include <memory>

#include "input-output/InputOutputAdapter.hpp"
#include "geometry-topology/GeometryTopology.hpp"

class InputAdapter : public InputOutputAdapter {
public:
    /** Constructor of InputAdapter object
     */
    InputAdapter();

    /** Destructor of Inputdapter object */
    ~InputAdapter();

    /** Method to deserialize file's data to internal neutral data structure */
    virtual std::shared_ptr<GeometryTopology> deserialize() = 0;

private:

};

#endif