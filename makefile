# NESLA
# Copyright (C) 2022 David Jolly
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
# AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

DIR_SRC=src/

FLAGS=-march=native\ -mtune=native\ -std=c11\ -Wall\ -Werror
FLAGS_DEBUG=FLAGS=$(FLAGS)\ -g
FLAGS_RELEASE=FLAGS=$(FLAGS)\ -O3\ -flto
FLAGS_MAKE=--no-print-directory -C

MAX_PARALLEL=8

.PHONY: all
all: release

.PHONY: analyze
analyze:
	@cloc .
	@cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem .

.PHONY: debug
debug:
	@make $(FLAGS_MAKE) $(DIR_SRC) build -j${MAX_PARALLEL} $(FLAGS_DEBUG)

.PHONY: release
release:
	@make $(FLAGS_MAKE) $(DIR_SRC) build -j${MAX_PARALLEL} $(FLAGS_RELEASE)
	@make $(FLAGS_MAKE) $(DIR_SRC) strip

.PHONY: clean
clean:
	@make $(FLAGS_MAKE) $(DIR_SRC) clean
