# Méthode Hongroise (Hungarian method)

An optimisation method for solving assignment problems.

## Context

Considering $n$ workers and $p$ tasks $(p \le n)$, we aim to find the best assignment of each workers to job, i.e such that the sum of the cost of all assignments is minimal. The costs of assignment of the workers to jobs are given in a matrix, with which we will process with the Hungarian method.

## Important note

The Hungarian method used here is an edited version by our Professor **RANDRIANARIVONY Arthur** during our class at University of Antananarivo. Great thanks to him for his devotion and passion for teaching math. He never stops optimizing inside optimization.

## How to run the code

Two options:

1. You have a C compiler:
```
# compile
gcc -o hongroise.exe hongroise.c

# launch it
./hongroise.exe
```
2. You can access the internet: go to an online C compiler like [https://www.programiz.com/c-programming/online-compiler/](https://www.programiz.com/c-programming/online-compiler/) and copy/paste the code inside the editor, then *Run* it.

The data (the matrix in which the rows represent the workers and the columns represent the tasks) is static for the moment. You can uncomment a given matrix (and if so, don't forget to comment or remove the other example) or write your own to see how the method works with different data. However, the case $n < p$ is not yet being handled for the moment.

## Resources for the Hungarian method

We are currently searching for the nearest correspoding article to this version of Hungarian method. Most of the resources such as videos on Youtube (e.g [https://youtu.be/lHvJV0bO4Cs?t=377](https://youtu.be/lHvJV0bO4Cs?t=377)) presented the method on examples which work for them. However, our Professor found out conter-examples on their version and then, proposed his version to us.

If you found the original article, please send the link or contact me at [hidekela.rajaovelona@univ-antananarivo.mg](mailto:hidekela.rajaovelona@univ-antananarivo.mg). Thank you.

## License

The C code provided here is without warranty of any kind, express or implied. In no event shall the author or copyright holder be liable for any claim, damages, or other liability.

## Author

Hidekela