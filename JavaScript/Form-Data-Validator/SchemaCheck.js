/*
 * Problem: When a backend receives a JSON payload from a frontend form, it cannot blindly 
 * trust the data. Missing fields or wrong data types (e.g., getting a string instead of a 
 * number for 'age') will crash the database.
 * Logic: We define a strict "Schema" mapping keys to required JavaScript types. We then 
 * iterate through the incoming JSON object to ensure 100% compliance before accepting the payload.
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

// The strict blueprint the data must follow
const userProfileSchema = {
    username: "string",
    age: "number",
    isActive: "boolean"
};

function validatePayload(payload, schema) {
    let errors = [];

    // Check for missing or incorrectly typed fields
    for (const [key, expectedType] of Object.entries(schema)) {
        if (!(key in payload)) {
            errors.push(`Missing required field: '${key}'`);
        } else if (typeof payload[key] !== expectedType) {
            errors.push(`Type mismatch on '${key}': Expected ${expectedType}, got ${typeof payload[key]}`);
        }
    }

    // Check for rogue, unexpected fields injected by the user
    for (const key of Object.keys(payload)) {
        if (!(key in schema)) {
            errors.push(`Unrecognized field injected: '${key}'`);
        }
    }

    return errors;
}

console.log("\x1b[1m\n--- Strict Payload Validator ---\x1b[0m");
console.log("\x1b[90mExpected Schema: { username: String, age: Number, isActive: Boolean }\x1b[0m");
console.log("\x1b[90mTry pasting a valid or invalid JSON object to test the middleware.\x1b[0m\n");

const promptUser = () => {
    readline.question("\x1b[1mIncoming JSON > \x1b[0m", (input) => {
        if (input.toLowerCase() === 'quit' || input.toLowerCase() === 'exit') return readline.close();
        
        try {
            const parsedData = JSON.parse(input);
            const validationErrors = validatePayload(parsedData, userProfileSchema);

            if (validationErrors.length === 0) {
                console.log("  \x1b[32m[200 OK] Payload accepted and validated.\x1b[0m\n");
            } else {
                console.log("  \x1b[31m[400 Bad Request] Validation failed:\x1b[0m");
                validationErrors.forEach(err => console.log(`   - ${err}`));
                console.log("");
            }
        } catch (error) {
            console.log("  \x1b[31m[400 Bad Request] Malformed JSON syntax.\x1b[0m\n");
        }
        
        promptUser();
    });
};

promptUser();