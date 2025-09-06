/**
 * @file OutputAbsractAdapter.hpp
 * @author Steven Darwin
 * @version 0.0.1
 * @date Created : 2025-08-20
 * @date Last Modified : 2025-08-30
 *
 * @brief [Header] Abstract class for output adapter
 */

#ifndef IO_OUTPUT_ADAPTER_HPP
#define IO_OUTPUT_ADAPTER_HPP

#include <memory>

#include "input-output/InputOutputAdapter.hpp"
#include "geometry-topology/GeometryTopology.hpp"

class OutputAdapter : public InputOutputAdapter {
public:
    /** Constructor of OutputAdapter object
     */
    OutputAdapter();

    /** Destructor of OutputAdapter object */
    ~OutputAdapter();

    /** Method to serialize internal neutral data structure to file's data */
    virtual void serialize(std::shared_ptr<GeometryTopology>) = 0;
private:

};

#endif