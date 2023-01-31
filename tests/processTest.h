#include <gtest/gtest.h>
#include <gmock/gmock.h> // Brings in gMock.

#include "process_manager.h"
#include <memory>
using ::testing::Return;

// mocking
class processMock: public wgm_processes::process_manager {
public:
MOCK_METHOD( void, start_process, (), (override));
MOCK_METHOD( void, stop_process, (), (override));
MOCK_METHOD( void, start_process, (Iprocess_manager* process), (override));
MOCK_METHOD( void, stop_process, (Iprocess_manager* process), (override));
MOCK_METHOD( void, start_all, (), (override));
MOCK_METHOD( void, stop_all, (), (override));



};

// Demonstrate some basic mocking.
TEST(cntLinearMotionMock, connectSuccess) {
  processMock mock_obj;

}
// Demonstrate some basic assertions.
TEST(whsLinearMotionPtr, deletePtr) {
  // expect connect
 std::unique_ptr< Iaxis_motion> moverPtr = std::make_unique< linear_motion>();
   moverPtr.reset();
  EXPECT_EQ(moverPtr, nullptr);
}