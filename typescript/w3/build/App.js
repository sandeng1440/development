"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const TheoTryCatch_1 = require("./TheoTryCatch");
async function add(a, b) {
    const ran = Math.random();
    if (ran < 0.5) {
        throw `ERROR: Random number too low`;
    }
    return a + b;
}
const doStuff = (async () => {
    const { data, error } = await (0, TheoTryCatch_1.tryCatch)(add(2, 5));
    if (error) {
        console.log(`Failed to get Data1. ${error}`);
        return null;
    }
    else {
        return data;
    }
})().then(data => {
    if (data)
        console.log(`Data1: ${data}`);
});
const norm = add(3, 2).then(n => {
    console.log(`Data2: ${n}`);
}).catch(e => {
    console.log(`Failed to get Data2: ${e}`);
});
const p = new Promise((resolve, reject) => {
    const rn = Math.random();
    if (rn < 0.5)
        resolve(`The promise was resolved: ${rn}`);
    reject(`The promise was rejected: ${rn}`);
}).then((value) => console.log(value), (reason) => console.log(reason));
