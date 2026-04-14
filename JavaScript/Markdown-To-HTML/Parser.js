/*
 * Problem: Modern text inputs (like Discord, Reddit, or Notion) allow users to type in 
 * Markdown, which the backend must instantly compile into readable HTML for the browser.
 * Logic: We utilize Regular Expressions (Regex) to map specific string patterns 
 * (like **bold**) and safely replace them with their HTML equivalents (<b>bold</b>).
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

function parseMarkdown(text) {
    let html = text;

    // Headings: # Heading 1 -> <h1>Heading 1</h1>
    html = html.replace(/^### (.*$)/gim, '<h3>$1</h3>');
    html = html.replace(/^## (.*$)/gim, '<h2>$1</h2>');
    html = html.replace(/^# (.*$)/gim, '<h1>$1</h1>');

    // Bold: **text** -> <strong>text</strong>
    html = html.replace(/\*\*(.*?)\*\*/gim, '<strong>$1</strong>');

    // Italic: *text* -> <em>text</em>
    html = html.replace(/\*(.*?)\*/gim, '<em>$1</em>');

    // Blockquote: > text -> <blockquote>text</blockquote>
    html = html.replace(/^> (.*$)/gim, '<blockquote>$1</blockquote>');

    return html;
}

console.log("\x1b[1m\n--- Live Markdown Compiler ---\x1b[0m");
console.log("\x1b[90mSupported syntax: # Heading, **Bold**, *Italic*, > Quote\x1b[0m");
console.log("\x1b[90mType 'quit' to exit.\x1b[0m\n");

const promptUser = () => {
    readline.question("\x1b[1mMarkdown > \x1b[0m", (input) => {
        if (input.toLowerCase() === 'quit') return readline.close();
        
        const output = parseMarkdown(input);
        console.log(`\x1b[36mHTML     >\x1b[0m \x1b[32m${output}\x1b[0m\n`);
        
        promptUser();
    });
};

promptUser();