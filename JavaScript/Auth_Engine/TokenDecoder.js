/*
 * Problem: Modern web apps use JSON Web Tokens (JWT) for login. We need to securely 
 * read the user data embedded in this token without making a database call.
 * Logic: Base64 decoding. A JWT has 3 parts separated by dots. The middle part is 
 * the payload. We split the string, decode the middle section, and parse the JSON.
 */

const mockJwt = "header.eyJ1c2VySUQiOiA5OTQsICJyb2xlIjogIkFETUlOIiwgImV4cCI6IDE2OTk5OTk5OTl9.signature";

function decodeToken(token) {
    console.log("\x1b[1m\n--- JWT Payload Decoder ---\x1b[0m");
    try {
        const payloadBase64 = token.split('.')[1]; // Get the middle part
        const decodedString = atob(payloadBase64); // Decode Base64 to text
        const userData = JSON.parse(decodedString);
        
        console.log("  \x1b[32m[Decoded Payload]\x1b[0m", userData);
        
        if (userData.role === "ADMIN") {
            console.log("  \x1b[33m[System]\x1b[0m Admin privileges granted.");
        }
    } catch (error) {
        console.log("  \x1b[31m[Error]\x1b[0m Invalid Token Format");
    }
}

decodeToken(mockJwt);