/**
 * @file noncopyable.h
 * @author Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
 * @brief Base class for classes that are not used much that we don't want to copy or reassign
 * @version 1.0
 * @date 2023-05-06
 * 
 * @copyright https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-copyable_Mixin
 * 
 */
#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

/**
 * @brief Base class for classes that are not used much that we don't want to copy or reassign
 * 
 */
class NonCopyable
{
  public: 
    NonCopyable (const NonCopyable &) = delete;
    NonCopyable & operator = (const NonCopyable &) = delete;

  protected:
    NonCopyable () = default;
    ~NonCopyable () = default; /// Protected non-virtual destructor
};
/**
 * @brief Base class for classes that are not used much that we don't want to copy or reassign
 * 
 */
class CantCopy : private NonCopyable
{};

#endif // NONCOPYABLE_H