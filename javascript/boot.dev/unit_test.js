
// unit_test.js

export const assert = {
  strictEqual(actual, expected, message) {
    if (actual !== expected) {
      throw new Error(`Assertion Failed: ${message}`);
    }
  },
  deepEqual(actual, expected, message) {
    if (actual.length !== expected.length) {
      throw new Error(`Assertion Failed: ${message}`);
    }
    if (!Array.isArray(actual[0])) {
      if (JSON.stringify(actual) !== JSON.stringify(expected)) {
        throw new Error(`Assertion Failed: ${message}`);
      }
      return
    }
    const a = [];
    const b = [];
    for (let i = 0; i < a.length; ++i) {
      a.push(JSON.stringify(actual[i]));
      b.push(JSON.stringify(expected[i]));
    }
    a.sort();
    b.sort();
    for (let i = 0; i < a.length; ++i) {
      if (a[0] !== b[0]) {
        throw new Error(`Assertion Failed: ${message}`);
      }
    }
  },
};

export async function describe(name, fn) {
  console.log(`\n[TEST SUITE] ${name}`);
  try {
    fn();
  } catch (error) {
    console.error(error);
  }
}

export async function it(name, fn) {
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
