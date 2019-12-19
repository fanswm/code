#!/bin/python
# -*-coding: utf-8 -*-

import sys

def show_args():
	args = sys.argv
	for i in args:
		print "%s" %i

if __name__ == "__main__":
	show_args()
