#!/bin/sh -e

echo 'It's verbose don't be afraid.'
(
libtoolize -v
aclocal -I m4
autoconf -v
autoheader -v
automake --add-missing --copy --no-force -v
)
