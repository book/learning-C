#!/bin/sh

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINUX_KERNEL_INDENT_PARAMS="-npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1"

BOOK_PARAMS="--ignore-profile \
 --k-and-r-style \
 --indent-level4 \
 --no-tabs \
 --leave-optional-blank-lines \
 --dont-format-comments \
 --line-length80"

COMMON_CLIB_TYPES="-T FILE -T size_t -T ssize_t \
 -T int8_t -T int16_t -T int32_t -T int64_t \
 -T uint8_t -T uint16_t -T uint32_t -T uint64_t"

indent $BOOK_PARAMS $COMMON_CLIB_TYPES "$@"
