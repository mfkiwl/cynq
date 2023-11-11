/*
 * See LICENSE for more information about licensing
 *
 * Copyright 2023
 * Author: Luis G. Leon-Vega <luis.leon@ieee.org>
 *         Diego Arturo Avila Torres <diego.avila@uned.cr>
 *
 */
#pragma once
#include <memory>

#include "cynq/datamover.hpp"
#include "cynq/enums.hpp"
#include "cynq/status.hpp"
#include "cynq/xrt/memory.hpp"

namespace cynq {
/**
 * @brief XRTDataMover class
 * Provides the api from which to interact with the data buffers responsable for
 * memory operations.
 *
 */
class XRTDataMover : public IDataMover {
 public:
  XRTDataMover() {}
  /**
   * @brief ~XRTDatamover destructor method
   * Destroy the XRTDatamover object.
   *
   */
  virtual ~XRTDataMover() = default;
  /**
   * @brief GetBuffer method
   * This method allocates a memory buffer. Depending on the MemoryType,
   * it allocates memory in a contiguous or memory region
   * (non-pageable) or non contiguous memory region depending on the Memory
   * typed past to the method. The memory can be mirrored with pageable memory
   * for its use in the host (or CPU).
   *
   * @param size Size in bytes of the buffer.
   *
   * @param type One of the values in the MemoryType enum class which can be one
   * of the following:
   * Dual (DIMM memory)
   * Cacheable (cache)
   * Host (Memory from the host)
   * Device (Memory from the device to be mapped)
   *
   * @return std::shared_ptr<XRTMemory>
   */
  std::shared_ptr<XRTMemory> GetBuffer(const size_t size,
                                       const MemoryType type) override;
  /**
   * @brief Upload method
   * This method moves the data from the host to the device using a DMA engine.
   * This triggers the AXI Memory Map and AXI Stream Transactions under the
   * hood.
   *
   * @param mem XRTMemory instance to upload.
   *
   * @param size Size in bytes of data being uploaded in the memory device by
   * making use of the buffer.
   *
   * @param exetype The execution type to use for the upload, this is either
   * sync (synchronous) or async (asynchronous) execution.
   *
   * @return Status
   */
  Status Upload(const std::shared_ptr<XRTMemory> mem, const size_t size,
                const ExecutionType exetype) override;
  /**
   * @brief Download method
   *
   * @param mem XRTMemory instance to download.
   *
   * @param size Size in bytes of data being downloaded from the memory device
   * by making use of the buffer.
   *
   * @param exetype The execution type to use for the download, this is either
   * sync (synchronous) or async (asynchronous) execution.
   *
   * @return Status
   */
  Status Download(const std::shared_ptr<XRTMemory> mem, const size_t size,
                  const ExecutionType exetype) override;
  /**
   * @brief Sync method
   * Synchronizes data movements in case of asynchronous Upload/Download.
   *
   * @return Status
   */
  Status Sync() override;
  /**
   * @brief GetStatus method
   * Returns the status of the data mover in terms of transactions.
   *
   * @return DeviceStatus
   */
  DeviceStatus GetStatus() override;
}
}  // namespace cynq
