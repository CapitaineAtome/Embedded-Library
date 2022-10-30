"""
This file should be at the base of the project.
"""

import os
import subprocess

base_path = os.getcwd()
sphinx_path = base_path+'/docs/sphinx'


def run_doxygen(only_xml=True):
    """
    Function that run doxygen.
    Doxygen will parse the c++ files for breathe to use them.
    :return: None
    """

    os.chdir(base_path)

    subprocess.run(['doxygen', 'config'])

    if only_xml:
        print("Deleting docs/html and docs/latex keeping only docs/xml")
        subprocess.run(['rm', '-rf', 'docs/html', 'docs/latex'])

    os.chdir(base_path)


def run_sphinx():
    """
    Function that run sphinx.
    Sphinx will create the documentation using the .rst files provided.
    :return: None
    """

    os.chdir(sphinx_path)

    subprocess.run(['make', 'html'])

    os.chdir(base_path)


if __name__ == '__main__':
    run_doxygen(only_xml=False)
    run_sphinx()
