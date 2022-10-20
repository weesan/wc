#!/usr/bin/env node

const fs = require("fs");
const readline = require("readline");

file = process.argv[2];

console.log("Javascript")
console.log("Processing %s ...", file)

let fp = readline.createInterface({
  input: fs.createReadStream(file),
  //output: process.stdout,
  console: false,
});

let count = 0
let wc = {}
fp.on("line", (line) => {
  count++
  line.split(" ").forEach((w) => {
    /*
    if (w.length == 0) {
      return;
    }
    */
    wc[w] ? wc[w]++ : wc[w] = 1;
  });
});

fp.on("close", () => {
  console.log("Processed %d lines.", count)

  let sorted = Object.keys(wc).sort((a, b) => wc[b] - wc[a]);

  sorted.forEach((w) => {
    // Note: Console log is very slow, even piped to > /dev/null.
    // console.log("%d: [%s]", wc[w], w);
  });
});
