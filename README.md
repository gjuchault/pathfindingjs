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

var finder = new Pathfinding();
var path = finder
    .setGrid(grid)
    .setFrom(2, 0)
    .setTo(2, 2)
    .find();
console.log(path);
```

## Walker size

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

var finder = new Pathfinding();
var path = finder
    .setGrid(grid)
    .setFrom(1, 1)
    .setWalkerSize(2)
    .setTo(13, 2)
    .find();

console.log(path);
```
