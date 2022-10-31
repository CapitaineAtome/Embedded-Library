# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html
import os
import sys

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Embedded-Library'
copyright = '2022, CapitaineAtome'
author = 'CapitaineAtome'
release = '0.1'

# -- Configuration for Breathe -----------------------------------------------
# https://breathe.readthedocs.io/en/latest/quickstart.html

doc_path = '/'.join(os.getcwd().split('/')[:-2])
sys.path.append(doc_path+'/breathe')

breathe_projects = {"Embedded-Library": doc_path+'/xml'}

breathe_default_project = "Embedded-Library"



# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx.ext.autodoc',
              'sphinx.ext.imgmath',
              'sphinx.ext.todo',
              'breathe']

templates_path = ['_templates']
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
