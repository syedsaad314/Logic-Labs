const Visualizer = {
    cols: 40, rows: 20,
    grid: [],
    startNode: [5, 5],
    endNode: [15, 35],

    init() {
        const container = document.getElementById('grid-container');
        for (let r = 0; r < this.rows; r++) {
            this.grid[r] = [];
            for (let c = 0; c < this.cols; c++) {
                const cell = document.createElement('div');
                cell.className = 'cell';
                cell.onmousedown = () => this.toggleWall(r, c);
                container.appendChild(cell);
                this.grid[r][c] = { r, c, isWall: false, visited: false, dist: Infinity, prev: null, element: cell };
            }
        }
        this.updatePoints();
    },

    updatePoints() {
        this.grid[this.startNode[0]][this.startNode[1]].element.classList.add('start');
        this.grid[this.endNode[0]][this.endNode[1]].element.classList.add('end');
    },

    toggleWall(r, c) {
        if ((r === this.startNode[0] && c === this.startNode[1]) || (r === this.endNode[0] && c === this.endNode[1])) return;
        this.grid[r][c].isWall = !this.grid[r][c].isWall;
        this.grid[r][c].element.classList.toggle('wall');
    },

    async solve() {
        let queue = [];
        const start = this.grid[this.startNode[0]][this.startNode[1]];
        start.dist = 0;
        queue.push(start);

        while (queue.length > 0) {
            queue.sort((a, b) => a.dist - b.dist);
            let current = queue.shift();
            if (current.visited || current.isWall) continue;
            current.visited = true;
            if (current !== start) current.element.classList.add('visited');

            if (current.r === this.endNode[0] && current.c === this.endNode[1]) break;

            const neighbors = this.getNeighbors(current);
            for (let neighbor of neighbors) {
                if (current.dist + 1 < neighbor.dist) {
                    neighbor.dist = current.dist + 1;
                    neighbor.prev = current;
                    queue.push(neighbor);
                }
            }
            await new Promise(r => setTimeout(r, 5));
        }
        this.drawPath();
    },

    getNeighbors(node) {
        let neighbors = [];
        const { r, c } = node;
        if (r > 0) neighbors.push(this.grid[r - 1][c]);
        if (r < this.rows - 1) neighbors.push(this.grid[r + 1][c]);
        if (c > 0) neighbors.push(this.grid[r][c - 1]);
        if (c < this.cols - 1) neighbors.push(this.grid[r][c + 1]);
        return neighbors.filter(n => !n.visited);
    },

    drawPath() {
        let curr = this.grid[this.endNode[0]][this.endNode[1]].prev;
        while (curr && curr.dist !== 0) {
            curr.element.classList.add('path');
            curr = curr.prev;
        }
    },

    reset() { location.reload(); }
};

window.onload = () => Visualizer.init();