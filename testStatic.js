var grid = [
    [ 0, 1, 0, 0, 0, 0, 0 ],
    [ 0, 0, 1, 0, 0, 0, 0 ],
    [ 0, 0, 0, 1, 0, 0, 0 ],
    [ 0, 0, 0, 0, 1, 0, 0 ],
    [ 0, 0, 0, 0, 0, 1, 0 ],
    [ 0, 1, 1, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0, 0, 0 ]
];

var Pathfinding = require('.');

var finder = new Pathfinding(grid);
var path = finder
    .setFrom(2, 0)
    .setTo(4, 4)
    .find();
console.log(path);

var returnPath = finder
    .setTo(2, 0)
    .find();
console.log(returnPath);

require('assert').deepEqual(path.reverse(), returnPath);
