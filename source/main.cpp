#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <memory>
#include "Interfaces.h"
#include "WeakPointersList.h"
#include "Printers.h"

class BasePublisher : public ICommandPublisher
{
public:
  virtual ~BasePublisher() = default;

  void addSubscriber(ICommandSubscriberWeakPtr pSubscriber)
  {
    m_Consumers.push_back(pSubscriber);
  }

protected:

  void passCommand(Command const& command) {
    m_Consumers.forEach(
      [&command](ICommandSubscriberPtr pSubscriber)
      {
        pSubscriber->handle(command);
      }
    );
  }

  void notifyRelax() {
    m_Consumers.forEach([](ICommandSubscriberPtr pSubscriber) {
      pSubscriber->relax();
    });
  }

private:
  WeakPointersList<ICommandSubscriber> m_Consumers;
};


class CommandInput : public BasePublisher
{
public:
  void run()
  {
    std::string sCommandBody;
    while (std::getline(std::cin, sCommandBody))
    {
      if (!sCommandBody.empty())
        passCommand(Command(std::time(nullptr), sCommandBody));
    }
    notifyRelax();
  }
};

using CommandInputPtr = std::shared_ptr<CommandInput>;


class Accumulator :
    public ICommandSubscriber,
    public BasePublisher
{
public:
  Accumulator(size_t nBulkSize) : m_nBulkSize(nBulkSize), m_nScopeLevel(0)
  {
    m_Commands.reserve(m_nBulkSize);
  }

  void handle(const Command& command) override
  {
    if (command.isOpenScopeCommand()) {
      if (!m_nScopeLevel)
        flushAccumulatedCommands();
      ++m_nScopeLevel;
    } else if(command.isCloseScopeCommand() && m_nScopeLevel) {
      --m_nScopeLevel;
      if (!m_nScopeLevel)
        flushAccumulatedCommands();
    } else {
      m_Commands.push_back(command);
      if (!m_nScopeLevel && m_Commands.size() == m_nBulkSize)
        flushAccumulatedCommands();
    }
  }

  void relax() override
  {
    if (!m_nScopeLevel)
      flushAccumulatedCommands();
  }

private:
  // pass all accumulated command to consumers
  void flushAccumulatedCommands() {
    for (const Command& command: m_Commands)
      passCommand(command);
    notifyRelax();
    m_Commands.clear();
  }

private:
  size_t               m_nBulkSize   = 3;
  std::vector<Command> m_Commands;
  size_t               m_nScopeLevel = 0;
};

using AccumulatorPtr = std::shared_ptr<Accumulator>;


int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "Usage:\n  " << argv[0] << " <BulkSize>" << std::endl;
    return 1;
  }

  size_t nBulkSize = size_t(atoi(argv[1]));
  if (nBulkSize == 0)
    return 1;

  CommandInputPtr   pReader         = std::make_shared<CommandInput>();
  AccumulatorPtr    pAccumulator    = std::make_shared<Accumulator>(nBulkSize);
  DefaultPrinterPtr pDefaultPrinter = std::make_shared<DefaultPrinter>();
  FilePrinterPtr    pFileWriter     = std::make_shared<FilePrinter>();

  pReader->addSubscriber(pAccumulator);
  pAccumulator->addSubscriber(pDefaultPrinter);
  pAccumulator->addSubscriber(pFileWriter);

  pReader->run();
  return 0;
}
