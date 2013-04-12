

BackOffTrigramModel

Author: L. Amber Wilcox-O'Hearn

Contact: amber@cs.toronto.edu

Released under the GNU AFFERO GENERAL PUBLIC LICENSE, see COPYING file for details.

============
Introduction
============
Functionality in Brief:

BackOffTrigramModel reads an arpa format trigram model and calculates trigram
probabilities according to the standard Katz back-off method.  The values are
stored in a Judy tree, and made available through a Python interface.  

============
Dependencies
============
BackOffTrigramModel requires:

A C compiler, Python, make, Judy Trees library (http://judy.sourceforge.net/)

It was tested under the following versions:

* Judy Trees  1.0.5
* Ubuntu 12.04.2 LTS
* Python 2.7.3
* GNU make 3.81

========
Building
========
run
::

 $ make

=================
Running the tests
=================
run
::

 $ make test

==========
Installing
==========
run
::

 $ make install

This will copy the ``BackOffTrigramModelPipe`` executable into $prefix/bin
and will execute ``python setup.py install``, which will result in the
BackOffTrigramModel Python module being copied into the appropriate place in
your Python installation.
