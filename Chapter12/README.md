# 12: Class Design

- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Drill 1](drill/01)
Deﬁne a class `B1` with a virtual function `vf()` and a non-virtual function `f()`. Deﬁne both of these functions within class `B1`. Implement each function to output its name (e.g., `B1::vf()`). Make the functions `public`. Make a `B1` object and call each function.

## [Drill 2](drill/02)
Derive a class `D1` from `B1` and override `vf()`. Make a `D1` object and call `vf()` and `f()` for it.

## [Drill 3](drill/03)
Deﬁne a reference to `B1` (a `B1&`) and initialize that to the `D1` object you just deﬁned. Call `vf()` and `f()` for that reference.

## [Drill 4](drill/04)
Now deﬁne a function called `f()` for `D1` and repeat 1–3. Explain the results.

## [Drill 5](drill/05)
Add a pure virtual function called `pvf()` to `B1` and try to repeat 1–4. Explain the result.

## [Drill 6](drill/06)
Deﬁne a class `D2` derived from `D1` and override `pvf()` in `D2`. Make an object of class `D2` and invoke `f()`, `vf()`, and `pvf()` for it.

## [Drill 7](drill/07)
Deﬁne a class `B2` with a pure virtual function `pvf()`. Deﬁne a class `D21` with a `string` data member and a member function that overrides `pvf()`; `D21::pvf()` should output the value of the `string`. Deﬁne a class `D22` that is just like `D21` except that its data member is an `int`. Deﬁne a function `f()` that takes a `B2&` argument and calls `pvf()` for its argument. Call `f()` with a `D21` and a `D22`.
