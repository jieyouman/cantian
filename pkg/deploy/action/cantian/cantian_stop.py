#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Perform hot backups of CantianDB100 databases.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
import sys
from cantian_uninstall import CanTian

if __name__ == "__main__":
    Func = CanTian()
    try:
        Func.cantian_stop()
    except ValueError as err:
        exit(str(err))
    except Exception as err:
        exit(str(err))
    exit(0)
