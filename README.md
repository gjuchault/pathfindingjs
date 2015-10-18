# Pathfindingjs

Install with `npm install gjuchault/pathfindingjs --save`

## Basic usage

```js
var grid = [
    [ 0, 1, 0, 0, 0 ],
    [ 0, 0, 1, 0, 0 ],
    [ 0, 0, 0, 1, 0 ],
    [ 0, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0 ]
];

var Pathfinding = require('pathfindingjs');

var finder = new Pathfinding(grid);
var path = finder
    .setFrom(2, 0)
    .setTo(2, 2)
    .find();
console.log(path);
```

Note : if you try to reach the origin point (from `(2, 0)` to `(2, 0)`), `find` will return true

## Walker size

The walker size is a number representing the width taken by the walker around its starting point.
That means that a basic walker has a walker size of 1 (`O` being the walker) :
```
. . . .
. O . .
. . . .
. . . .
```

And a walker with a size of two is like this (`O` and `x` being the walker) :
```
x x x .
x O x .
x x x .
. . . .
```

```
var grid = [
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 ]
];

var Pathfinding = require('.');

var finder = new Pathfinding(grid, 2);
var path = finder
    .setFrom(1, 1)
    .setTo(13, 2)
    .find();

console.log(path);
```

## Chaining

After calling find, the origin is set to the target point, and you may call `setTo` and `find` again

```js
var grid = [
    [ 0, 1, 0, 0, 0 ],
    [ 0, 0, 1, 0, 0 ],
    [ 0, 0, 0, 1, 0 ],
    [ 0, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0 ]
];

var Pathfinding = require('pathfindingjs');

var finder = new Pathfinding(grid);
var path = finder
    .setFrom(2, 0)
    .setTo(2, 2)
    .find();
console.log(path);

var returnPath = finder
    .setTo(2, 0)
    .find();
console.log(returnPath);

require('assert').deepEqual(path.reverse(), returnPath);
```
