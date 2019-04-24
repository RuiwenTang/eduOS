#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
import shutil

if __name__ == "__main__":
    shutil.copyfile(sys.argv[1], sys.argv[2])