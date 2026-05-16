/* * [PROBLEM STATEMENT]
 * If a database or third-party API goes down, continuously hammering it 
 * with requests will cause cascading system failures. We need a mechanism 
 * to "trip" and stop sending traffic to a dead service until it recovers.
 *
 * [LOGIC & INSIGHT]
 * I built an 'API Circuit Breaker'. It wraps standard functions. If a 
 * function fails 3 times in a row, the state changes from 'CLOSED' 
 * (traffic flows) to 'OPEN' (traffic is blocked). It implements a 
 * 'Cooldown Phase' where it waits before sending a test ping to see if 
 * the service is back. This is Netflix-level resilience engineering 
 * built in pure Vanilla JS.
 */

class CircuitBreaker {
    constructor(requestFunction, failureThreshold = 3, cooldownMs = 3000) {
        this.requestFunction = requestFunction;
        this.failureThreshold = failureThreshold;
        this.cooldownMs = cooldownMs;
        this.failures = 0;
        this.state = 'CLOSED'; // CLOSED = Traffic flows normally
        this.nextAttempt = null;
    }

    async fire(...args) {
        if (this.state === 'OPEN') {
            if (Date.now() > this.nextAttempt) {
                console.log(`\x1b[33m[CIRCUIT]\x1b[0m Half-Open. Testing service recovery...`);
                this.state = 'HALF_OPEN';
            } else {
                console.log(`\x1b[31m[CIRCUIT]\x1b[0m OPEN. Request blocked to prevent cascading failure.`);
                return null;
            }
        }

        try {
            const response = await this.requestFunction(...args);
            return this.onSuccess(response);
        } catch (error) {
            return this.onFailure(error);
        }
    }

    onSuccess(response) {
        this.failures = 0;
        this.state = 'CLOSED';
        console.log(`\x1b[32m[API]\x1b[0m Success:`, response);
        return response;
    }

    onFailure(error) {
        this.failures++;
        console.log(`\x1b[31m[API]\x1b[0m Request Failed. (Strike ${this.failures})`);
        
        if (this.failures >= this.failureThreshold) {
            this.state = 'OPEN';
            this.nextAttempt = Date.now() + this.cooldownMs;
            console.log(`\x1b[41m\x1b[30m [FATAL] Threshold reached. CIRCUIT TRIPPED! \x1b[0m`);
        }
        return null;
    }
}

// Mocking a failing API
const unstableAPI = async () => { throw new Error("Connection Timeout"); };

const breaker = new CircuitBreaker(unstableAPI, 2);

console.log("\x1b[1m--- INITIATING SYSTEM STRESS TEST ---\x1b[0m");
setTimeout(() => breaker.fire(), 100);
setTimeout(() => breaker.fire(), 200);
setTimeout(() => breaker.fire(), 300); // This will trip the circuit
setTimeout(() => breaker.fire(), 400); // This will be blocked instantly