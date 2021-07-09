// umacro
#include <umacro.h>

// googletest
#include <gtest.h>

// system includes
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class StatFixture : public ::testing::Test
{
    protected:
    int rc = -99999;
    struct stat sb = {0};
    const char *real_file = "file.txt";
    const char *fake_file = "nonexistent.txt";

    bool caught_error = false;
    void catch_error(int rc, const char *msg) {
        caught_error = true;
    }

    void SetUp() {
        FILE *fp;
        fp = fopen(real_file, "w");
        fclose(fp);
    }

    void TearDown() {
        std::remove(real_file);
    }
};

TEST_F(StatFixture, TestCheckSyscallSuccess) {
    CHECK_SYSCALL(stat, rc, 0, catch_error, real_file, &sb);
    ASSERT_TRUE(rc == 0);
    ASSERT_FALSE(caught_error);
}

TEST_F(StatFixture, TestCheckSyscallFailure) {
    ASSERT_FALSE(caught_error);
    CHECK_SYSCALL(stat, rc, 0, catch_error, fake_file, &sb);
    // stat sets errno instead of properly returning an rcode
    ASSERT_TRUE(errno == 2);
    ASSERT_TRUE(rc == -1);
    ASSERT_TRUE(caught_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
