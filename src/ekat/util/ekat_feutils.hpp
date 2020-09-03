#ifndef EKAT_FEUTILS_HPP
#define EKAT_FEUTILS_HPP

#include "ekat/ekat.hpp"

#include <cfenv>

#ifndef EKAT_HAVE_FEENABLEEXCEPT

namespace ekat {

#ifdef APPLE

inline int
fegetexcept (void)
{
  static fenv_t fenv;

  return fegetenv (&fenv) ? -1 : (fenv.__control & FE_ALL_EXCEPT);
}

inline int
feenableexcept (int excepts)
{
  static fenv_t fenv;
  int new_excepts = excepts & FE_ALL_EXCEPT,
               old_excepts;  // previous masks

  if ( fegetenv (&fenv) ) return -1;
  old_excepts = fenv.__control & FE_ALL_EXCEPT;

  // unmask
  fenv.__control &= ~new_excepts;
  fenv.__mxcsr   &= ~(new_excepts << 7);

  return ( fesetenv (&fenv) ? -1 : old_excepts );
}

inline int
fedisableexcept (int excepts)
{
  static fenv_t fenv;
  int new_excepts = excepts & FE_ALL_EXCEPT,
               old_excepts;  // all previous masks

  if ( fegetenv (&fenv) ) return -1;
  old_excepts = fenv.__control & FE_ALL_EXCEPT;

  // mask
  fenv.__control |= new_excepts;
  fenv.__mxcsr   |= new_excepts << 7;

  return ( fesetenv (&fenv) ? -1 : old_excepts );
}

#else // unsupported machine.

inline int
fegetexcept (void)
{
  fprintf(stderr, "fegetexcept: unsupported environment (no effect)\n");
  return 0;
}

inline int
feenableexcept (int excepts)
{
  fprintf(stderr, "feenableexcept: unsupported environment (no effect)\n");
}

inline int
fedisableexcept (int excepts)
{
  fprintf(stderr, "fedisableexcept: unsupported environment (no effect)\n");
}

#endif

} // namespace ekat
#endif // EKAT_NEEDS_FEENABLEEXCEPT

#endif // EKAT_FEUTILS_HPP
