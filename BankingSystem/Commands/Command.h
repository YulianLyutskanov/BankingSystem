#pragma once

class Command
{
  public:
    Command() = default;
    virtual void execute() = 0;
    virtual void cancel() = 0;
    virtual void view() const = 0;
    virtual void details() const = 0;
    virtual Command *clone() const = 0;
    virtual ~Command() = default;
};
