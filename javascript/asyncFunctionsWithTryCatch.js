import { tryCatch } from "./TheoTryCatch.js";

async function getData() {
  const rn = Math.random();
  if (rn < 0.5) {
    throw `Failed to get data`;
  }
  return `Here's the data...`;
}

const { data, error } = await tryCatch(getData());
if (error) {
  console.log(`Error: ${error}`);
} else {
  console.log(`Outcome: ${data}`);
}
