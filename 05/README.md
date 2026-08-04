For module 05 I (re)learned how the heap works/how to use it and valgrind. Exercises were mainly
about intentionally writing bugs then fixing them after running Valgind, but I also revamped
module 03's little stats tool to use dynamically allocated memory instead of a fixed size
array. The capstone for this module is a dynamic vector of doubles. In addition to the basic ops
I also implemented `vec_insert()` and `vec_remove()` with the help of `memmove()`. Some of the
API details in there are a bit inconsistent (handling fail states, mainly), but I'm very happy
with it. The tests in `/vec/main.c` are also a bit shoddy but I'm very confident it works.
