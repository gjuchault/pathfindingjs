function Pathfinding () {
    this.x0 = 0;
    this.y0 = 0;
    this.x1 = 0;
    this.y1 = 0;
    this.walkerSize = 1;
    this.grid = [ [ 0 ] ];

    this.setGrid = function (grid) {
        this.grid = grid;
        return this;
    }

    this.setWalkerSize = function (n) {
        this.walkerSize = n;
        return this;
    };

    this.setFrom = function (x, y) {
        this.x0 = x;
        this.y0 = y;
        return this;
    };

    this.setTo = function (x, y) {
        this.x1 = x;
        this.y1 = y;
        return this;
    };

    this.find = function () {
        if (this.grid[this.y0] == undefined || this.grid[this.y0][this.x0] == undefined) {
            throw new Error('Unknown start case');
        }

        if (this.grid[this.y1] == undefined || this.grid[this.y1][this.x1] == undefined) {
            throw new Error('Unknown ends case');
        }

        if (this.grid[this.y0][this.x0] === 1) {
            throw new Error('Unwalkable start case');
        }

        if (this.grid[this.y1][this.x1] === 1) {
            throw new Error('Unwalkable start case');
        }

        if (this.x1 === this.y0 && this.y1 === this.y0) {
            return true;
        }

        var finder = require('bindings')('pathfindingjs');

        finder.setGrid(this.grid);
        finder.setWalkerSize(this.walkerSize);
        finder.setFrom(this.x0, this.y0);
        return finder.findTo(this.x1, this.y1);
    };
}

module.exports = Pathfinding;
