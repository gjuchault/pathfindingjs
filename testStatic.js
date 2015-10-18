var grid = [
    [ 0, 1, 0, 0, 0 ],
    [ 0, 0, 1, 0, 0 ],
    [ 0, 0, 0, 1, 0 ],
    [ 0, 1, 1, 1, 0 ],
    [ 0, 0, 0, 0, 0 ]
];

var Pathfinding = require('.');

var finder = new Pathfinding();
finder
    .setGrid(grid)
    .setFrom(2, 0)
    .setTo(2, 2)
    .find();