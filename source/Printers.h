#pragma once
#include <iostream>
#include <fstream>
#include <memory>

#include "Interfaces.h"

class DefaultPrinter : public ICommandSubscriber
{
public:

  // overrides from ICommandSubscriber
  void handle(const Command &command) override
  {
    std::cout << (m_nCounter ? ", " : "bulk: ");
    m_nCounter++;
    std::cout << command.sBody;
  }

  void relax() override
  {
    m_nCounter = 0;
    std::cout << std::endl;
  }

private:
  size_t m_nCounter = 0;
};


class FilePrinter : public ICommandSubscriber
{
public:

  // overrides from ICommandSubscriber
  void handle(const Command &command) override
  {
    if (!m_nCounter) {
      m_File.open("bulk" + std::to_string(command.nTimestamp) + ".log");
    }
    m_nCounter++;
    m_File << command.sBody << std::endl;
  }

  void relax() override
  {
    m_nCounter = 0;
    m_File.close();
  }

private:
  size_t        m_nCounter = 0;
  std::ofstream m_File;
};

using DefaultPrinterPtr = std::shared_ptr<DefaultPrinter>;
using FilePrinterPtr    = std::shared_ptr<FilePrinter>;
