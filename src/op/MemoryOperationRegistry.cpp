#include "umpire/op/MemoryOperationRegistry.hpp"

#include "umpire/op/CudaCopyFromOperation.hpp"
#include "umpire/op/CudaCopyToOperation.hpp"
#include "umpire/op/HostCopyOperation.hpp"

namespace umpire {
namespace op {

MemoryOperationRegistry*
MemoryOperationRegistry::s_memory_operation_registry_instance = nullptr;

MemoryOperationRegistry&
MemoryOperationRegistry::getInstance()
{
  if (!s_memory_operation_registry_instance) {
    s_memory_operation_registry_instance = new MemoryOperationRegistry();
  }

  return *s_memory_operation_registry_instance;
}

MemoryOperationRegistry::MemoryOperationRegistry()
{
  registerOperation(
      "COPY",
      std::make_pair(Platform::cpu, Platform::cpu),
      std::make_shared<HostCopyOperation>());

  registerOperation(
      "COPY",
      std::make_pair(Platform::cpu, Platform::cuda),
      std::make_shared<CudaCopyToOperation>());

  registerOperation(
      "COPY",
      std::make_pair(Platform::cuda, Platform::cpu),
      std::make_shared<CudaCopyToOperation>());
}

MemoryOperationRegistry::registerOperation(
    const std::string& name,
    std::pair<Platform, Platform> platforms,
    std::shared_ptr<MemoryOperation>&& operation)
{
  auto operations = m_operators.find(name);

  if (operations == m_operators.end()) {
    operations = m_operators.insert(
        std::make_pair(name,
          std::unordered_map<std::pair<Platform, Platform>,
          std::shared_ptr<MemoryOperation>>())).first;
  }

  operations->second.insert(std::make_pair(platforms, operation))
}

std::shared_ptr<umpire::op::MemoryOperation> find(
    const std::string& name,
    std::shared_ptr<AllocatorInterface>& source_allocator,
    std::shared_ptr<AllocatorInterface>& dst_allocator)
{
  auto platforms = std::make_pair(
      source_allocator->getPlatform(),
      dest_allocator->getPlatform());

  auto operations = m_operators.find(name);

  if (operations == m_operators.end()) {
    UMPIRE_ERROR("Cannot find operator " << name) << ", " << platforms.second());
  }

  auto op = operations.find(platforms);

  if (op == operations.end()) {
    UMPIRE_ERROR("Cannot find operator" << name << " for platforms " << platforms.first() << ", " << platforms.second());
  }

  return op;
}



} // end of namespace op
} // end of namespace umpire
