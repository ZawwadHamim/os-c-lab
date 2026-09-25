# JavaScript Array Methods — forEach, map, filter, find, includes, some, every, reduce, sort, chaining

## Prerequisite: what is a "callback function"?

Every method in this note takes a **function as an argument**. That's called a **callback** — "call this function back, once for every item, and tell me what you did."

```js
const nums = [1, 2, 3];
nums.forEach(function (n) {
  console.log(n);
});
```

Read this as: "for each item in `nums`, run this little function, and inside it, call the current item `n`." You never call the function yourself — the array method calls it *for* you, automatically, once per element. This is the one idea that unlocks all ten methods below: they're all really the same shape — "loop through the array, run my function on each item" — they just differ in *what they do with the function's answer*.

All examples below run on this array unless stated otherwise:
```js
const nums = [1, 2, 3, 4, 5];
```

---

## 1. `forEach` — just run something for each item, keep nothing

```js
nums.forEach(function (n) {
  console.log(n * 2);
});
```
Output:
```
2
4
6
8
10
```
`forEach` doesn't build a new array or give anything back (it returns `undefined`) — it's for side effects only, like printing, or saving each item somewhere else. If you find yourself trying to "collect" a result from `forEach`, you want `map` instead.

## 2. `map` — transform every item, get a new array back

```js
const doubled = nums.map(function (n) {
  return n * 2;
});
console.log(doubled);
```
Output:
```
[ 2, 4, 6, 8, 10 ]
```
Key difference from `forEach`: your callback **returns** a value, and `map` collects all those returned values into a brand-new array — same length as the original, one output per input. The original `nums` is untouched.

## 3. `filter` — keep only items that pass a test

```js
const evens = nums.filter(function (n) {
  return n % 2 === 0;
});
console.log(evens);
```
Output:
```
[ 2, 4 ]
```
Your callback returns `true` or `false` for each item (this kind of true/false-returning function is called a **predicate**). `filter` keeps the items where it was `true`, throws away the rest, and gives you a new (possibly shorter) array.

## 4. `find` — get the first item that passes a test

```js
const firstBig = nums.find(function (n) {
  return n > 3;
});
console.log(firstBig);
```
Output:
```
4
```
Same idea as `filter`, but `find` stops at the **first match** and gives you that one item directly — not an array. If nothing matches, it gives you `undefined`.

## 5. `includes` — does this exact value exist in the array?

```js
console.log(nums.includes(3));
console.log(nums.includes(10));
```
Output:
```
true
false
```
No callback needed — just give it a value to look for. Returns a plain `true`/`false`. Use this when you just need a yes/no answer, not the item itself (that's what `find` is for).

## 6. `some` — is there AT LEAST ONE item that passes?

```js
console.log(nums.some(function (n) { return n > 4; }));
console.log(nums.some(function (n) { return n > 10; }));
```
Output:
```
true
false
```
Stops as soon as it finds one match and returns `true`. If it checks everything and finds nothing, returns `false`.

## 7. `every` — do ALL items pass?

```js
console.log(nums.every(function (n) { return n > 0; }));
console.log(nums.every(function (n) { return n > 2; }));
```
Output:
```
true
false
```
Stops as soon as it finds one item that **fails** and returns `false` immediately. Only returns `true` if every single item passed.

**`some` vs `every`, side by side:** `some` = "at least one," `every` = "all of them." Both give back a plain `true`/`false`, never an array.

## 8. `reduce` — combine the whole array into one single value

This is the one beginners find hardest, so slow down here.

```js
const total = nums.reduce(function (acc, n) {
  return acc + n;
}, 0);
console.log(total);
```
Output:
```
15
```
`reduce` takes **two** arguments: the callback, and a starting value (`0` here). The callback itself takes two things: `acc` (short for "accumulator" — the running total so far) and `n` (the current item). Walking through it by hand:

| Step | `acc` coming in | `n` | `acc + n` (becomes new `acc`) |
|---|---|---|---|
| 1 | 0 (the starting value) | 1 | 1 |
| 2 | 1 | 2 | 3 |
| 3 | 3 | 3 | 6 |
| 4 | 6 | 4 | 10 |
| 5 | 10 | 5 | 15 |

Final `acc` = `15`, which is what gets returned. Think of `acc` as a snowball rolling through the array, picking up a bit more each time. `reduce` is the most general of all these methods — you could technically rebuild `map` or `filter` using `reduce` alone, but it's usually reached for when you want to collapse an array down to one thing: a sum, a count, an object, etc.

## 9. `sort` — reorder the array (with a real gotcha)

```js
const messy = [40, 1, 5, 200];
console.log(messy.sort());
```
Output:
```
[ 1, 200, 40, 5 ]
```
**That's wrong, and it's not a bug in the example — it's how `sort` actually behaves by default.** With no callback, `sort` compares items as *text*, not numbers — so `"200"` sorts before `"40"` because `"2"` comes before `"4"` alphabetically. Fix it by giving `sort` a comparison callback:

```js
console.log(messy.sort(function (a, b) { return a - b; }));
```
Output:
```
[ 1, 5, 40, 200 ]
```
Rule for the comparison callback: if it returns a negative number, `a` comes first; positive, `b` comes first; zero, leave their order alone. `a - b` gives negative when `a < b`, which is exactly "smallest first" — ascending order. `b - a` would sort descending. Also worth knowing: unlike every method above, **`sort` changes the original array in place** instead of returning a new one — this is the one exception in this whole list.

## 10. Method chaining — combining several of these in a row

```js
const result = nums
  .filter(function (n) { return n % 2 === 0; })
  .map(function (n) { return n * 10; })
  .reduce(function (acc, n) { return acc + n; }, 0);
console.log(result);
```
Output:
```
60
```
This works because `filter` and `map` each **return a new array**, and arrays have these same methods available on them — so you can call the next method directly on the result, chained with `.`, instead of saving each step into its own variable. Reading it top to bottom: start with `[1,2,3,4,5]` → filter to evens `[2,4]` → map ×10 `[20,40]` → reduce to a sum `60`. Chaining only works with methods that return something chainable (an array, for `filter`/`map`/`sort`); `forEach` returns `undefined`, so it can't be chained onto — if you see `undefined` errors mid-chain, check whether you accidentally used `forEach` where you meant `map`.

---

## Q&A

1. **What's the one thing all ten of these methods have in common?** They all take a callback function and run it once per array element.
2. **What's the difference between `forEach` and `map`?** `forEach` just runs code per item and returns `undefined`; `map` collects each callback's return value into a new array.
3. **When would you use `find` instead of `filter`?** When you only need the first matching item itself, not an array of all matches.
4. **What's the difference between `includes` and `some`?** `includes` checks for one exact value with no callback; `some` runs a callback test and checks if any item passes it.
5. **What does `every` return if the array is empty?** `true` — there's a vacuous-truth reason (nothing fails a test that's never run), but practically: know that empty arrays make `every` trivially true and `some` trivially false.
6. **In `reduce`, what are the two parts of the callback's first argument's role?** `acc` is the running result carried from the previous step; it starts as the value you passed as `reduce`'s second argument.
7. **Why does `[40, 1, 5, 200].sort()` come out wrong?** Because `sort` compares elements as strings by default, not numbers, so it sorts by text order rather than numeric order.
8. **Does `sort` return a new array or modify the original?** It modifies the original array in place (and also returns it) — the one exception among these methods.
9. **Why can't you chain another array method after `.forEach(...)`?** `forEach` returns `undefined`, which has no array methods on it.
10. **What do `filter` and `map` have in common that makes chaining possible?** Both return a new array, so the next method in the chain has something to call itself on.

---

## Practice problems

Try these yourself before checking the answer key below. Use the array `const scores = [55, 90, 42, 78, 61, 33, 88];` unless a problem says otherwise.

1. Use `map` to create a new array where every score has 5 bonus points added.
2. Use `filter` to get only the passing scores (60 or above).
3. Use `find` to get the first score above 80.
4. Use `includes` to check whether `100` is in `scores`.
5. Use `some` to check whether any score is a perfect 100.
6. Use `every` to check whether every score is at least 30.
7. Use `reduce` to calculate the average of all scores.
8. Use `sort` to sort `scores` from highest to lowest.
9. Chain `filter` + `map` to get the passing scores, each with 5 bonus points added, in one expression.
10. Bonus (combines `reduce` with an object instead of a number): use `reduce` to count how many scores are passing vs failing, ending with an object like `{ passing: 4, failing: 3 }`.

### Answer key

```js
const scores = [55, 90, 42, 78, 61, 33, 88];

// 1
const withBonus = scores.map(function (s) { return s + 5; });

// 2
const passing = scores.filter(function (s) { return s >= 60; });

// 3
const firstOver80 = scores.find(function (s) { return s > 80; });

// 4
const hasPerfect = scores.includes(100);

// 5
const anyPerfect = scores.some(function (s) { return s === 100; });

// 6
const allAtLeast30 = scores.every(function (s) { return s >= 30; });

// 7
const average = scores.reduce(function (acc, s) { return acc + s; }, 0) / scores.length;

// 8
const highToLow = scores.slice().sort(function (a, b) { return b - a; });
// note: .slice() first, to copy the array instead of mutating the original `scores`

// 9
const passingWithBonus = scores
  .filter(function (s) { return s >= 60; })
  .map(function (s) { return s + 5; });

// 10
const counts = scores.reduce(function (acc, s) {
  if (s >= 60) acc.passing++;
  else acc.failing++;
  return acc;
}, { passing: 0, failing: 0 });
```
