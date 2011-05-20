# Copyright (C) 2011 Ron Huang
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.


import sys
import os
import string
import Image


def usage():
    print "python %s <folder containing framemarkers>" % (os.path.basename(sys.argv[0]))


def dump(fullname):
    basename = os.path.basename(fullname)

    im = Image.open(fullname)
    pix = im.load()

    print "    /* %s */" % (basename)
    patterns = []

    for i in range(9):
        patterns.append("0" if pix[2 + 2 * i, 1] == 2 else "1")
    for i in range(9):
        patterns.append("0" if pix[20, 2 + 2 * i] == 2 else "1")
    for i in range(9):
        patterns.append("0" if pix[3 + 2 * i, 20] == 2 else "1")
    for i in range(9):
        patterns.append("0" if pix[1, 3 + 2 * i] == 2 else "1")

    patterns.append("")

    print "   ", string.join(patterns, ",")


def main():
    if len(sys.argv) < 2:
        usage()
        return

    print """#ifndef __MARKERS__
#define __MARKERS__

byte markers[] = {"""

    folder = sys.argv[1]
    ld = os.listdir(folder)
    ld.sort()
    for basename in ld:
        fullname = os.path.join(folder, basename)
        dump(fullname)

    print """    /* end */
    0
};

#endif /* __MARKERS__ */"""


def main2():
    for i in range(9):
        print i


if __name__ == '__main__':
    main()
