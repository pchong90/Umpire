#ifndef UMPIRE_MemorySpaceRegistry_HPP
#define UMPIRE_MemorySpaceRegistry_HPP

#include "umpire/space/MemorySpaceFactory.hpp"

#include <vector>
#include <string>
#include <memory>

namespace umpire {
namespace space {

class MemorySpaceRegistry {
  public:
    static MemorySpaceRegistry& getInstance();

    void registerMemorySpaceFactory(const std::string& name,
        std::shared_ptr<MemorySpaceFactory> factory);

    std::vector<std::string> getMemorySpaceFactoryNames();

    std::shared_ptr<MemorySpaceFactory> getMemorySpaceFactory(const
        std::string& name);

  protected:
    MemorySpaceRegistry();

  private:
    void buildRegistry();

    static MemorySpaceRegistry* s_memory_space_registry_instance;

    std::map<std::string, std::shared_ptr<MemorySpaceFactory>> m_space_factories;
    std::vector<std::string> m_space_factory_names;
};

} // end of namespace space
} // end of namespace umpire

#endif // UMPIRE_MemorySpaceRegistry_HPP