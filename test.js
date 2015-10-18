var Pathfinding = require('.');
var finder = new Pathfinding();

var grid = [];

var height = 1000;
var width  = 1000;

var startPos = [0, 0];
var endPos   = [];

for (var i = 0; i < height; ++i) {
    grid[i] = [];
    for (var j = 0; j < width; ++j) {
        grid[i][j] = (j % 2 === 0) ? 0 : 1;
    }
}

for (var i = 1; i < width; i +=2) {
    var rowAvailable = Math.floor(Math.random() * height - 1) + 1;
    grid[rowAvailable][i] = 0;

    if (i === width - 1) {
        endPos = [i, rowAvailable];
    }
}

finder
    .setGrid(grid)
    .setFrom(startPos[0], startPos[1])
    .setTo(endPos[0], endPos[1]);

console.log('From', '(' + startPos[0] + ',' + startPos[1] + ')');
console.log('To',  '(' + endPos[0] + ',' + endPos[1] + ')');

var d1 = (new Date()).getTime();
var path = finder.find();
var d2 = (new Date()).getTime() - d1;

if (path !== false) {
    console.log('Found in ' + (d2 / 1000) + 's');
} else {
    console.log('Not found in ' + (d2 / 1000) + 's')
}
