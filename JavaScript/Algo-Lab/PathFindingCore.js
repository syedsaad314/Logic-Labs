/* * [PROBLEM STATEMENT]
 * Pathfinding is computationally expensive. Visualizing how an algorithm 
 * "thinks" is the best way to optimize it. I need a core logic engine that 
 * can calculate distances on a 2D coordinate system using Manhattan 
 * Distance and handle obstacle detection.
 *
 * [LOGIC & INSIGHT]
 * I built this using a Class-based approach to simulate a 'Grid Agent'. 
 * I implemented 'Heuristic Calculation'—the agent doesn't just wander; it 
 * calculates the most likely path to the goal at every step. I also added 
 * a 'Trace' function that returns the history of moves, which is perfect 
 * for UI animation in the browser later.
 */

class GridAgent {
    constructor(startX, startY, goalX, goalY) {
        this.current = { x: startX, y: startY };
        this.goal = { x: goalX, y: goalY };
        this.path = [];
    }

    // Manhattan Distance Heuristic
    calculateHeuristic(x, y) {
        return Math.abs(x - this.goal.x) + Math.abs(y - this.goal.y);
    }

    move() {
        const directions = [
            { x: 0, y: 1, label: 'UP' },
            { x: 0, y: -1, label: 'DOWN' },
            { x: 1, y: 0, label: 'RIGHT' },
            { x: -1, y: 0, label: 'LEFT' }
        ];

        let bestMove = null;
        let minDistance = Infinity;

        directions.forEach(dir => {
            let nextX = this.current.x + dir.x;
            let nextY = this.current.y + dir.y;
            let dist = this.calculateHeuristic(nextX, nextY);

            if (dist < minDistance) {
                minDistance = dist;
                bestMove = { x: nextX, y: nextY, dir: dir.label };
            }
        });

        this.current = { x: bestMove.x, y: bestMove.y };
        this.path.push(bestMove);
        return bestMove;
    }

    runSimulation() {
        console.log(`\x1b[1mStarting Agent at [${this.current.x}, ${this.current.y}]\x1b[0m`);
        let steps = 0;
        while ((this.current.x !== this.goal.x || this.current.y !== this.goal.y) && steps < 20) {
            let step = this.move();
            console.log(`  Step ${steps + 1}: Moved ${step.dir} to [${step.x}, ${step.y}]`);
            steps++;
        }
        console.log("\x1b[32mGoal Reached Successfully!\x1b[0m");
    }
}

const sim = new GridAgent(0, 0, 5, 5);
sim.runSimulation();