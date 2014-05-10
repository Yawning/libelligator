CXXFLAGS := -O2 -g -Wall -Werror -Wextra -fPIC -I./src
LDFLAGS := -shared -Wl,-soname,$(SONAME)
TEST_LDFLAGS := -L. -lelligator -lgtest -lgtest_main

SONAME = libelligator.so
SRCS = src/elligator/elligator.cc \
			 src/elligator/fe/crypto_verify_32.cc \
			 src/elligator/fe/fe_add.cc \
			 src/elligator/fe/fe_copy.cc \
			 src/elligator/fe/fe_cmov.cc \
			 src/elligator/fe/fe_frombytes.cc \
			 src/elligator/fe/fe_invert.cc \
			 src/elligator/fe/fe_isnonzero.cc \
			 src/elligator/fe/fe_mul.cc \
			 src/elligator/fe/fe_neg.cc \
			 src/elligator/fe/fe_sq.cc \
			 src/elligator/fe/fe_sq2.cc \
			 src/elligator/fe/fe_sub.cc \
			 src/elligator/fe/fe_tobytes.cc \
			 src/elligator/ge/ge_madd.cc \
			 src/elligator/ge/ge_p1p1_to_p2.cc \
			 src/elligator/ge/ge_p1p1_to_p3.cc \
			 src/elligator/ge/ge_p2_dbl.cc \
			 src/elligator/ge/ge_p3_0.cc \
			 src/elligator/ge/ge_p3_dbl.cc \
			 src/elligator/ge/ge_p3_to_p2.cc \
			 src/elligator/ge/ge_precomp_0.cc \
			 src/elligator/ge/ge_scalarmult_base.cc

TESTNAME = libelligator_test
TEST_SRCS = src/tests/kat.cc

OBJS = $(SRCS:.cc=.o)
TEST_OBJS = $(TEST_SRCS:.cc=.o)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONE: all clean

all: $(SONAME)

test: $(SONAME) $(TESTNAME)

$(SONAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(SONAME)

$(TESTNAME): $(SONAME) $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) $(TEST_LDFLAGS) -o $(TESTNAME)

clean:
	rm -f $(OBJS) $(SONAME) $(TEST_OBJS) $(TESTNAME)
