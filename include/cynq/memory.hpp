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

#include "cynq/enums.hpp"
#include "cynq/status.hpp"

namespace cynq {
/**
 * @brief Interface for standardising the API of Memory devices:
 * - no inheritors -
 *
 */
class IMemory {
 public:
  /**
   * @brief ~IMemory destructor method
   * Destroy the IMemory object.
   */
  virtual ~IMemory() = default;
  /**
   * @brief Type
   * Type of runtime supported by the IMemory.
   *
   */
  enum Type { None = 0, XRT };
  /**
   * @brief Sync method
   * Synchronizes the memory in terms of transactions.
   *
   * @param type The orientation of the Synchronizaton this can be host to host
   * to device (HostToDevice) or device to host (DeviceToHost).
   *
   * @return Status
   */
  virtual Status Sync(const SyncType type) = 0;
  /**
   * @brief Size method
   * Gives the value for the memory size in bytes.
   *
   * @return size_t
   */
  virtual size_t Size() = 0;
  /**
   * @brief Create method
   * Factory method to create specific subclasses of IMemory.
   *
   * @example
   * - no implementations -
   *
   * @param impl
   * Used for establishin if the object is dependent on a runtime, use None if
   * this is not the case.
   *
   * @param size
   * Size in bytes of the memory, this defines the length of the address space
   * of the transaction being mapped.
   *
   * @param hostptr
   * Pointer of the address that belongs to the host, used for memory mapping
   * from the host to the device.
   *
   * @param devptr
   * Pointer of the address that belongs to the device, used for mapping memory
   * to the device.
   *
   * @return std::shared_ptr<IMemory>
   */
  static std::shared_ptr<IMemory> Create(IMemory::Type impl,
                                         const std::size_t size,
                                         uint8_t* hostptr, uint8_t* devptr);

 protected:
  /**
   * @brief GetHostAddress method
   * Get the Address that belongs to the host.
   * [Reference] shared memory pointer with reference counting.
   *
   * @return std::shared_ptr<uint8_t>
   */
  virtual std::shared_ptr<uint8_t> GetHostAddress() = 0;
  /**
   * @brief GetDeviceAddress method
   * Get the Address that belongs to the device.
   * [Reference] shared memory pointer with reference counting.
   *
   * @return std::shared_ptr<uint8_t>
   */
  virtual std::shared_ptr<uint8_t> GetDeviceAddress() = 0;
};
}  // namespace cynq
