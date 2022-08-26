#include "ekat/ekat_session.hpp"

/*
 * This small file contains the default implementation of a test session
 * initialization/finalization. These implementation simply call the
 * correspondinf ekat session intialization/finalization, but it also
 * enables some "default" fpes in EKAT
 *
 * If your application needs to perform additional initialization or finalization
 * work, you MUST define these functions in a cpp file. Your implementation should
 * likely call EKAT's session initialization/finalization, but are allowed to do
 * additional work.
 * When calling EkatCreateUnitTest, you must specify the option EXCLUDE_TEST_SESSION,
 * which will prevent Ekat from linking in this file (avoiding multiple definition
 * of these routines).
 */

static int get_default_fpes () {
#ifdef EKAT_ENABLE_DEFAULT_FPE
  return (FE_DIVBYZERO |
          FE_INVALID   |
          FE_OVERFLOW);
#else
  return 0;
#endif
}

void ekat_initialize_test_session (int argc, char** argv, const bool print_config) {
  ekat::initialize_ekat_session (argc,argv,print_config);
#ifdef EKAT_ENABLE_FPE_SUPPORT
  ekat::enable_fpes(get_default_fpes());
#endif
}

void ekat_finalize_test_session () {
  ekat::finalize_ekat_session ();
}
