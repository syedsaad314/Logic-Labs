/* * [PROBLEM STATEMENT]
 * On a search bar, if a user types "Karachi", a standard event listener 
 * fires 7 API calls (one for each letter). This hammers the server and 
 * slows down the UI. We need a way to "wait" until the user stops typing 
 * before firing the call.
 *
 * [LOGIC & INSIGHT]
 * I built a 'Debounce Wrapper'. It uses high-order functions and 
 * closures. The logic is: "Wait 500ms. If the user presses another key, 
 * reset the timer. Only when the timer finally runs out do we fire the 
 * actual function." This saves 90% of network traffic on a typical 
 * search input. It's a must-have for any professional dashboard.
 */

const debounce = (func, delay) => {
    let timerId;
    return (...args) => {
        if (timerId) {
            console.log("\x1b[90m  [DEBOUNCE]\x1b[0m Resetting timer...");
            clearTimeout(timerId);
        }
        timerId = setTimeout(() => {
            func.apply(null, args);
        }, delay);
    };
};

// The expensive task we want to limit
const fetchResults = (query) => {
    console.log(`\n\x1b[32m[API_CALL]\x1b[0m Searching database for: "${query}"`);
    console.log(`\x1b[34m[STATUS]\x1b[0m Results fetched for ${query.length} chars.\n`);
};

const optimizedSearch = debounce(fetchResults, 1000);

// Simulating rapid typing
console.log("\x1b[1m--- SIMULATING USER TYPING 'UBIT' ---\x1b[0m");
optimizedSearch("U");
optimizedSearch("UB");
optimizedSearch("UBI");
optimizedSearch("UBIT"); // Only this one should fire after 1 second