function Pathfinding (grid, walkerSize) {
    if (!grid || !Array.isArray(grid)) {
        throw new Error('Invalid grid');
    }

    if (typeof walkerSize !== 'number' || walkerSize <= 0) {
        walkerSize = 1;
    } else {
        walkerSize = parseInt(walkerSize, 10);
    }

    this.finder = require('bindings')('pathfindingjs');
    this.x0 = 0;
    this.y0 = 0;
    this.x1 = 0;
    this.y1 = 0;
    this.grid = reArrangeGrid(grid, walkerSize);
    this.finder.setGrid(this.grid);

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
        if (typeof this.x0 !== 'number' || typeof this.y0 !== 'number') {
            throw new Error('Please call .setFrom() before .find()');
        }

        if (typeof this.x1 !== 'number' || typeof this.y1 !== 'number') {
            throw new Error('Please call .setTo() before .find()');
        }

        if (!this.finder.isWalkableAt(this.x0, this.y0)) {
            throw new Error('Invalid starting point (' + this.x0 + ', ' + this.y0 + ')');
        }

        if (!this.finder.isWalkableAt(this.x1, this.y1)) {
            throw new Error('Invalid ending point (' + this.x1 + ', ' + this.y1 + ')');
        }

        if (this.x1 === this.x0 && this.y1 === this.y0) {
            return true;
        }

        this.finder.setGrid(this.grid);
        this.finder.setFrom(this.x0, this.y0);
        var path = this.finder.findTo(this.x1, this.y1);

        this.setFrom(this.x1, this.y1);

        return path;
    };

    function reArrangeGrid (grid, walkerSize) {
        var i;
        var j;

        for (i = 0; i < grid.length; ++i) {
            for (j = 0; j < grid[i].length; ++j) {
                if (grid[i][j] === 1) {
                    setNonWalkabke(grid, i, j, walkerSize);
                }
            }
        }

        for (i = 0; i < grid.length; ++i) {
            for (j = 0; j < grid[i].length; ++j) {
                if (grid[i][j] === 2) {
                    grid[i][j] = 1;
                }
            }
        }

        return grid;
    }

    function setNonWalkabke (grid, i, j, walkerSize) {
        var u;
        var v;

        for (u = i - walkerSize + 1; u <= i + walkerSize - 1; ++u)
        {
            if (grid[u] === undefined || grid[u][0] === undefined) {
                continue;
            }

            for (v = j - walkerSize + 1; v <= j + walkerSize - 1; ++v)
            {
                if (grid[u][v] === undefined) {
                    continue;
                }

                grid[u][v] = 2;
            }
        }
    }
}

module.exports = Pathfinding;
