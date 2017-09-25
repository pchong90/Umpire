#ifndef UMPIRE_AllocatorInterface_HPP
#define UMPIRE_AllocatorInterface_HPP

#include "umpire/util/Platform.hpp"

#include <memory>
#include <cstddef>


namespace umpire {

/*!
 * \brief Allocator provides a unified interface to all Umpire classes that can
 * be used to allocate and free data.
 */
class AllocatorInterface :
  public std::enable_shared_from_this<AllocatorInterface>
{
  public:
    /*!
     * \brief Allocate bytes of memory.
     *
     * \param bytes Number of bytes to allocate.
     *
     * \return Pointer to start of allocation.
     */
    virtual void* allocate(size_t bytes) = 0;

    /*!
     * \brief Free the memory at ptr.
     *
     * \param ptr Pointer to free.
     */
    virtual void deallocate(void* ptr) = 0;

    /*!
     * \brief Return number of bytes allocated for allocation
     *
     * \param ptr Pointer to allocation in question
     *
     * \return number of bytes allocated for ptr
     */
    virtual size_t size(void* ptr) = 0;

    virtual long getCurrentSize() = 0;
    virtual long getHighWatermark() = 0;

    virtual Platform getPlatform()  = 0;
};

} // end of namespace umpire

#endif // UMPIRE_AllocatorInterface_HPP
