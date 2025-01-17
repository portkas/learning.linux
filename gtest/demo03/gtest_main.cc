#include <cstdio>
#include "gtest/gtest.h"

#if defined(GTEST_OS_ESP8266) || defined(GTEST_OS_ESP32) || \
    (defined(GTEST_OS_NRF52) && defined(ARDUINO))

#ifdef GTEST_OS_ESP8266
extern "C" {
#endif

void setup() { testing::InitGoogleTest(); }
void loop() { RUN_ALL_TESTS(); }


#ifdef GTEST_OS_ESP8266
}
#endif

#elif defined(GTEST_OS_QURT)

GTEST_API_ int main() {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
#else

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
