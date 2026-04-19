/*
 * Problem: Raw text pasted from the internet is messy. We need to scrape actionable 
 * data (like emails, phone numbers, and URLs) out of chaotic strings.
 * Logic: Regular Expressions (Regex). We compile robust search patterns that scan the 
 * entire string, extracting matches into clean, categorized arrays regardless of formatting.
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

const PATTERNS = {
    emails: /[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}/g,
    urls: /https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*)/g,
    phones: /\b\d{3}[-.]?\d{3}[-.]?\d{4}\b/g // Standard 10 digit formats: 123-456-7890
};

function mineData(rawText) {
    const extracted = {
        Emails: rawText.match(PATTERNS.emails) || [],
        Links: rawText.match(PATTERNS.urls) || [],
        Phones: rawText.match(PATTERNS.phones) || []
    };

    console.log("\n\x1b[1m--- Extraction Results ---\x1b[0m");
    
    for (const [category, items] of Object.entries(extracted)) {
        if (items.length > 0) {
            console.log(`\x1b[36m${category}:\x1b[0m`);
            // Deduplicate using Set to make it professional
            const uniqueItems = [...new Set(items)]; 
            uniqueItems.forEach(item => console.log(`  - \x1b[32m${item}\x1b[0m`));
        } else {
            console.log(`\x1b[36m${category}:\x1b[0m \x1b[90mNo matches found.\x1b[0m`);
        }
    }
    console.log("");
}

console.log("\x1b[1m\n--- Text Entity Miner ---\x1b[0m");
console.log("\x1b[90mPaste a messy block of text containing emails, links, or phone numbers.\x1b[0m");
console.log("\x1b[90mType 'quit' to exit.\x1b[0m\n");

const promptUser = () => {
    readline.question("\x1b[1mRaw Text > \x1b[0m", (input) => {
        if (input.toLowerCase() === 'quit' || input.toLowerCase() === 'exit') return readline.close();
        
        mineData(input);
        promptUser();
    });
};

promptUser();