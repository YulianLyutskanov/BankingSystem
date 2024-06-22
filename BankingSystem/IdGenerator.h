#pragma once
class IdGenerator
{
  public:
    unsigned getUniqueId();
    void setStartingId(unsigned newStarting);

    static IdGenerator &getInstance();
    IdGenerator(const IdGenerator &other) = delete;
    IdGenerator &operator=(const IdGenerator &other) = delete;

  private:
    unsigned curId = 100;
    IdGenerator() = default;
};
