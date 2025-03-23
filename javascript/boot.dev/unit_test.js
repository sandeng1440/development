
// unit_test.js

export const assert = {
  strictEqual(actual, expected, message) {
    if (actual !== expected) {
      throw new Error(`Assertion Failed: ${message}`);
    }
  },
};

export function describe(name, fn) {
  console.log(`\n[TEST SUITE] ${name}`);
  try {
    fn();
  } catch (error) {
    console.error(error);
  }
}

export function it(name, fn) {
  try {
    fn();
    console.log(`✔ PASS: ${name}`);
  } catch (error) {
    console.error(`✖ FAIL: ${name}`);
    console.error(error.message);
  }
}

// Simulating the 'withSubmit' feature
export const withSubmit = true;
