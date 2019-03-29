#pragma once

#include <string>
#include <memory>

struct Command {
  Command(time_t nTimestamp, const std::string& sBody)
    : nTimestamp(nTimestamp), sBody(sBody)
  {}
  Command(Command const& other) = default;
  Command(Command&& other) = default;

  bool isOpenScopeCommand()  const { return sBody == "{"; }
  bool isCloseScopeCommand() const { return sBody == "}"; }

  time_t      nTimestamp;
  std::string sBody;
};


class ICommandSubscriber
{
public:
  virtual ~ICommandSubscriber() = default;

  virtual void handle(Command const& command) = 0;
  virtual void relax() = 0;
};

using ICommandSubscriberPtr     = std::shared_ptr<ICommandSubscriber>;
using ICommandSubscriberWeakPtr = std::weak_ptr<ICommandSubscriber>;


class ICommandPublisher
{
public:
  virtual ~ICommandPublisher() = default;

  virtual void addSubscriber(ICommandSubscriberWeakPtr pSubscriber) = 0;
};

using ICommandPublisherPtr      = std::shared_ptr<ICommandPublisher>;
using ICommandPublisherWeakPtr  = std::weak_ptr<ICommandPublisher>;
