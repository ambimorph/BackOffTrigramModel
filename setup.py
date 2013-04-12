# -*- coding: utf-8 -*-

# Copyright © 2009-2013 Amber and Zooko Wilcox-O'Hearn
#
# See README.rst for licensing information.

PKG='BackOffTrigramModel'

import os

import versioneer
versioneer.versionfile_source = os.path.join('src', 'Python', 'BackOffTrigramModel', '_version.py')
versioneer.versionfile_build = os.path.join('BackOffTrigramModel', '_version.py')
versioneer.tag_prefix = PKG+'-' # tags are like 1.2.0
versioneer.parentdir_prefix = versioneer.tag_prefix

from setuptools import setup

trove_classifiers=[
    "Environment :: Console",
    "License :: OSI Approved :: GNU Affero General Public License v3 or later (AGPLv3+)"
    "License :: DFSG approved",
    "Intended Audience :: Science/Research",
    "Natural Language :: English",
    "Programming Language :: C",
    "Programming Language :: Python",
    "Programming Language :: Python :: 2",
    "Programming Language :: Python :: 2.7",
    "Topic :: Software Development :: Libraries",
    "Topic :: Scientific/Engineering",
    "Topic :: Text Processing :: Linguistic",
    ]

readmetext = open('README.rst').read()
if readmetext[:3] == '\xef\xbb\xbf':
    # utf-8 "BOM" 
    readmetext = readmetext[3:]

try:
    readmetext = readmetext.decode('utf-8')
except UnicodeDecodeError:
    pass

def _setup(longdescription):
    setup(name=PKG,
          version=versioneer.get_version(),
          description='Python wrappers for a few algorithms from the Crypto++ library',
          long_description=longdescription,
          author='Zooko Wilcox-O\'Hearn',
          author_email='zooko@zooko.com',
          url='https://tahoe-lafs.org/trac/' + PKG,
          package_dir = {'': os.path.join('src', 'Python')},
          classifiers=trove_classifiers,
          test_suite="test",
          zip_safe=False, # I prefer unzipped for easier access.
          cmdclass=versioneer.get_cmdclass(),
          )

try:
    _setup(readmetext)
except UnicodeEncodeError:
    _setup(repr(readmetext))
