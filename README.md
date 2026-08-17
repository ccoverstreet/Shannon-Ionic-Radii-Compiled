# Compiled Shannon Ionic Radii

This repository contains a parsing script for generating a CSV version of the Shannon Ionic Radii website hosted by the Atomistic Simulation Group in the Materials Department of Imperial College. This repository contains a saved version of the site.

## CLI

A CLI for the database is included in `shannonradiicli.py`. This script can be run with provided elements and arguments to quickly filter and sort results

Example usage:
```
    shannonradiicli.py Ho Dy Tm Tb Sm Pr --coord VIII --sort r_ionic --charge 3
```
