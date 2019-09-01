# Copyright (c) 2019 Tom Hancocks, The Diamond Project
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

TEST-SOURCES := $(shell find tests -name "*.c")
TEST-OBJECTS := $(TEST-SOURCES:%.c=%-test.o)

LIB-SOURCES := $(shell find cpu -name "*.c")
LIB-OBJECTS := $(LIB-SOURCES:%.c=%-lib.o)

.PHONY: run-all-tests
run-all-tests: lib68-test-target
	./lib68-test-target

.PHONY: clean
clean:
	-rm -v $(TEST-OBJECTS) $(LIB-OBJECTS) lib68.a libUnit/unit.o
	-make -C libUnit clean

# Test Target Related

lib68-test-target: $(TEST-OBJECTS) libUnit/unit.o lib68.a
	$(CC) -DUNIT_TEST -I./ -o $@ $^

%-test.o: %.c
	$(CC) -DUNIT_TEST -c -o $@ -I./ $<

libUnit/unit.o: libUnit/unit.c
	$(CC) -DUNIT_TEST -c -o $@ $^

# Library Related

lib68.a: $(LIB-OBJECTS)
	$(AR) -cr $@ $^

%-lib.o: %.c
	$(CC) -c -o $@ -I./ $<