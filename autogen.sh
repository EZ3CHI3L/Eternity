#!/bin/sh -e

echo '<3'
(
libtoolize
aclocal -I m4
autoconf
autoheader
automake --add-missing --copy --no-force
)
